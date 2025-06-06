#include "zero/gl.hpp"

#define LOAD_GL_FUNC(name) name = reinterpret_cast<decltype(name)>(SDL_GL_GetProcAddress(#name))

namespace GL {
  PFNGLDEBUGMESSAGECALLBACKPROC glDebugMessageCallback = nullptr;
  PFNGLDEBUGMESSAGECONTROLPROC glDebugMessageControl = nullptr;
  PFNGLGENBUFFERSPROC glGenBuffers = nullptr;
  PFNGLBINDBUFFERPROC glBindBuffer = nullptr;
  PFNGLBUFFERDATAPROC glBufferData = nullptr;
  PFNGLCREATESHADERPROC glCreateShader = nullptr;
  PFNGLCOMPILESHADERPROC glCompileShader = nullptr;
  PFNGLSHADERSOURCEPROC glShaderSource = nullptr;
  PFNGLGETSHADERIVPROC glGetShaderiv = nullptr;
  PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = nullptr;
  PFNGLDELETEPROGRAMPROC glDeleteProgram = nullptr;
  PFNGLCREATEPROGRAMPROC glCreateProgram = nullptr;
  PFNGLGETPROGRAMIVPROC glGetProgramiv = nullptr;
  PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = nullptr;
  PFNGLLINKPROGRAMPROC glLinkProgram = nullptr;
  PFNGLATTACHSHADERPROC glAttachShader = nullptr;
  PFNGLDETACHSHADERPROC glDetachShader = nullptr;
  PFNGLUSEPROGRAMPROC glUseProgram = nullptr;
  PFNGLDELETESHADERPROC glDeleteShader = nullptr;
  PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = nullptr;
  PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = nullptr;
  PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = nullptr;
  PFNGLBINDVERTEXARRAYPROC glBindVertexArray = nullptr;
  PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = nullptr;

  PFNGLUNIFORM1FPROC glUniform1f = nullptr;
  PFNGLUNIFORM2FPROC glUniform2f = nullptr;
  PFNGLUNIFORM3FPROC glUniform3f = nullptr;
  PFNGLUNIFORM4FPROC glUniform4f = nullptr;

  PFNGLUNIFORM1IPROC glUniform1i = nullptr;
  PFNGLUNIFORM2IPROC glUniform2i = nullptr;
  PFNGLUNIFORM3IPROC glUniform3i = nullptr;
  PFNGLUNIFORM4IPROC glUniform4i = nullptr;

  PFNGLUNIFORM1DPROC glUniform1d = nullptr;
  PFNGLUNIFORM2DPROC glUniform2d = nullptr;
  PFNGLUNIFORM3DPROC glUniform3d = nullptr;
  PFNGLUNIFORM4DPROC glUniform4d = nullptr;

  PFNGLUNIFORM1UIPROC glUniform1ui = nullptr;
  PFNGLUNIFORM2UIPROC glUniform2ui = nullptr;
  PFNGLUNIFORM3UIPROC glUniform3ui = nullptr;
  PFNGLUNIFORM4UIPROC glUniform4ui = nullptr;

  PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = nullptr;
  PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = nullptr;
  PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = nullptr;

  PFNGLBUFFERSUBDATAPROC glBufferSubData = nullptr;
  PFNGLACTIVETEXTUREPROC glActiveTexture = nullptr;
  PFNGLGENERATEMIPMAPPROC glGenerateMipmap = nullptr;

