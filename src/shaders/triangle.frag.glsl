#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform vec4 ourColor;
uniform sampler2D ourTexture;
uniform bool useTexture;

void main() {
  if (useTexture) {
    FragColor = texture(ourTexture, TexCoords);
    return;
  }

  FragColor = ourColor;
}