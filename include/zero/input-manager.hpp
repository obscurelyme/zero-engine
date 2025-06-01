#ifndef ZERO_ENGINE_INPUT_MANAGER_
#define ZERO_ENGINE_INPUT_MANAGER_

#include <SDL3/SDL_events.h>

class InputManager {
  public:
    /**
     * Returns the keyboard input event for the current frame.
     */
    static const SDL_KeyboardEvent* GetInput();
    static void SetInput(SDL_KeyboardEvent event);

  private:
    static SDL_KeyboardEvent currentFrameEvent;
};

#endif