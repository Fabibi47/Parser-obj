#include "SpotLight.h"

SpotLight::SpotLight(glm::vec3 pos, glm::vec3 dir, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float cutOff, float extCutOff, 
	float linear, float quadratic, float constant) :
	PointLight(pos, ambient, diffuse, specular, linear, quadratic, constant), pos(pos), dir(dir), cutOff(cutOff), extCutOff(extCutOff) {
	if (cutOff > extCutOff) {
		float temp = extCutOff;
		extCutOff = cutOff;
		cutOff = temp;
	}
}