#include "zero/fs.hpp"

#include <filesystem>
#include <vector>

std::string FS::ReadFile(const std::string &filePath) {
  std::filesystem::path dir = SDL_GetBasePath();
  std::filesystem::path fullFilePath = dir / filePath;

  auto stream = SDL_IOFromFile(fullFilePath.string().c_str(), "r");
  auto fileSize = SDL_GetIOSize(stream);

  std::vector<char> buffer(fileSize + 1);  // NOTE: add room for Jesus...I mean null terminating char.

  SDL_ReadIO(stream, buffer.data(), fileSize);
  SDL_CloseIO(stream);
  buffer[fileSize] = '\0';  // NOTE: ensure null termination char so that string creation knows where to end.

  return std::string(buffer.data());
}