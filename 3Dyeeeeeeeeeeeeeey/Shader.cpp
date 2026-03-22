#pragma once
#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Material.h"
#include "PointLight.h"
#include "DirLight.h"
#include "SpotLight.h"

Shader::Shader(const char* vertexPath, const char* fragmentPath) {
    std::string vertexCode = GetFileContent(vertexPath);
    std::string fragmentCode = GetFileContent(fragmentPath);

    Process(vertexCode, fragmentCode);
}

Shader::~Shader() {
    glDeleteProgram(programId);
}

void Shader::Use() const {
    glUseProgram(programId);
}

void Shader::Shutdown() const {
    glUseProgram(0);
}

std::string Shader::GetFileContent(const char* path) {
    try {
        std::ifstream shaderFile;
        shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

        shaderFile.open(path);
        std::stringstream shaderStream;
        shaderStream << shaderFile.rdbuf();
        shaderFile.close();

        return shaderStream.str();
    }
    catch (std::ifstream::failure& e) {
        std::cout << "ERROR : failed to read file\n" << e.what() << std::endl;
    }
}

void Shader::SetMatrix4(const std::string& name, const glm::mat4& value) const {
    Use();
    glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, &value[0][0]);
    Shutdown();
}

void Shader::Process(std::string vertexCode, std::string fragmentCode) {
    // Vertex Shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    const char* pouet = vertexCode.c_str();
    glShaderSource(vertexShader, 1, &pouet, nullptr);
    glCompileShader(vertexShader);
    // Si ça marche
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(vertexShader, 512, nullptr, infoLog);
        std::cout << "VERTEX SHADER : compilation failed" << infoLog << std::endl;
    }
    vertexShaderId = vertexShader;

    // Fragment Shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    const char* casse_bonbons = fragmentCode.c_str();
    glShaderSource(fragmentShader, 1, &casse_bonbons, nullptr);
    glCompileShader(fragmentShader);
    // Si ça marche
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(fragmentShader, 512, nullptr, infoLog);
        std::cout << "FRAGMENT SHADER : compilation failed" << infoLog << std::endl;
    }
    fragmentShaderId = fragmentShader;

    // Programme des Shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // Si ça marche
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
        std::cout << "SHADER PROGRAM : link failed \n" << infoLog << std::endl;
    }
    programId = shaderProgram;

    // flag les shaders qu'il faut détruire à la destruction du programme
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::SetInt(const std::string& name, int value) const {
    Use();
    glUniform1i(glGetUniformLocation(programId, name.c_str()), value);
    Shutdown();
}

void Shader::SetVector3(const std::string& name, const glm::vec3& value) const {
    Use();
    glUniform3f(glGetUniformLocation(programId, name.c_str()), value.x, value.y, value.z);
    Shutdown();
}

void Shader::SetFloat(const std::string& name, float value) const {
    Use();
    glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
    Shutdown();
}

void Shader::SetMaterial(const std::string& name, Material material) {
    const std::string& ambientName = name + ".ambient";
    const std::string& diffuseName = name + ".diffuse";
    const std::string& specularName = name + ".specular";
    const std::string& shininessName = name + ".shininess";
    SetVector3(ambientName, material.ambient);
    SetVector3(diffuseName, material.diffuse);
    SetVector3(specularName, material.specular);
    SetFloat(shininessName, material.shininess);
}

void Shader::SetDirLight(const std::string& name, DirLight light) {
    const std::string& ambientName = name + ".ambient";
    const std::string& dirName = name + ".direction";
    const std::string& diffuseName = name + ".diffuse";
    const std::string& specularName = name + ".specular";
    SetVector3(ambientName, light.ambientForce);
    SetVector3(specularName, light.specularForce);
    SetVector3(diffuseName, light.diffuseForce);
    SetVector3(dirName, light.dir);
}

void Shader::SetPointLight(const std::string& name, PointLight light) {
    const std::string& ambientName = name + ".ambient";
    const std::string& positionName = name + ".position";
    const std::string& diffuseName = name + ".diffuse";
    const std::string& specularName = name + ".specular";
    const std::string& constantName = name + ".constant";
    const std::string& linearName = name + ".linear";
    const std::string& quadraticName = name + ".quadratic";
    SetVector3(ambientName, light.ambientForce);
    SetVector3(specularName, light.specularForce);
    SetVector3(diffuseName, light.diffuseForce);
    SetVector3(positionName, light.position);
    SetFloat(constantName, light.constant);
    SetFloat(linearName, light.linear);
    SetFloat(quadraticName, light.quadratic);
}

void Shader::SetSpotLight(const std::string& name, SpotLight light) {
    const std::string& directionName = name + ".direction";
    const std::string& cutOffName = name + ".cutOff";
    const std::string& extCutOffName = name + ".extCutOff";
    SetVector3(directionName, light.dir);
    SetFloat(cutOffName, glm::cos(glm::radians(light.cutOff)));
    SetFloat(extCutOffName, glm::cos(glm::radians(light.extCutOff)));
    SetPointLight(name, PointLight(light.position, light.ambientForce, light.diffuseForce, light.specularForce, light.linear, light.quadratic, light.constant));
}