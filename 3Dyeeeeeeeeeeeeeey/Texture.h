#pragma once
#include <glad/glad.h>

class Texture
{
public:
	unsigned int id;
	Texture(const char* path, GLint wrapMode = GL_REPEAT, GLint filter = GL_LINEAR);
	void Bind();
	void Unbind();
	void Wrap(GLint fillMode);
	void Filter(GLint filter);
	void Load(const char* path);
	void Use(int id);
};