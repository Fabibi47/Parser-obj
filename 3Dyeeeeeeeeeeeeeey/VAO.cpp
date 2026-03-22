#pragma once
#include "VAO.h"
#include <iostream>
#include <vector>

VAO::VAO(std::vector<float> vertices, int verticeSize, int stride, GLenum drawType) : drawType(drawType), stride(stride), verticesNb(verticeSize) {
	glGenVertexArrays(1, &VAOid);
	glGenBuffers(1, &VBOid);
	
	glBindVertexArray(VAOid);
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	glBufferData(GL_ARRAY_BUFFER, verticesNb*sizeof(float), vertices.data(), drawType);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VAO::SetAttribute(int index, int size, int stride, int decal) {
	this->stride = stride;
	std::cout << verticesNb << std::endl;
	glBindVertexArray(VAOid);
	glBindBuffer(GL_ARRAY_BUFFER, VBOid);
	glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride * sizeof(float), (void*)(decal * sizeof(float)));
	glEnableVertexAttribArray(index);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void VAO::Draw() {
	glBindVertexArray(VAOid);
	glDrawArrays(GL_TRIANGLES, 0, verticesNb/stride); // diviser verticesNb par la stride des vertices
	glBindVertexArray(0);
}

VAO::~VAO() {
	glDeleteVertexArrays(1, &VAOid);
	glDeleteBuffers(1, &VBOid);
}