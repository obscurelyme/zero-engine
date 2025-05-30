#include "zero/triangle.hpp"

#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/sdl_video.h>

#include "zero/gl.hpp"
#include "zero/shader-program.hpp"

Triangle::Triangle() {
  verticies = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};

  ShaderProgramBuilder builder;

  shaderProgram = builder.AddShader({.shaderType = GL_VERTEX_SHADER, .shaderFile = "shaders/triangle.vert.glsl"})
                      .AddShader({.shaderType = GL_FRAGMENT_SHADER, .shaderFile = "shaders/triangle.frag.glsl"})
                      .Build();

  this->genBufferInfo();
}

Triangle::Triangle(const Triangle& triangle) {
  verticies = triangle.verticies;
  shaderProgram = triangle.shaderProgram;
}

Triangle& Triangle::operator=(const Triangle& triangle) {
  if (this == &triangle) {
    return *this;
  }

  verticies = triangle.verticies;
  shaderProgram = triangle.shaderProgram;

  return *this;
}

void Triangle::Render() {
  shaderProgram->Use();
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
