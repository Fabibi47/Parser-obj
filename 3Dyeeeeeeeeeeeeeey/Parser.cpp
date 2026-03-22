#pragma once
#include "Parser.h"
#include <iostream>
#include <fstream>
#include <sstream>*
#include <map>
#include "Mesh.h"
#include "SubMesh.h"
#include "Material.h"
#include "Texture.h"

Parser::Parser() {}

Mesh* Parser::ParseMesh(const char* path) {
	try {
		Mesh* Object = new Mesh();
		std::ifstream objFile;

		objFile.open(path);
		std::string currentName = " ";
		std::string line;
		std::vector<float> vertice;
		std::vector<float> textureVertice;
		std::vector<float> normalVertice;
		std::vector<float> orderedVertice;

		SubMesh* currentSubMesh = new SubMesh();

		bool isVT = false;
		bool isVN = false;
		while (std::getline(objFile, line)) {
			std::string type;
			std::stringstream lineStream(line);
			lineStream >> type;
			if (type == "v") {
				float v1, v2, v3;
				lineStream >> v1 >> v2 >> v3;
				vertice.push_back(v1);
				vertice.push_back(v2);
				vertice.push_back(v3);
			}
			else if (type == "vt") {
				isVT = true;
				float v1, v2;
				lineStream >> v1 >> v2;
				textureVertice.push_back(v1);
				textureVertice.push_back(v2);
			}
			else if (type == "vn") {
				isVN = true;
				float v1, v2, v3;
				lineStream >> v1 >> v2 >> v3;
				normalVertice.push_back(v1);
				normalVertice.push_back(v2);
				normalVertice.push_back(v3);
			}
			else if (type == "f") {
				if (isVT) {
					do {
						std::string id;
						lineStream >> id;
						std::stringstream idStream(id);
						std::string value;
						int count = 0;
						while (std::getline(idStream, value, '/')) {
							std::stringstream valueStream(value);
							int v;
							valueStream >> v;
							if (v != 0) {
								if (count == 0) {
									orderedVertice.push_back(vertice[(v - 1) * 3]);
									orderedVertice.push_back(vertice[(v - 1) * 3+1]);
									orderedVertice.push_back(vertice[(v - 1) * 3+2]);
								}
								else if (count == 1 && value.size() > 0){
									orderedVertice.push_back(textureVertice[(v - 1) * 2]);
									orderedVertice.push_back(textureVertice[(v - 1) * 2+1]);
								}
								else {
									orderedVertice.push_back(normalVertice[(v - 1) * 3]);
									orderedVertice.push_back(normalVertice[(v - 1) * 3+1]);
									orderedVertice.push_back(normalVertice[(v - 1) * 3+2]);
								}
							}
							count++;
						}
					} while (!lineStream.eof());
				}
				else {
					int v1, v2, v3;
					lineStream >> v1 >> v2 >> v3;
					orderedVertice.push_back(vertice[(v1-1)*3]);
					orderedVertice.push_back(vertice[(v1-1)*3+1]);
					orderedVertice.push_back(vertice[(v1-1)*3+2]);
					orderedVertice.push_back(vertice[(v2-1)*3]);
					orderedVertice.push_back(vertice[(v2-1)*3+1]);
					orderedVertice.push_back(vertice[(v2-1)*3+2]);
					orderedVertice.push_back(vertice[(v3-1)*3]);
					orderedVertice.push_back(vertice[(v3-1)*3+1]);
					orderedVertice.push_back(vertice[(v3-1)*3+2]);
				}
			}
			else if (type == "o" || type == "g") {
				if (orderedVertice.size() > 0) {
					std::vector<float> verticeToAdd = ConfirmVertice(orderedVertice, isVN);
					currentSubMesh->setVertice(verticeToAdd);
					currentSubMesh->SetTextured(isVT);
					currentSubMesh->GenerateVao();
					Object->AddSubMesh(currentSubMesh, currentName);
					currentSubMesh = new SubMesh();
					orderedVertice.clear();
				}
				std::string name;
				lineStream >> name;
				currentName = name;
			}
			else if (type == "mtllib") {
				std::string materialPath;
				lineStream >> materialPath;
				ParseMaterials(materialPath, Object);
			}
			else if (type == "usemtl") {
				std::string materialName;
				lineStream >> materialName;
				currentSubMesh->SetMaterial(Object->materials[materialName]);
			}
		}

		std::vector<float> verticeToAdd = ConfirmVertice(orderedVertice, isVN);
		currentSubMesh->setVertice(verticeToAdd);
		currentSubMesh->SetTextured(isVT);
		currentSubMesh->GenerateVao();
		Object->AddSubMesh(currentSubMesh, currentName);

		objFile.close();

		return Object;
	}
	catch (std::ifstream::failure& e) {
		std::cout << "problemo parsando l'objeto : \n" << e.what() << std::endl;
	}
}

