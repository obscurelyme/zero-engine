#ifndef ZERO_ENGINE_TEXT_
#define ZERO_ENGINE_TEXT_

#include <glm/mat4x4.hpp>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <memory>

#include "shader-program.hpp"
#include "zero/irenderable.hpp"

/**
 * Quick and dirty static class to render text on the
 * screen.
 */
class Text : public IRenderable {
  public:
    Text() = delete;
    ~Text();
    explicit Text(const std::string&);
    Text(const std::string&, const glm::vec3&);
    void SubmitRender(Renderer& renderer) const override;
    void SetPosition(float x, float y);

    static void ClearShader();

  private:
    std::string text;
    glm::vec3 color;
    glm::vec2 position;

    static void createShader();
    static void genBufferData();
    static std::shared_ptr<ShaderProgram> shader;
    static glm::mat4 projection;
    static unsigned int vao;
    static unsigned int vbo;
};

#endif