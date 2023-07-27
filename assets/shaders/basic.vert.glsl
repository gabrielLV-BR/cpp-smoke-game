#version 330 core

layout(location=0) in vec3 inPos;
layout(location=1) in vec3 inNor;
layout(location=2) in vec2 inUV;

out vec2 aUV;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProject;

void main() {
   gl_Position = uProject * uView * uModel * vec4(inPos / 2, 1.0);
   aUV = inUV;
}