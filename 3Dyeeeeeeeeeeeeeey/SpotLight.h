#pragma once
#include "PointLight.h"

class SpotLight : public PointLight
{
public:
	float cutOff;
	float extCutOff;
	glm::vec3 dir;
	glm::vec3 pos;


	SpotLight(glm::vec3 pos, glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float cutOff, float extCutOff,
		float linear, float quadratic, float constant = 1);
};

