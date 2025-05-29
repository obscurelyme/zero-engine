#include "zero/triangle.hpp"

#include <SDL3/SDL_opengl.h>
#include <SDL3/sdl_video.h>

#include <memory>

#include "zero/fs.hpp"
#include "zero/gl.hpp"

Triangle::Triangle() {
  verticies = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

  vertexShaderFile = FS::ReadFile("shaders/triangle.vert.glsl");
  fragmentShaderFile = FS::ReadFile("shaders/triangle.frag.glsl");

  vertexShader = std::make_shared<Shader>(GL_VERTEX_SHADER, vertexShaderFile);
  fragmentShader = std::make_shared<Shader>(GL_FRAGMENT_SHADER, fragmentShaderFile);

  shaderProgram.AttachShader(vertexShader);
  shaderProgram.AttachShader(fragmentShader);
  shaderProgram.LinkProgram();

  this->genBufferInfo();
}

Triangle::Triangle(const Triangle& triangle) {
  verticies = triangle.verticies;
  vertexShaderFile = triangle.vertexShaderFile;
  vertexShader = triangle.vertexShader;
  fragmentShader = triangle.fragmentShader;
}

Triangle& Triangle::operator=(const Triangle& triangle) {
  if (this == &triangle) {
    return *this;
  }

  verticies = triangle.verticies;
  vertexShaderFile = triangle.vertexShaderFile;
  vertexShader = triangle.vertexShader;
  fragmentShader = triangle.fragmentShader;

  return *this;
}

void Triangle::Render() {
  this->shaderProgram.Use();
  GL::glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::genBufferInfo() {
  GL::glGenVertexArrays(1, &vao);
  GL::glGenBuffers(1, &vbo);

  GL::glBindVertexArray(vao);

  GL::glBindBuffer(GL_ARRAY_BUFFER, vbo);
  GL::glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticies.size(), verticies.data(), GL_STATIC_DRAW);

  GL::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  GL::glEnableVertexAttribArray(0);

  GL::glBindBuffer(GL_ARRAY_BUFFER, 0);
  GL::glBindVertexArray(0);
}
