#include "zero/window.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_video.h>
#include <fmt/format.h>

#include <stdexcept>

Window::Window(const std::string& title, unsigned int width, unsigned int height) {
  this->window = SDL_CreateWindow(title.c_str(), width, height, windowFlags);

  if (this->window == nullptr) {
    std::string message = fmt::format("{}", SDL_GetError());
    throw std::runtime_error(message);
  }
}

Window::~Window() {
  if (this->window != nullptr) {
    SDL_DestroyWindow(this->window);
  }
}

SDL_Window* Window::GetWindow() const { return this->window; }