#ifndef ZERO_ENGINE_SHAPE_TRIANGLE_
#define ZERO_ENGINE_SHAPE_TRIANGLE_

#include <array>

class Triangle {
  public:
    Triangle();
    Triangle(const Triangle&);
    Triangle& operator=(const Triangle&);
    std::array<float, 9> verticies;
    unsigned int vbo;

  private:
    void genBufferInfo();
};

#endif