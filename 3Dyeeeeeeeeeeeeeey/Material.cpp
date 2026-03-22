#pragma once
#include "Material.h"
#include "Texture.h"

void Material::Use() {
	if (ambientTex)
		ambientTex->Use(3);
	if (diffuseTex)
		diffuseTex->Use(4);
	if (specularTex)
		specularTex->Use(5);
}