#include "zero/shader-program.hpp"

#include <SDL3/SDL_opengl.h>

#include <stdexcept>

#include "zero/gl.hpp"

ShaderProgram::ShaderProgram() : infoLog(512) { program = GL::glCreateProgram(); }

void ShaderProgram::LinkProgram() {
  for (const auto& shader : shaders) {
    GL::glAttachShader(program, shader->Get());
  }
  GL::glLinkProgram(program);

  int success;
  GL::glGetProgramiv(program, GL_LINK_STATUS, &success);

  if (!success) {
    GL::glGetProgramInfoLog(program, GL_LINK_STATUS, nullptr, infoLog.data());
    throw std::runtime_error(std::string(infoLog.data()));
  }
}
