#ifndef ZERO_ENGINE_GL_
#define ZERO_ENGINE_GL_

#include <SDL3/SDL_opengl.h>
#include <SDL3/sdl_video.h>

namespace GL {
  void UnloadGLFunctions();
  void LoadGLFunctions();

  /**
   * Generate buffer object names
   * @returns void
   */
  extern PFNGLGENBUFFERSPROC glGenBuffers;
  extern PFNGLBINDBUFFERPROC glBindBuffer;
  extern PFNGLBUFFERDATAPROC glBufferData;
  extern PFNGLCREATESHADERPROC glCreateShader;
  extern PFNGLCOMPILESHADERPROC glCompileShader;
  extern PFNGLSHADERSOURCEPROC glShaderSource;
  extern PFNGLGETSHADERIVPROC glGetShaderiv;
  extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
  extern PFNGLCREATEPROGRAMPROC glCreateProgram;
  extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
  extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
  extern PFNGLLINKPROGRAMPROC glLinkProgram;
  extern PFNGLATTACHSHADERPROC glAttachShader;
  extern PFNGLDETACHSHADERPROC glDetachShader;
  extern PFNGLUSEPROGRAMPROC glUseProgram;
  extern PFNGLDELETESHADERPROC glDeleteShader;
}  // namespace GL

#endif