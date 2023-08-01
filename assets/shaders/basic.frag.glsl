#version 330 core

in vec2 aUV;
in vec3 aNor;
out vec4 outColor;

uniform float uTime;
uniform sampler2D uTexture;

void main() {
   outColor = texture(uTexture, aNor.xy);
}