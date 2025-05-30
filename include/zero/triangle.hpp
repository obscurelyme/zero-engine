#ifndef ZERO_ENGINE_SHAPE_TRIANGLE_
#define ZERO_ENGINE_SHAPE_TRIANGLE_

#include <array>

#include "shader-program.hpp"

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
    std::shared_ptr<ShaderProgram> shaderProgram = nullptr;
};

#endif