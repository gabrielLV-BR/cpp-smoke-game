#version 330 core

in vec2 aUV;
out vec4 outColor;

uniform float uTime;

void main() {
//   outColor = vec4(1.0, sin(uTime), 0.0, 1.0);
   outColor = vec4(aUV, 1.0, 1.0);
}