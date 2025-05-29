#ifndef ZERO_ENGINE_FILESYSTEM_
#define ZERO_ENGINE_FILESYSTEM_

#include <SDL3/SDL.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_iostream.h>

#include <string>

/**
 * @namespace FS
 * @brief Utility functions for file system operations.
 */
namespace FS {
  /**
   * Read a file into a string.
   * The file should exist within the `/assets` directory.
   */
  std::string ReadFile(const std::string& filePath);
}  // namespace FS

#endif