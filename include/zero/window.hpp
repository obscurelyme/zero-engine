#ifndef ZERO_ENGINE_WINDOW_
#define ZERO_ENGINE_WINDOW_

#include <SDL3/SDL_oldnames.h>
#include <SDL3/sdl_video.h>

#include <string>

class Window {
  public:
    Window(const std::string& title, unsigned int width, unsigned int height);
    Window(const Window&) = delete;  // NOTE: delete the copy constructor, we don't copy windows around here
    Window& operator=(const Window&) =
        delete;  // NOTE: delete the assignment operator, we don't reassign windows around here
    ~Window();

    SDL_Window* GetWindow() const;

  private:
    SDL_Window* window = nullptr;
    unsigned long long windowFlags = SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL | SDL_WINDOW_HIGH_PIXEL_DENSITY;
};

#endif