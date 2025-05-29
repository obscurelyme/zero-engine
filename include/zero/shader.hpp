#ifndef ZERO_ENGINE_SHADER_
#define ZERO_ENGINE_SHADER_

#include <SDL3/SDL_opengl.h>

#include <string>
#include <vector>

class Shader {
  public:
    Shader(GLenum shaderType, const std::string& sourceCode);
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    ~Shader();

    unsigned int Get() const;

  private:
    GLenum shaderType;
    std::string sourceCode;
    unsigned int shaderAddr;
    std::vector<char> infoLog;
};

#endif