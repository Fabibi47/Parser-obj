#pragma once
#include <glm/glm.hpp>

class Light
{
public:
	glm::vec3 ambientForce;
	glm::vec3 diffuseForce;
	glm::vec3 specularForce;

	Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : 
		ambientForce(ambient), diffuseForce(diffuse), specularForce(specular) {}
};

