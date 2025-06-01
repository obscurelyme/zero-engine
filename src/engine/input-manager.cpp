#include "zero/input-manager.hpp"

#include <SDL3/SDL_events.h>

SDL_KeyboardEvent InputManager::currentFrameEvent{};

const SDL_KeyboardEvent* InputManager::GetInput() {
  if (currentFrameEvent.type == SDL_EVENT_KEY_DOWN || currentFrameEvent.type == SDL_EVENT_KEY_UP) {
    return &currentFrameEvent;
  }

  return nullptr;
}

void InputManager::SetInput(SDL_KeyboardEvent event) { currentFrameEvent = event; }