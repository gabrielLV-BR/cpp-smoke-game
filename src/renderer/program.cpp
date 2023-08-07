#include "./program.hpp"

#include <string>
#include <unordered_map>
#include <iostream>
#include <exception>

#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "glad/glad.h"

Program::Program(Shader vertex, Shader fragment) : handle(glCreateProgram()) {
    std::cout << "Creating program\n";
    glAttachShader(handle, vertex.handle);
    glAttachShader(handle, fragment.handle);
    glLinkProgram(handle);

    _CheckForErrors();
}

Program::~Program() {
    glDeleteProgram(handle);
}

void Program::Bind() {
    glUseProgram(handle);
}

void Program::Unbind() {
    glUseProgram(0);
}

int Program::GetUniformLocation(const std::string& name) const {
    return glGetUniformLocation(handle, name.c_str());
}

void Program::_InternalSetUniform(int location, int value) {
    glUniform1i(location, value);
}

void Program::_InternalSetUniform(int location, float value) {
    glUniform1f(location, value);
}

void Program::_InternalSetUniform(int location, const Texture& t) {
    glUniform1i(location, t.handle);
}

void Program::_CheckForErrors() {
    GLint status;
    glGetProgramiv(handle, GL_LINK_STATUS, &status);

    if (status == GL_FALSE) {
        throw std::runtime_error("[ERROR] Error linking program");
    }

    glValidateProgram(handle);
    glGetProgramiv(handle, GL_VALIDATE_STATUS, &status);

    if (status == GL_FALSE) {
        char log[1024];
        glGetProgramInfoLog(handle, 1024, nullptr, log);
        throw std::runtime_error(log);
    }

    // switch(glGetError()) {
    //   case GL_INVALID_ENUM: {
    //     throw std::runtime_error("[ERROR] Error creating program!
    //     <INVALID_ENUM>"); break;
    //   }
    //   case GL_INVALID_VALUE: {
    //     throw std::runtime_error("[ERROR] Error creating program!
    //     <INVALID_VALUE>"); break;
    //   }
    //   case GL_INVALID_OPERATION: {
    //     throw std::runtime_error("[ERROR] Error creating program!
    //     <INVALID_OPERATION>"); break;
    //   }
    //   case GL_OUT_OF_MEMORY: {
    //     throw std::runtime_error("[ERROR] Error creating program!
    //     <OUT_OF_MEMORY>"); break;
    //   }
    //   case GL_INVALID_FRAMEBUFFER_OPERATION: {
    //     throw std::runtime_error("[ERROR] Error creating program!
    //     <INVALID_FRAMEBUFFER_OPERATION>"); break;
    //   }
    //   default: {
    //     std::cout << "No errors while creating program\n";
    //   }
    // }
}