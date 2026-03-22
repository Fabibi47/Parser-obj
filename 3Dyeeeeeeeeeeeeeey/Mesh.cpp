#pragma once
#include "Mesh.h"
#include "SubMesh.h"
#include <vector>
#include "Shader.h"

Mesh::Mesh() {}

Mesh::~Mesh() {
	for (auto kv : subMeshes) {
		delete kv.second;
	}
}

void Mesh::AddSubMesh(SubMesh* newSubMesh, std::string name) {
	if (subMeshes.contains(name)) {
		delete subMeshes[name];
	}
	subMeshes[name] = newSubMesh;
}

void Mesh::PopSubMesh(std::string name) {
	subMeshes.erase(name);
}

SubMesh* Mesh::getSubMesh(std::string name) {
	return subMeshes[name];
}

void Mesh::Draw(Shader* shader) {
	for (auto kv : subMeshes) {
		kv.second->Draw(shader);
	}
}