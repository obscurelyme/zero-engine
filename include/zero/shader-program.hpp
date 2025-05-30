#ifndef ZERO_ENGINE_SHADER_PROGRAM_
#define ZERO_ENGINE_SHADER_PROGRAM_

#include <SDL3/SDL_opengl.h>

#include <memory>
#include <vector>

#include "zero/shader.hpp"

class ShaderProgram;

/**
 * Builder class that accepts a number of shader source files. When build is invokes, this builder
 * will read in the files and create a new ShaderProgram with the compiled shaders.
 */
class ShaderProgramBuilder {
  public:
    ShaderProgramBuilder() = default;
    ~ShaderProgramBuilder() = default;

    ShaderProgramBuilder AddShaderFile(const std::string& shaderFile);

    ShaderProgram Build();

  private:
    std::vector<std::string> shaderFiles;
};

class ShaderProgram {
  public:
    ShaderProgram();
    ~ShaderProgram();

    void Use();
    void AddShader();
    void AttachShader(std::shared_ptr<Shader> shader);
    void LinkProgram();

    void SetBool(const std::string& uniformName, bool value);
    void SetInt(const std::string& uniformName, GLint value);
    void SetUInt(const std::string& uniformName, GLuint value);
    void SetFloat(const std::string& uniformName, GLfloat value);

    void SetVec2i(const std::string& uniformName, GLint x, GLint y);
    void SetVec3i(const std::string& uniformName, GLint x, GLint y, GLint z);
    void SetVec4i(const std::string& uniformName, GLint x, GLint y, GLint z, GLint w);

    void SetVec2ui(const std::string& uniformName, GLuint x, GLuint y);
    void SetVec3ui(const std::string& uniformName, GLuint x, GLuint y, GLuint z);
    void SetVec4ui(const std::string& uniformName, GLuint x, GLuint y, GLuint z, GLuint w);

    void SetVec2f(const std::string& uniformName, GLfloat x, GLfloat y);
    void SetVec3f(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z);
    void SetVec4f(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

    // void SetMatrix2f(const std::string& uniformName, GLfloat x, GLfloat y);
    // void SetMatrix3f(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z);
    // void SetMatrix4f(const std::string& uniformName, GLfloat x, GLfloat y, GLfloat z, GLfloat w);

    std::vector<std::shared_ptr<Shader>> shaders{};
    unsigned int id;
    std::vector<char> infoLog;
};

#endif