  void LoadGLFunctions() {
    LOAD_GL_FUNC(glDebugMessageCallback);
    LOAD_GL_FUNC(glDebugMessageControl);

    LOAD_GL_FUNC(glGenBuffers);
    LOAD_GL_FUNC(glBindBuffer);
    LOAD_GL_FUNC(glBufferData);

    LOAD_GL_FUNC(glCreateShader);
    LOAD_GL_FUNC(glDeleteShader);
    LOAD_GL_FUNC(glCompileShader);
    LOAD_GL_FUNC(glShaderSource);
    LOAD_GL_FUNC(glGetShaderiv);
    LOAD_GL_FUNC(glGetShaderInfoLog);

    LOAD_GL_FUNC(glDeleteProgram);
    LOAD_GL_FUNC(glCreateProgram);
    LOAD_GL_FUNC(glGetProgramiv);
    LOAD_GL_FUNC(glGetProgramInfoLog);
    LOAD_GL_FUNC(glLinkProgram);
    LOAD_GL_FUNC(glAttachShader);
    LOAD_GL_FUNC(glDetachShader);
    LOAD_GL_FUNC(glUseProgram);

    LOAD_GL_FUNC(glVertexAttribPointer);
    LOAD_GL_FUNC(glEnableVertexAttribArray);
    LOAD_GL_FUNC(glGenVertexArrays);
    LOAD_GL_FUNC(glBindVertexArray);

    LOAD_GL_FUNC(glGetUniformLocation);

    LOAD_GL_FUNC(glUniform1f);
    LOAD_GL_FUNC(glUniform2f);
    LOAD_GL_FUNC(glUniform3f);
    LOAD_GL_FUNC(glUniform4f);
    LOAD_GL_FUNC(glUniform1i);
    LOAD_GL_FUNC(glUniform2i);
    LOAD_GL_FUNC(glUniform3i);
    LOAD_GL_FUNC(glUniform4i);
    LOAD_GL_FUNC(glUniform1d);
    LOAD_GL_FUNC(glUniform2d);
    LOAD_GL_FUNC(glUniform3d);
    LOAD_GL_FUNC(glUniform4d);
    LOAD_GL_FUNC(glUniform1ui);
    LOAD_GL_FUNC(glUniform2ui);
    LOAD_GL_FUNC(glUniform3ui);
    LOAD_GL_FUNC(glUniform4ui);
    LOAD_GL_FUNC(glUniformMatrix2fv);
    LOAD_GL_FUNC(glUniformMatrix3fv);
    LOAD_GL_FUNC(glUniformMatrix4fv);

    LOAD_GL_FUNC(glBufferSubData);
    LOAD_GL_FUNC(glActiveTexture);
    LOAD_GL_FUNC(glGenerateMipmap);
  }

  void UnloadGLFunctions() {
    glDebugMessageCallback = nullptr;
    glDebugMessageControl = nullptr;
    glGenBuffers = nullptr;
    glBindBuffer = nullptr;
    glBufferData = nullptr;
    glCreateShader = nullptr;
    glCompileShader = nullptr;
    glShaderSource = nullptr;
    glGetShaderiv = nullptr;
    glGetShaderInfoLog = nullptr;
    glDeleteProgram = nullptr;
    glCreateProgram = nullptr;
    glGetProgramiv = nullptr;
    glGetProgramInfoLog = nullptr;
    glLinkProgram = nullptr;
    glAttachShader = nullptr;
    glDetachShader = nullptr;
    glUseProgram = nullptr;
    glDeleteShader = nullptr;
    glVertexAttribPointer = nullptr;
    glEnableVertexAttribArray = nullptr;
    glGenVertexArrays = nullptr;
    glBindVertexArray = nullptr;
    glGetUniformLocation = nullptr;
    glUniform1f = nullptr;
    glUniform2f = nullptr;
    glUniform3f = nullptr;
    glUniform4f = nullptr;
    glUniform1i = nullptr;
    glUniform2i = nullptr;
    glUniform3i = nullptr;
    glUniform4i = nullptr;
    glUniform1d = nullptr;
    glUniform2d = nullptr;
    glUniform3d = nullptr;
    glUniform4d = nullptr;
    glUniform1ui = nullptr;
    glUniform2ui = nullptr;
    glUniform3ui = nullptr;
    glUniform4ui = nullptr;
    glUniformMatrix2fv = nullptr;
    glUniformMatrix3fv = nullptr;
    glUniformMatrix4fv = nullptr;
    glBufferSubData = nullptr;
    glActiveTexture = nullptr;
    glGenerateMipmap = nullptr;
  }

}  // namespace GL
