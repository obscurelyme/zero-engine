#include "zero/gl.hpp"

#include <SDL3/sdl_video.h>

namespace GL {
  PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
  PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
  PFNGLBUFFERDATAPROC glBufferData = nullptr;
  PFNGLCREATESHADERPROC glCreateShader = nullptr;
  PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
  PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
  PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
  PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;

  void LoadGLFunctions() {
    glGenBuffers = reinterpret_cast<PFNGLGENBUFFERSPROC>(SDL_GL_GetProcAddress("glGenBuffers"));
    glBindBuffer = reinterpret_cast<PFNGLBINDBUFFERPROC>(SDL_GL_GetProcAddress("glBindBuffer"));
    glBufferData = reinterpret_cast<PFNGLBUFFERDATAPROC>(SDL_GL_GetProcAddress("glBufferData"));
    glCreateShader = reinterpret_cast<PFNGLCREATESHADERPROC>(SDL_GL_GetProcAddress("glCreateShader"));
    glCompileShader = reinterpret_cast<PFNGLCOMPILESHADERPROC>(SDL_GL_GetProcAddress("glCompileShader"));
    glShaderSource = reinterpret_cast<PFNGLSHADERSOURCEPROC>(SDL_GL_GetProcAddress("glShaderSource"));
    glGetShaderiv = reinterpret_cast<PFNGLGETSHADERIVPROC>(SDL_GL_GetProcAddress("glGetShaderiv"));
    glGetShaderInfoLog = reinterpret_cast<PFNGLGETSHADERINFOLOGPROC>(SDL_GL_GetProcAddress("glGetShaderInfoLog"));
  }

  void UnloadGLFunctions() {
    glGenBuffers = nullptr;
    glBindBuffer = nullptr;
    glBufferData = nullptr;
    glCreateShader = nullptr;
    glCompileShader = nullptr;
    glShaderSource = nullptr;
    glGetShaderiv = nullptr;
    glGetShaderInfoLog = nullptr;
  }

}  // namespace GL
