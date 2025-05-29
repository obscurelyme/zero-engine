#include "zero/triangle.hpp"

#include <SDL3/SDL_opengl.h>
#include <SDL3/sdl_video.h>

#include <memory>

#include "zero/fs.hpp"
#include "zero/gl.hpp"

Triangle::Triangle() {
  verticies = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
  vertexShaderFile = FS::ReadFile("shaders/triangle.vert.glsl");

  shader = std::make_shared<Shader>(GL_VERTEX_SHADER, vertexShaderFile);
}

Triangle::Triangle(const Triangle& triangle) {
  verticies = triangle.verticies;
  vertexShaderFile = triangle.vertexShaderFile;
  shader = triangle.shader;
}

Triangle& Triangle::operator=(const Triangle& triangle) {
  if (this == &triangle) {
    return *this;
  }

  verticies = triangle.verticies;
  vertexShaderFile = triangle.vertexShaderFile;
  shader = triangle.shader;

  return *this;
}

void Triangle::Render() { this->genBufferInfo(); }

void Triangle::genBufferInfo() {
  GL::glGenBuffers(1, &vbo);
  GL::glBindBuffer(GL_ARRAY_BUFFER, vbo);
  GL::glBufferData(GL_ARRAY_BUFFER, sizeof(verticies.data()), verticies.data(), GL_STATIC_DRAW);
}
