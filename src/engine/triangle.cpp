#include "zero/triangle.hpp"

#include <GL/glew.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/sdl_video.h>

Triangle::Triangle() {
  verticies = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

  this->genBufferInfo();
}

Triangle::Triangle(const Triangle& triangle) {
  verticies = triangle.verticies;
  this->genBufferInfo();
}

Triangle& Triangle::operator=(const Triangle& triangle) {
  if (this == &triangle) {
    return *this;
  }

  verticies = triangle.verticies;
  this->genBufferInfo();

  return *this;
}

void Triangle::genBufferInfo() {
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(verticies.data()), verticies.data(), GL_STATIC_DRAW);
}