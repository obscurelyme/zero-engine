#include "zero/text.hpp"

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_opengl.h>

#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/vector_float3.hpp>
#include <memory>

#include "zero/character.hpp"
#include "zero/gl.hpp"
#include "zero/renderer.hpp"
#include "zero/shader-program.hpp"

Text::Text(const std::string& str) : text(str), color(glm::vec3(0.0f, 0.0f, 0.0f)) {
  if (shader == nullptr) {
    createShader();
    genBufferData();
  }
}

Text::Text(const std::string& str, const glm::vec3& color) : text(str), color(color) {
  if (shader == nullptr) {
    createShader();
    genBufferData();
  }
}

Text::~Text() {}

void Text::SetPosition(float x, float y) {
  position.x = x;
  position.y = y;
}

void Text::SubmitRender(Renderer& renderer) const {
  float x = position.x;
  float y = position.y;
  renderer.BindShader(shader);
  shader->SetMat4f("projection", projection);
  shader->SetVec3f("textColor", color.x, color.y, color.z);

  GL::glActiveTexture(GL_TEXTURE0);
  GL::glBindVertexArray(vao);

  // iterate through all characters
  std::string::const_iterator c;
  for (c = text.begin(); c != text.end(); c++) {
    Character ch = Zero::Characters[*c];

    float xpos = x + ch.bearing.x * 1;
    float ypos = y - (ch.size.y - ch.bearing.y) * 1;

    float w = ch.size.x * 1;
    float h = ch.size.y * 1;
    // update VBO for each character
    float vertices[6][4] = {
        {xpos, ypos + h, 0.0f, 0.0f}, {xpos, ypos, 0.0f, 1.0f},     {xpos + w, ypos, 1.0f, 1.0f},

        {xpos, ypos + h, 0.0f, 0.0f}, {xpos + w, ypos, 1.0f, 1.0f}, {xpos + w, ypos + h, 1.0f, 0.0f}};
    // render glyph texture over quad
    glBindTexture(GL_TEXTURE_2D, ch.textureId);
    // update content of VBO memory
    GL::glBindBuffer(GL_ARRAY_BUFFER, vbo);
    GL::glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices),
                        vertices);  // be sure to use glBufferSubData and not glBufferData

    GL::glBindBuffer(GL_ARRAY_BUFFER, 0);
    // render quad
    glDrawArrays(GL_TRIANGLES, 0, 6);
    // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
    x += (ch.advance >> 6) * 1;  // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels
                                 // by 64 to get amount of pixels))
  }

  GL::glBindVertexArray(0);
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::ClearShader() { shader = nullptr; }

// void Text::Render(const std::string& text, float x, float y, glm::vec3 color) {}

void Text::createShader() {
  ShaderProgramBuilder builder;
  shader = builder.AddShader({GL_VERTEX_SHADER, "shaders/font.vert.glsl"})
               .AddShader({GL_FRAGMENT_SHADER, "shaders/font.frag.glsl"})
               .Build();
}

void Text::genBufferData() {
  GL::glGenVertexArrays(1, &vao);
  GL::glGenBuffers(1, &vbo);

  GL::glBindVertexArray(vao);
  GL::glBindBuffer(GL_ARRAY_BUFFER, vbo);

  GL::glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  GL::glEnableVertexAttribArray(0);
  GL::glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);

  GL::glBindBuffer(GL_ARRAY_BUFFER, 0);
  GL::glBindVertexArray(0);
}

unsigned int Text::vao = 0;
unsigned int Text::vbo = 0;
std::shared_ptr<ShaderProgram> Text::shader = nullptr;
// TODO: need to get the window's height and width instead somehow.
glm::mat4 Text::projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);