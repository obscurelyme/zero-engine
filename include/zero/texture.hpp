#ifndef ZERO_ENGINE_TEXTURE_
#define ZERO_ENGINE_TEXTURE_

#include <SDL3/SDL_opengl.h>

#include <string>


enum TextureWrapping {
  Repeat = GL_REPEAT,
  MirroredRepeat = GL_MIRRORED_REPEAT,
  ClampToEdge = GL_CLAMP_TO_EDGE,
  ClampToBorder = GL_CLAMP_TO_BORDER
};

class Texture {
  public:
    explicit Texture(const std::string& fileName);
    Texture(const Texture&);
    Texture& operator=(const Texture&);

    TextureWrapping Wrapping;

  private:
};

#endif