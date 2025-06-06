#include <SDL3/SDL_filesystem.h>
#include <fmt/format.h>

#include <algorithm>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <filesystem>
#include <vector>

#include "zero/fs.hpp"

std::string FS::ReadFile(const std::string& filePath) {
  std::filesystem::path dir = SDL_GetBasePath();
  std::filesystem::path fullFilePath = dir / "assets" / filePath;

  auto* stream = SDL_IOFromFile(fullFilePath.string().c_str(), "r");
  auto fileSize = SDL_GetIOSize(stream);

  std::vector<char> buffer(fileSize + 1);  // NOTE: leave room for Jesus...I mean null terminating char.

  SDL_ReadIO(stream, buffer.data(), fileSize);
  SDL_CloseIO(stream);
  buffer[fileSize] = '\0';  // NOTE: ensure null termination char so that string creation knows where to end.

  return std::string{buffer.data()};
}

FS::ImageProps FS::LoadImageFile(const std::string& filePath) {
  std::filesystem::path dir = SDL_GetBasePath();
  std::filesystem::path fullFilePath = dir / "assets" / filePath;

  int width;
  int height;
  int channels;
  unsigned char* data = nullptr;

  data = stbi_load(fullFilePath.string().c_str(), &width, &height, &channels, 0);

  if (data == nullptr) {
    throw std::runtime_error(fmt::format("Unabled to read image file {}", filePath));
  }

  size_t dataSize = width * height * channels;

  std::vector<unsigned char> buffer(data, data + dataSize);
  stbi_image_free(data);

  return {.width = width, .height = height, .channels = channels, .data = std::move(buffer)};
}