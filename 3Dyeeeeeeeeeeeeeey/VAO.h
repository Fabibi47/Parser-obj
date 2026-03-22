#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

class VAO
{
	unsigned int VAOid;
	unsigned int VBOid;
	int stride;
	int verticesNb;
	GLenum drawType;
public:
	VAO(std::vector<float> vertices, int verticeSize, int stride, GLenum drawType);
	~VAO();
	void SetAttribute(int index, int size, int stride, int decal);
	void Draw();
};

