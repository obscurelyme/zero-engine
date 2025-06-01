#ifndef ZERO_ENGINE_GAME_OBJECT_
#define ZERO_ENGINE_GAME_OBJECT_

#include <memory>
#include <utility>

#include "iprocessable.hpp"
#include "irenderable.hpp"
#include "processable-manager.hpp"
#include "renderable-manager.hpp"


template <typename T, typename... Args>
std::shared_ptr<T> CreateGameObject(Args&&... args) {
  auto obj = std::make_shared<T>(std::forward<Args>(args)...);

  if (auto renderable = std::dynamic_pointer_cast<IRenderable>(obj)) {
    RenderableManager::AddRenderable(renderable);
  }
  if (auto processable = std::dynamic_pointer_cast<IProcessable>(obj)) {
    ProcessableManager::AddProcessable(processable);
  }

  return obj;
}

#endif