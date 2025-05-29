#include "zero/renderer.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>
#include <fmt/format.h>

#include <stdexcept>

#include "zero/gl.hpp"

Renderer::Renderer(SDL_Window* window, unsigned int width, unsigned int height) {
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
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::SwapBuffers() const { SDL_GL_SwapWindow(window); }