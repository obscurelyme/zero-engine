#ifndef ZERO_ENGINE_RENDERER_
#define ZERO_ENGINE_RENDERER_

#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>
#include <memory.h>
#include <spdlog/logger.h>
#include <spdlog/spdlog.h>

#include <memory>

#include "shader-program.hpp"
#include "zero/irenderable.hpp"

class Renderer {
  public:
    Renderer(SDL_Window* window, unsigned int width, unsigned int height);
    Renderer(const Renderer&) = delete;
    const Renderer operator=(const Renderer&) = delete;
    ~Renderer();

    void ClearScreen() const;
    void SwapBuffers() const;
    void BindShader(const std::shared_ptr<ShaderProgram>& shader);
    void RenderScene();
    /**
     * Called at the end of the frame or whenever you need to unset the used shader program.
     */
    void ClearUsedShaderProgram();
    static bool IsShaderProgramBound(unsigned int shaderProgram);
    static void Log(GLenum source, GLenum type, unsigned int id, GLenum severity, GLsizei length, const char* message,
                    const void* userParam);

  private:
    void cleanRenderables();

    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;
    const GLubyte* glVendor;
    const GLubyte* glVersion;
    const GLubyte* glslVersion;
    unsigned int boundShaderProgram;

    static std::shared_ptr<spdlog::logger> logger;
};

#endif