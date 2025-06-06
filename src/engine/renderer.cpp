#include "zero/renderer.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>
#include <fmt/format.h>
#include <spdlog/common.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <stdexcept>

#include "zero/gl.hpp"
#include "zero/renderable-manager.hpp"
#include "zero/shader-program.hpp"

std::shared_ptr<spdlog::logger> Renderer::logger = nullptr;

Renderer::Renderer(SDL_Window *window, unsigned int width, unsigned int height) : boundShaderProgram(0) {
  if (logger == nullptr) {
    logger = spdlog::stdout_color_mt("renderer");
    logger->set_level(spdlog::level::trace);
  }

  if (window == nullptr) {
    throw std::runtime_error("Unable to create renderer from a null window.");
  }

  this->window = window;

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  glContext = SDL_GL_CreateContext(window);

  if (glContext == nullptr) {
    std::string message = fmt::format("Unabled to create OpenGL context: {}", SDL_GetError());
    throw std::runtime_error(message);
  }

  // NOTE: load dynamic functions
  GL::LoadGLFunctions();

  glViewport(0, 0, width, height);

  if (!SDL_GL_SetSwapInterval(1)) {
    std::string message = fmt::format("Unabled to set VSync: {}", SDL_GetError());
    throw std::runtime_error(message);
  };

  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
#ifdef DEBUG_BUILD
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  GL::glDebugMessageCallback(Renderer::Log, nullptr);
  GL::glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif

  glVendor = glGetString(GL_VENDOR);
  glVersion = glGetString(GL_VERSION);
  glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
}

Renderer::~Renderer() {
  if (this->glContext != nullptr) {
    SDL_GL_DestroyContext(this->glContext);
    GL::UnloadGLFunctions();
  }
}

void Renderer::ClearScreen() const {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SwapBuffers() const { SDL_GL_SwapWindow(window); }

void Renderer::ClearUsedShaderProgram() {
  GL::glUseProgram(0);
  boundShaderProgram = 0;
}

void Renderer::BindShader(const std::shared_ptr<ShaderProgram> &shader) {
  unsigned int shaderId = shader->Get();
  if (boundShaderProgram == shaderId) {
    return;
  }
  boundShaderProgram = shaderId;
  GL::glUseProgram(shaderId);
}

void Renderer::RenderScene() {
  RenderableManager::CleanRenderables();

  for (const auto &objectPointer : RenderableManager::GetRenderables()) {
    if (const auto &renderable = objectPointer.lock()) {
      renderable->SubmitRender(*this);
    }
  }
}

void Renderer::Log(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei, const char *message,
                   const void *) {
  // NOTE: ignore non-significant error/warning codes
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

  std::string sourcefmt;
  std::string typefmt;
  std::string logMessage = fmt::format("{}|{}", id, message);

  switch (source) {
    case GL_DEBUG_SOURCE_API:
      sourcefmt = "Source: API";
      break;
    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
      sourcefmt = "Source: Window System";
      break;
    case GL_DEBUG_SOURCE_SHADER_COMPILER:
      sourcefmt = "Source: Shader Compiler";
      break;
    case GL_DEBUG_SOURCE_THIRD_PARTY:
      sourcefmt = "Source: Third Party";
      break;
    case GL_DEBUG_SOURCE_APPLICATION:
      sourcefmt = "Source: Application";
      break;
    case GL_DEBUG_SOURCE_OTHER:
      sourcefmt = "Source: Other";
      break;
  }

  switch (type) {
    case GL_DEBUG_TYPE_ERROR:
      typefmt = "Type: Error";
      break;
    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
      typefmt = "Type: Deprecated Behaviour";
      break;
    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
      typefmt = "Type: Undefined Behaviour";
      break;
    case GL_DEBUG_TYPE_PORTABILITY:
      typefmt = "Type: Portability";
      break;
    case GL_DEBUG_TYPE_PERFORMANCE:
      typefmt = "Type: Performance";
      break;
    case GL_DEBUG_TYPE_MARKER:
      typefmt = "Type: Marker";
      break;
    case GL_DEBUG_TYPE_PUSH_GROUP:
      typefmt = "Type: Push Group";
      break;
    case GL_DEBUG_TYPE_POP_GROUP:
      typefmt = "Type: Pop Group";
      break;
    case GL_DEBUG_TYPE_OTHER:
      typefmt = "Type: Other";
      break;
  }

  switch (severity) {
    case GL_DEBUG_SEVERITY_HIGH: {
      logger->debug("[high] {}|{}|{}", logMessage, sourcefmt, typefmt);
      break;
    }
    case GL_DEBUG_SEVERITY_MEDIUM: {
      logger->debug("[medium] {}|{}|{}", logMessage, sourcefmt, typefmt);
      break;
    }
    case GL_DEBUG_SEVERITY_LOW: {
      logger->debug("[low] {}|{}|{}", logMessage, sourcefmt, typefmt);
      break;
    }
    case GL_DEBUG_SEVERITY_NOTIFICATION: {
      logger->debug("[notification] {}|{}|{}", logMessage, sourcefmt, typefmt);
      break;
    }
  }
}