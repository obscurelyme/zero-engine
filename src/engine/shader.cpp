#include "zero/shader.hpp"

#include <stdexcept>

#include "zero/gl.hpp"

Shader::Shader(GLenum shaderType, const std::string& sourceCode) : infoLog(512) {
  this->sourceCode = sourceCode;
  this->shaderAddr = GL::glCreateShader(shaderType);

  const char* source = sourceCode.c_str();
  GL::glShaderSource(this->shaderAddr, 1, &source, nullptr);
  GL::glCompileShader(this->shaderAddr);

  int success;
  GL::glGetShaderiv(this->shaderAddr, GL_COMPILE_STATUS, &success);

  if (!success) {
    GL::glGetShaderInfoLog(this->shaderAddr, 512, nullptr, infoLog.data());
    throw std::runtime_error(std::string(infoLog.data()));
  }
}

Shader::~Shader() {
  if (shaderAddr != 0) {
    GL::glDeleteShader(shaderAddr);
  }
}

unsigned int Shader::Get() const { return this->shaderAddr; }