#pragma once
#include "Texture.h"
#include "stb_image.h"
#include <iostream>

Texture::Texture(const char* path, GLint wrapMode, GLint filter) {
	glGenTextures(1, &id);
    // un ptit WRRRRAP
    Wrap(wrapMode);
    // 3xfiltré
    Filter(filter);
    // Load
    Load(path);
}

void Texture::Bind() {
    glBindTexture(GL_TEXTURE_2D, id);
}

void Texture::Unbind() {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Wrap(GLint fillMode) {
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, fillMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, fillMode);
    Unbind();
}

void Texture::Filter(GLint filter) {
    Bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
    Unbind();
}

void Texture::Load(const char* path) {
    Bind();
    int width, height, nbChannels;
    unsigned char* data = stbi_load(path, &width, &height, &nbChannels, 0);
    if (data) {
        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
        if (nbChannels == 3) {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        }
        else {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        }
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        std::cout << "Failed to load image" << std::endl;
    }
    stbi_image_free(data);
    Unbind();
}

void Texture::Use(int id) {
    glActiveTexture(GL_TEXTURE0 + id);
    Bind();
}