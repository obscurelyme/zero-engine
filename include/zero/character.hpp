#ifndef ZERO_ENGINE_FONT_CHARACTER_
#define ZERO_ENGINE_FONT_CHARACTER_

#include <glm/ext/vector_int2.hpp>
#include <glm/vec2.hpp>
#include <map>

struct Character {
    unsigned int textureId;
    glm::ivec2 size;
    glm::ivec2 bearing;
    unsigned int advance;
};

namespace Zero {
  extern std::map<char, Character> Characters;
}

#endif