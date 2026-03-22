#pragma once
#include "Light.h"

class PointLight : public Light
{
public:
	float constant = 1;
	float linear;
	float quadratic;
	glm::vec3 position;

	PointLight(glm::vec3 position, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float linear, float quadratic, float constant = 1) :
		Light(ambient, diffuse, specular), position(position), constant(constant), linear(linear), quadratic(quadratic) {}
};

