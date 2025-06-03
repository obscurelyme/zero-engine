#include "zero/shader-program.hpp"

#include <SDL3/SDL_opengl.h>

#include <glm/ext/matrix_float2x2.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>
#include <stdexcept>

#include "zero/fs.hpp"
#include "zero/gl.hpp"
#include "zero/shader.hpp"

ShaderProgramBuilder ShaderProgramBuilder::AddShader(const ShaderProps& props) {
  shaderProps.push_back(props);
  return *this;
}

std::shared_ptr<ShaderProgram> ShaderProgramBuilder::Build() {
  std::shared_ptr<ShaderProgram> program = std::make_shared<ShaderProgram>();

  for (const auto& shaderProp : shaderProps) {
    std::string shaderSource = FS::ReadFile(shaderProp.shaderFile);
    std::shared_ptr<Shader> shader = std::make_shared<Shader>(shaderProp.shaderType, shaderSource);
    program->AttachShader(shader);
  }

  program->LinkProgram();

  return program;
}

ShaderProgram::ShaderProgram() : isBound(false), infoLog(512) { id = GL::glCreateProgram(); }

ShaderProgram::~ShaderProgram() {
  if (id != 0) {
    GL::glDeleteProgram(id);
  }
}

unsigned int ShaderProgram::Get() const { return id; }

void ShaderProgram::AttachShader(std::shared_ptr<Shader> shader) { shaders.push_back(shader); }

void ShaderProgram::LinkProgram() {
  for (const auto& shader : shaders) {
    GL::glAttachShader(id, shader->Get());
  }
  GL::glLinkProgram(id);

  int success;
  GL::glGetProgramiv(id, GL_LINK_STATUS, &success);

  if (!success) {
    GL::glGetProgramInfoLog(id, GL_LINK_STATUS, nullptr, infoLog.data());
    throw std::runtime_error(std::string(infoLog.data()));
  }

  shaders.clear();
}

void ShaderProgram::SetBool(const std::string& uniformName, bool value) {
  GL::glUniform1i(GL::glGetUniformLocation(id, uniformName.c_str()), (GLint)value);
}

void ShaderProgram::SetInt(const std::string& uniformName, GLint value) {
  GL::glUniform1i(GL::glGetUniformLocation(id, uniformName.c_str()), value);
}

void ShaderProgram::SetUInt(const std::string& uniformName, GLuint value) {
  GL::glUniform1ui(GL::glGetUniformLocation(id, uniformName.c_str()), value);
}

void ShaderProgram::SetFloat(const std::string& uniformName, GLfloat value) {
  GL::glUniform1f(GL::glGetUniformLocation(id, uniformName.c_str()), value);
}

void ShaderProgram::SetVec2f(const std::string& uniformName, GLfloat x, GLfloat y) {
  GL::glUniform2f(GL::glGetUniformLocation(id, uniformName.c_str()), x, y);
}

void ShaderProgram::SetVec3f(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z) {
  GL::glUniform3f(GL::glGetUniformLocation(id, uniformName.c_str()), x, y, z);
}

void ShaderProgram::SetVec4f(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w) {
  GL::glUniform4f(GL::glGetUniformLocation(id, uniformName.c_str()), x, y, z, w);
}

void ShaderProgram::SetVec2i(const std::string& uniformName, GLint x, GLint y) {
  GL::glUniform2i(GL::glGetUniformLocation(id, uniformName.c_str()), x, y);
}

void ShaderProgram::SetVec3i(const std::string& uniformName, GLint x, GLint y, GLint z) {
  GL::glUniform3i(GL::glGetUniformLocation(id, uniformName.c_str()), x, y, z);
}

void ShaderProgram::SetVec4i(const std::string& uniformName, GLint x, GLint y, GLint z, GLint w) {
  GL::glUniform4i(GL::glGetUniformLocation(id, uniformName.c_str()), x, y, z, w);
}

void ShaderProgram::SetVec2ui(const std::string& uniformName, GLuint x, GLuint y) {
  GL::glUniform2ui(GL::glGetUniformLocation(id, uniformName.c_str()), x, y);
}

void ShaderProgram::SetVec3ui(const std::string& uniformName, GLuint x, GLuint y, GLuint z) {
  GL::glUniform3ui(GL::glGetUniformLocation(id, uniformName.c_str()), x, y, z);
}

void ShaderProgram::SetVec4ui(const std::string& uniformName, GLuint x, GLuint y, GLuint z, GLuint w) {
  GL::glUniform4ui(GL::glGetUniformLocation(id, uniformName.c_str()), x, y, z, w);
}

void ShaderProgram::SetMat2f(const std::string& uniformName, const glm::mat2& value) {
  GL::glUniformMatrix2fv(GL::glGetUniformLocation(id, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::SetMat3f(const std::string& uniformName, const glm::mat3& value) {
  GL::glUniformMatrix3fv(GL::glGetUniformLocation(id, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}

void ShaderProgram::SetMat4f(const std::string& uniformName, const glm::mat4& value) {
  GL::glUniformMatrix4fv(GL::glGetUniformLocation(id, uniformName.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}