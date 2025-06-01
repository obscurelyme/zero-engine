#ifndef ZERO_ENGINE_IRENDERABLE_
#define ZERO_ENGINE_IRENDERABLE_

class Renderer;

class IRenderable {
  public:
    virtual void SubmitRender(Renderer& renderer) const = 0;
    virtual ~IRenderable() = default;
};

#endif