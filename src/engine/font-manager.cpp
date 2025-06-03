#include "zero/font-manager.hpp"

#include <SDL3/SDL_filesystem.h>
#include <SDL3/SDL_opengl.h>
#include <fmt/format.h>
#include <freetype/freetype.h>

#include <filesystem>
#include <glm/vec2.hpp>
#include <stdexcept>
#include <utility>

#include "zero/character.hpp"

FT_Library FontManager::ftLibrary = nullptr;

void FontManager::Init() {
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  int error = FT_Init_FreeType(&FontManager::ftLibrary);
  if (error) {
    std::string errString = fmt::format("{}", FT_Error_String(error));
    throw std::runtime_error(errString);
  }
}

void FontManager::LoadFont(const std::string &fontFilePath) {
  std::filesystem::path dir = SDL_GetBasePath();
  std::filesystem::path fullFilePath = dir / "assets" / fontFilePath;

  FT_Face face;
  int error = FT_New_Face(ftLibrary, fullFilePath.string().c_str(), 0, &face);

  if (error) {
    std::string errString = fmt::format("{}", FT_Error_String(error));
    throw std::runtime_error(errString);
  }

  FT_Set_Pixel_Sizes(face, 0, 48);

  characterLoop(face);

  FT_Done_Face(face);
}

void FontManager::characterLoop(FT_Face face) {
  for (unsigned char c = 0; c < 128; c++) {
    int error = FT_Load_Char(face, c, FT_LOAD_RENDER);

    if (error) {
      std::string message = fmt::format("{}", FT_Error_String(error));
      throw std::runtime_error(message);
    }

    // generate texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, face->glyph->bitmap.width, face->glyph->bitmap.rows, 0, GL_RED,
                 GL_UNSIGNED_BYTE, face->glyph->bitmap.buffer);
    // texture options
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Store character
    Character character = {texture, glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                           glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                           static_cast<unsigned int>(face->glyph->advance.x)};

    Zero::Characters.insert(std::pair<char, Character>(c, character));
  }
}