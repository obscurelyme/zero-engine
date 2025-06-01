#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec2 bPos;
 
void main() {
  gl_Position = vec4(aPos.x + bPos.x, aPos.y + bPos.y, aPos.z, 1.0);
}