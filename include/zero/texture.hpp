#ifndef ZERO_ENGINE_TEXTURE_
#define ZERO_ENGINE_TEXTURE_

#include <SDL3/SDL_opengl.h>

#include <string>

#include "fs.hpp"

enum class TextureWrapping : unsigned int {
  Repeat = GL_REPEAT,
  MirroredRepeat = GL_MIRRORED_REPEAT,
  ClampToEdge = GL_CLAMP_TO_EDGE,
  ClampToBorder = GL_CLAMP_TO_BORDER
};

class Texture {
  public:
    Texture() = delete;
    Texture(const std::string& fileName, const TextureWrapping& wrapping);
    Texture(const Texture&) = default;
    Texture& operator=(const Texture&) = default;

    [[nodiscard]] GLenum Get() const;

  private:
    TextureWrapping wrapping;
    FS::ImageProps properties;
    GLenum textureId;
};

#endif