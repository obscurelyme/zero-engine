#include "zero/shader.hpp"

#include <stdexcept>

#include "zero/gl.hpp"

Shader::Shader(GLenum shaderType, const std::string& sourceCode) : infoLog(512) {
  this->sourceCode = sourceCode;
  this->id = GL::glCreateShader(shaderType);

  const char* source = sourceCode.c_str();
  GL::glShaderSource(this->id, 1, &source, nullptr);
  GL::glCompileShader(this->id);

  int success;
  GL::glGetShaderiv(this->id, GL_COMPILE_STATUS, &success);

  if (!success) {
    GL::glGetShaderInfoLog(this->id, 512, nullptr, infoLog.data());
    throw std::runtime_error(std::string(infoLog.data()));
  }
}

Shader::~Shader() {
  if (id != 0) {
    GL::glDeleteShader(id);
  }
}

unsigned int Shader::Get() const { return this->id; }