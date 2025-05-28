#ifndef ZERO_ENGINE_FILESYSTEM_
#define ZERO_ENGINE_FILESYSTEM_

#include <SDL3/SDL.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_iostream.h>

#include <string>

namespace FS {
  std::string ReadFile(const std::string& filePath);
}  // namespace FS

#endif