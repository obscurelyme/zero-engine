#include "zero/texture.hpp"

#include <SDL3/SDL_opengl.h>

#include "zero/fs.hpp"
#include "zero/gl.hpp"

Texture::Texture(const std::string& fileName, const TextureWrapping& wrapping) : wrapping(wrapping), textureId(0) {
  properties = FS::LoadImageFile(fileName);
  glGenTextures(1, &textureId);
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, static_cast<int>(wrapping));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, static_cast<int>(wrapping));
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, properties.width, properties.height, 0, GL_RGB, GL_UNSIGNED_BYTE,
               properties.data.data());
  GL::glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
}

GLenum Texture::Get() const { return textureId; }