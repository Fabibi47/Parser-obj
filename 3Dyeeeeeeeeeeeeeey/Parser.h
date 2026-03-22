#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <string>

class Mesh;
class Material;
class Parser
{
public:
	Parser();
	Mesh* ParseMesh(const char* path);
	void ParseMaterials(std::string path, Mesh* mesh);
	std::vector<float> GenerateNormals(std::vector<float> vertice, bool textured);
	std::vector<float> ConfirmVertice(std::vector<float> vertice, bool hasNormals);
};

