#pragma once
#include <glm/glm.hpp>

class Texture;
class Material
{
public:
	float shininess;

	glm::vec3 ambient;
	glm::vec3 diffuse;
	glm::vec3 specular;

	Texture* ambientTex;
	Texture* diffuseTex;
	Texture* specularTex;

	Material(glm::vec3 ambient = {1.0f, 1.0f, 1.0f}, glm::vec3 diffuse = {1.0f, 1.0f, 1.0f}, glm::vec3 specular = {1.0f, 1.0f, 1.0f}, 
		float shininess = 32, Texture* ambientTex = nullptr, Texture* diffuseTex = nullptr, Texture* specularTex = nullptr) :
		ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), ambientTex(ambientTex), diffuseTex(diffuseTex), specularTex(specularTex) {}

	void Use();
};

