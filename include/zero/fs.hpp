#ifndef ZERO_ENGINE_FILESYSTEM_
#define ZERO_ENGINE_FILESYSTEM_

#include <SDL3/SDL.h>
#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_iostream.h>

#include <string>
#include <vector>

/**
 * @namespace FS
 * @brief Utility functions for file system operations.
 */
namespace FS {
  struct ImageProps {
      int width;
      int height;
      int channels;
      std::vector<unsigned char> data;
  };

  /**
   * Read a file into a string.
   * The file should exist within the `/assets` directory.
   */
  std::string ReadFile(const std::string& filePath);

  /**
   * Read an image into a buffer
   * The file should exist withing the `/assets` directory.
   */
  ImageProps LoadImageFile(const std::string& filePath);
}  // namespace FS

#endif