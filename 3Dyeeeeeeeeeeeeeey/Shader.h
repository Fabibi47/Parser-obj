#pragma once
#include <glm/glm.hpp>
#include <string>

class Material;
class PointLight;
class DirLight;
class SpotLight;
class Shader
{
	std::string GetFileContent(const char* path);
public:
	unsigned int vertexShaderId;
	unsigned int fragmentShaderId;
	unsigned int programId;

	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void Process(std::string vertexCode, std::string fragmentCode);

	void Use() const;
	void Shutdown() const;

	void SetMatrix4(const std::string& name, const glm::mat4& value) const;
	void SetVector3(const std::string& name, const glm::vec3& value) const;
	void SetFloat(const std::string& name, float value) const;

	void SetInt(const std::string& name, int value) const;

	void SetMaterial(const std::string& name, Material material);
	void SetPointLight(const std::string& name, PointLight light);
	void SetDirLight(const std::string& name, DirLight light);
	void SetSpotLight(const std::string& name, SpotLight light);
};
