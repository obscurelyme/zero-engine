#ifndef ZERO_ENGINE_FONT_
#define ZERO_ENGINE_FONT_

#include <ft2build.h>

#include <string>

#include FT_FREETYPE_H

class FontManager {
  public:
    static void Init();
    static void LoadFont(const std::string& fontName);

  private:
    static void characterLoop(FT_Face face);

    static FT_Library ftLibrary;
};

#endif