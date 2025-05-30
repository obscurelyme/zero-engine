#ifndef ZERO_ENGINE_GL_
#define ZERO_ENGINE_GL_

#include <SDL3/SDL_opengl.h>
#include <SDL3/sdl_video.h>

namespace GL {
  void UnloadGLFunctions();
  void LoadGLFunctions();

  /**
   * Register a callback function that will be called whenever a debug message is generated. This is useful for
   * debugging and getting detailed information about OpenGL operations.
   * ---
   * @param GLenum source,
   * @param GLenum type,
   * @param unsigned int id,
   * @param GLenum severity,
   * @param GLsizei length,
   * @param const char *message,
   * @param const void *userParam
   */
  extern PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback;
  extern PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl;

  /**
   * Generate buffer object names
   * @returns void
   */
  extern PFNGLGENBUFFERSPROC glGenBuffers;
  extern PFNGLBINDBUFFERPROC glBindBuffer;
  extern PFNGLBUFFERDATAPROC glBufferData;

  extern PFNGLCREATESHADERPROC glCreateShader;
  extern PFNGLDELETESHADERPROC glDeleteShader;
  extern PFNGLCOMPILESHADERPROC glCompileShader;
  extern PFNGLSHADERSOURCEPROC glShaderSource;
  extern PFNGLGETSHADERIVPROC glGetShaderiv;
  extern PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;

  extern PFNGLCREATEPROGRAMPROC glCreateProgram;
  extern PFNGLDELETEPROGRAMPROC glDeleteProgram;
  extern PFNGLGETPROGRAMIVPROC glGetProgramiv;
  extern PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
  extern PFNGLLINKPROGRAMPROC glLinkProgram;
  extern PFNGLATTACHSHADERPROC glAttachShader;
  extern PFNGLDETACHSHADERPROC glDetachShader;
  extern PFNGLUSEPROGRAMPROC glUseProgram;

  /**
   * ---
   *
   * @param index - Specifies the index of the generic vertex attribute to be modified.
   * @param size - Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4. Additionally,
   * the symbolic constant GL_BGRA is accepted by glVertexAttribPointer. The initial value is 4.
   * @param type - Specifies the data type of each component in the array.
   * @param normalized - specifies whether fixed-point data values should be normalized
   * @param stride - Specifies the byte offset between consecutive generic vertex attributes. If stride is 0, the
   * generic vertex attributes are understood to be tightly packed in the array. The initial value is 0.
   * @param pointer - Specifies a offset of the first component of the first generic vertex attribute in the array in
   * the data store of the buffer currently bound to the GL_ARRAY_BUFFER target. The initial value is 0.
   */
  extern PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
  extern PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
  extern PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
  extern PFNGLBINDVERTEXARRAYPROC glBindVertexArray;
}  // namespace GL

#endif