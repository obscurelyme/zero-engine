#ifndef ZERO_ENGINE_SHADER_PROGRAM_
#define ZERO_ENGINE_SHADER_PROGRAM_

#include <memory>
#include <vector>

#include "zero/shader.hpp"

class ShaderProgram {
  public:
    ShaderProgram();
    void LinkProgram();
    std::vector<std::shared_ptr<Shader>> shaders{};
    unsigned int program;
    std::vector<char> infoLog;
};

#endif