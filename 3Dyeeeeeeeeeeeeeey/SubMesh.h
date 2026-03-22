#pragma once
#include <vector>

class VAO;
class Material;
class Shader;
class SubMesh
{
	bool textured = false;
	int verticeSize = 0;

	std::vector<float> all;
	VAO* vao = nullptr;
	Material* material = nullptr;
public:
	SubMesh();
	SubMesh(std::vector<float> all, int verticeSize, bool textured, Material* material = nullptr);
	VAO* GenerateVao();
	VAO* getVao();
	std::vector<float> getVertice();
	void setVertice(std::vector<float> newVertice);
	void Draw(Shader* shader);
	void SetMaterial(Material* material);
	void SetTextured(bool textured);
	bool isTextured();
};

