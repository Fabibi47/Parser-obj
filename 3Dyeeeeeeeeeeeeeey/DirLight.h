#pragma once
#include "Light.h"

class DirLight : public Light
{
public:
	glm::vec3 dir;

	DirLight(glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular) : Light(ambient, diffuse, specular), dir(dir) {}
};

