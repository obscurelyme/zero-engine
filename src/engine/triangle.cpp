#include "zero/triangle.hpp"

#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_timer.h>
#include <SDL3/sdl_video.h>

#include <cmath>

#include "zero/gl.hpp"
#include "zero/input-manager.hpp"
#include "zero/shader-program.hpp"

Triangle::Triangle() {
  ShaderProgramBuilder builder;

  shaderProgram = builder.AddShader(GL_VERTEX_SHADER, "shaders/triangle.vert.glsl")
                      ->AddShader(GL_FRAGMENT_SHADER, "shaders/triangle.frag.glsl")
                      ->Build();
  this->genVertices();
  this->genBufferInfo();
}

Triangle::Triangle(const Triangle& triangle) : verticies(triangle.verticies), shaderProgram(triangle.shaderProgram) {}

Triangle& Triangle::operator=(const Triangle& triangle) {
  if (this == &triangle) {
    return *this;
  }

  verticies = triangle.verticies;
  shaderProgram = triangle.shaderProgram;

  return *this;
}

void Triangle::Process(float delta) {
  const auto* input = InputManager::GetInput();

  if (input != nullptr) {
    if (input->key == SDLK_G) {
      usingTexture = true;
    }

    if (input->key == SDLK_H) {
      usingTexture = false;
    }

    if (input->key == SDLK_W) {
      yPos += 5.0 * delta;
    }
    if (input->key == SDLK_S) {
      yPos -= 5.0 * delta;
    }
    if (input->key == SDLK_A) {
      xPos -= 5.0 * delta;
    }
    if (input->key == SDLK_D) {
      xPos += 5.0 * delta;
    }
  }
}

void Triangle::SetTexture(const Texture* texturePtr) { texture = texturePtr; }

void Triangle::SubmitRender(Renderer& renderer) const {
  renderer.BindShader(shaderProgram);

  float redValue = (sin(SDL_GetTicks() / 1000.0f) / 2.0f) + 0.5f;

  shaderProgram->SetVec4f("ourColor", redValue, 0.0f, 0.0f, 1.0f);
  shaderProgram->SetVec2f("bPos", xPos, yPos);
  shaderProgram->SetBool("useTexture", usingTexture);
  GL::glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture->Get());
  GL::glBindVertexArray(vao);
  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Triangle::genVertices() {
  verticies = {-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,

               0.5f,  -0.5f, 0.0f, 1.0f, 0.0f,

               0.0f,  0.5f,  0.0f, 0.5f, 1.0f};
}

void Triangle::genBufferInfo() {
  GL::glGenVertexArrays(1, &vao);
  GL::glGenBuffers(1, &vbo);

  GL::glBindVertexArray(vao);

  GL::glBindBuffer(GL_ARRAY_BUFFER, vbo);
  GL::glBufferData(GL_ARRAY_BUFFER, sizeof(float) * verticies.size(), verticies.data(), GL_STATIC_DRAW);

  // position attribute
  GL::glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  GL::glEnableVertexAttribArray(0);
  // texture attribute
  GL::glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  GL::glEnableVertexAttribArray(1);

  GL::glBindBuffer(GL_ARRAY_BUFFER, 0);
  GL::glBindVertexArray(0);
}
