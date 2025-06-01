#include "zero/triangle.hpp"

#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/sdl_video.h>

#include <cmath>

#include "zero/gl.hpp"
#include "zero/input-manager.hpp"
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

void Triangle::Process(float delta) {
  auto input = InputManager::GetInput();

  if (input != nullptr) {
    if (input->key == SDLK_W) {
      yPos += 1.0 * delta;
    }
    if (input->key == SDLK_S) {
      yPos -= 1.0 * delta;
    }
  }
}

void Triangle::SubmitRender(Renderer& renderer) const {
  renderer.BindShader(shaderProgram);

  float redValue = sin(SDL_GetTicks() / 1000.0f) / 2.0f + 0.5f;

  shaderProgram->SetVec4f("ourColor", redValue, 0.0f, 0.0f, 1.0f);
  shaderProgram->SetVec2f("bPos", 0.0f, yPos);

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
