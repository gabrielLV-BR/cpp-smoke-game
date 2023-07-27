#version 330 core

layout(location=0) in vec3 inPos;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProject;

void main() {
   gl_Position = uProject * uView * uModel * vec4(inPos / 2, 1.0);
}