void Parser::ParseMaterials(std::string path, Mesh* mesh) {
	try {

		std::ifstream mtlFile;

		mtlFile.open(path);

		std::string line;
		std::string currentName;
		Material* currentMaterial = new Material();
		
		while (std::getline(mtlFile, line)) {
			std::string type;
			std::stringstream linestream(line);
			linestream >> type;
			if (type == "newmtl") {
				currentMaterial = new Material();
				linestream >> currentName;
				mesh->materials[currentName] = currentMaterial;
			}
			else if (type == "Kd") {
				float v1, v2, v3;
				linestream >> v1 >> v2 >> v3;
				currentMaterial->diffuse = glm::vec3(v1, v2, v3);
			}
			else if (type == "map_Kd") {
				std::string path;
				linestream >> path;
				currentMaterial->diffuseTex = new Texture(path.c_str());
			}
			else if (type == "Ka") {
				float v1, v2, v3;
				linestream >> v1 >> v2 >> v3;
				currentMaterial->ambient = glm::vec3(v1, v2, v3);
			}
			else if (type == "map_Ka") {
				std::string path;
				linestream >> path;
				currentMaterial->ambientTex = new Texture(path.c_str());
			}
			else if (type == "Ks") {
				float v1, v2, v3;
				linestream >> v1 >> v2 >> v3;
				currentMaterial->specular = glm::vec3(v1, v2, v3);
			}
			else if (type == "map_Ks") {
				std::string path;
				linestream >> path;
				currentMaterial->specularTex = new Texture(path.c_str());
			}
			else if (type == "Ns") {
				float value;
				linestream >> value;
				currentMaterial->shininess = value;
			}
		}
	}
	catch (std::ifstream::failure& e) {
		std::cout << "problemo parsando le materio : \n" << e.what() << std::endl;
	}
}

std::vector<float> Parser::GenerateNormals(std::vector<float> vertice, bool textured) {
	std::cout << textured << std::endl;
	int jump = textured ? 5 : 3;
	std::vector<float> correctVertice;
	for (int i = 0; i < vertice.size(); i += jump * 3) {
		glm::vec3 p1(vertice[i], vertice[i + 1], vertice[i + 2]);
		glm::vec3 p2(vertice[i + jump], vertice[i + jump + 1], vertice[i + jump + 2]);
		glm::vec3 p3(vertice[i + (jump * 2)], vertice[i + (jump * 2) + 1], vertice[i + (jump * 2) + 2]);

		glm::vec3 u = p2 - p1;
		glm::vec3 v = p3 - p1;

		glm::vec3 normal = glm::cross(u, v);

		for (int j = 0; j < 3; ++j) {
			correctVertice.push_back(vertice[i + j * jump]);
			correctVertice.push_back(vertice[i + j * jump + 1]);
			correctVertice.push_back(vertice[i + j * jump + 2]);
			if (textured) {
				correctVertice.push_back(vertice[i + j * jump + 3]);
				correctVertice.push_back(vertice[i + j * jump + 4]);
			}
			correctVertice.push_back(normal.x);
			correctVertice.push_back(normal.y);
			correctVertice.push_back(normal.z);
		}
	}
	std::cout << correctVertice.size() / 6 << std::endl;
	return correctVertice;
}

std::vector<float> Parser::ConfirmVertice(std::vector<float> vertice, bool hasNormals) {
	std::vector<float> finalVertice;
	if (!hasNormals) {
		finalVertice = GenerateNormals(vertice, hasNormals);
	}
	else {
		finalVertice = vertice;
	}
	return finalVertice;
}