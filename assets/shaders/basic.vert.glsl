#version 330 core

layout(location=0) in vec3 inPos;
layout(location=1) in vec3 inNor;
layout(location=2) in vec2 inUV;

out vec2 aUV;

uniform mat4 uModel;

void main() {
   gl_Position = uModel * vec4(inPos / 2, 1.0);
   aUV = inUV;
}