#ifndef ZERO_ENGINE_SHADER_PROGRAM_
#define ZERO_ENGINE_SHADER_PROGRAM_

#include "zero/shader.hpp"

class ShaderProgram {
  public:
    void LinkProgram();
    std::vector<Shader> shaders;
};

#endif