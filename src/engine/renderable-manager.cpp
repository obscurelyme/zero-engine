#include <algorithm>
#include <memory>
#include <vector>
#include <zero/renderable-manager.hpp>

#include "zero/irenderable.hpp"

std::vector<std::weak_ptr<IRenderable>> RenderableManager::renderables{};

void RenderableManager::AddRenderable(const std::shared_ptr<IRenderable>& renderable) {
  renderables.push_back(renderable);
}

std::vector<std::weak_ptr<IRenderable>>& RenderableManager::GetRenderables() { return renderables; }

void RenderableManager::CleanRenderables() {
  renderables.erase(std::remove_if(renderables.begin(), renderables.end(),
                                   [](const std::weak_ptr<IRenderable>& wkptr) { return wkptr.expired(); }),
                    renderables.end());
}