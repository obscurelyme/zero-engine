#ifndef ZERO_ENGINE_SHAPE_TRIANGLE_
#define ZERO_ENGINE_SHAPE_TRIANGLE_

#include <array>

#include "zero/iprocessable.hpp"
#include "zero/irenderable.hpp"
#include "zero/renderer.hpp"
#include "zero/shader-program.hpp"
#include "zero/texture.hpp"

class Triangle : public IRenderable, public IProcessable {
  public:
    Triangle();
    Triangle(const Triangle&);
    Triangle& operator=(const Triangle&);
    ~Triangle() noexcept override = default;
    std::array<float, 15> verticies;
    unsigned int vbo = 0;
    unsigned int vao = 0;

    void Process(float delta) override;
    void Render();
    void SubmitRender(Renderer& renderer) const override;
    void SetTexture(const Texture* texture);

  private:
    float xPos = 0;
    float yPos = 0;
    void genVertices();
    void genBufferInfo();
    const Texture* texture;
    std::shared_ptr<ShaderProgram> shaderProgram = nullptr;
    bool usingTexture = false;
};

#endif