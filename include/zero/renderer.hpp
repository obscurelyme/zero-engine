#ifndef ZERO_ENGINE_RENDERER_
#define ZERO_ENGINE_RENDERER_

#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_video.h>

class Renderer {
  public:
    Renderer(SDL_Window* window, unsigned int width, unsigned int height);
    Renderer(const Renderer&) = delete;
    const Renderer operator=(const Renderer&) = delete;
    ~Renderer();

    void ClearScreen() const;
    void SwapBuffers() const;
    /**
     * Called at the end of the frame or whenever you need to unset the used shader program.
     */
    void ClearUsedShaderProgram() const;

  private:
    SDL_Window* window = nullptr;
    SDL_GLContext glContext = nullptr;
    const GLubyte* glVendor;
    const GLubyte* glVersion;
    const GLubyte* glslVersion;
};

#endif