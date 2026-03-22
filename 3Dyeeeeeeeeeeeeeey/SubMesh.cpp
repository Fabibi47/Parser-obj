#include "SubMesh.h"
#include "VAO.h"
#include "Material.h"
#include "Shader.h"

SubMesh::SubMesh() {}

SubMesh::SubMesh(std::vector<float> all, int verticeSize, bool textured, Material* material) : all(all), verticeSize(verticeSize), textured(textured), material(material) {
	vao = GenerateVao();
}

VAO* SubMesh::GenerateVao() {
	int stride = textured ? 8 : 6;
	vao = new VAO(all, verticeSize, stride, GL_STATIC_DRAW);
	vao->SetAttribute(0, 3, stride, 0);
	vao->SetAttribute(1, 2, stride, 3);
	if (textured)
		vao->SetAttribute(2, 3, stride, 5);
	return vao;
}

VAO* SubMesh::getVao() {
	return vao;
}

std::vector<float> SubMesh::getVertice() {
	return all;
}

void SubMesh::Draw(Shader* shader) {
	material->Use();
	shader->SetMaterial("material", *material);
	shader->Use();
	vao->Draw();
	shader->Shutdown();
}

void SubMesh::SetMaterial(Material* material) {
	this->material = material;
}

void SubMesh::setVertice(std::vector<float> newVertice) {
	all = newVertice;
	verticeSize = all.size();
}

void SubMesh::SetTextured(bool textured) {
	this->textured = textured;
}

bool SubMesh::isTextured() {
	return textured;
}