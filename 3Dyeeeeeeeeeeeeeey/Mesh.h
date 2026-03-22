#pragma once
#include <map>
#include <string>

class SubMesh;
class Material;
class Shader;
class Mesh
{
	std::map<std::string, SubMesh*> subMeshes;
public:
	std::map<std::string, Material*> materials;
	Mesh();
	~Mesh();
	SubMesh* getSubMesh(std::string name);
	void AddSubMesh(SubMesh* newSubMesh, std::string name);
	void PopSubMesh(std::string name);
	void Draw(Shader* shader);
};

