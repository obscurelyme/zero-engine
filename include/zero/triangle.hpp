#ifndef ZERO_ENGINE_SHAPE_TRIANGLE_
#define ZERO_ENGINE_SHAPE_TRIANGLE_

#include <array>
#include <memory>
#include <string>

#include "shader-program.hpp"
#include "zero/shader.hpp"

class Triangle {
  public:
    Triangle();
    Triangle(const Triangle&);
    Triangle& operator=(const Triangle&);
    ~Triangle() = default;
    std::array<float, 9> verticies;
    unsigned int vbo = 0;
    unsigned int vao = 0;

    void Render();

  private:
    void genBufferInfo();
    std::string vertexShaderFile = "";
    std::string fragmentShaderFile = "";
    std::shared_ptr<Shader> vertexShader = nullptr;
    std::shared_ptr<Shader> fragmentShader = nullptr;
    ShaderProgram shaderProgram;
};

#endif