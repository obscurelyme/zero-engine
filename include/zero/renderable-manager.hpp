#ifndef ZERO_ENGINE_RENDERABLE_MANAGER_
#define ZERO_ENGINE_RENDERABLE_MANAGER_

#include <memory>
#include <vector>

#include "zero/irenderable.hpp"

class RenderableManager {
  public:
    static void CleanRenderables();
    static void AddRenderable(const std::shared_ptr<IRenderable>& renderable);
    static std::vector<std::weak_ptr<IRenderable>>& GetRenderables();

  private:
    static std::vector<std::weak_ptr<IRenderable>> renderables;

    RenderableManager() = default;
    RenderableManager(const RenderableManager&) = delete;
    RenderableManager& operator=(const RenderableManager&) = delete;
};

#endif