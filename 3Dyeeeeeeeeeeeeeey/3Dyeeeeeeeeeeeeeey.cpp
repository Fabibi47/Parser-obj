#pragma once
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "Shader.h"
#include "Window.h"
#include "VAO.h"
#include "stb_image.h"
#include "Texture.h"
#include "Parser.h"
#include "Mesh.h"
#include "SubMesh.h"
#include "Material.h"
#include "PointLight.h"
#include "DirLight.h"
#include "SpotLight.h"

unsigned int WIDTH_SCREEN = 800;
unsigned int HEIGHT_SCREEN = 600;
unsigned int SHADOW_WIDTH = 1024;
unsigned int SHADOW_HEIGHT = 1024;

int main()
{
    Window window(WIDTH_SCREEN, HEIGHT_SCREEN, "cours OpenGL");

    Parser parser;

    Shader shader("./vertex.glsl", "./fragment.glsl");
   Shader shaderLight("./vertexLight.glsl", "./fragmentLight.glsl");

    // LE CUBE TEXTURÉ ET NORMALISÉ
    std::vector<float> vertices = {
        ////////////FACE AVANT////////////
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        ///////////////////////////////
        0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, -1.0f,
        0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        /////////FACE DROITE//////////
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        //////////////////////////////
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f,
        ////////////FACE HAUT////////////
        0.5f, 0.5f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        /////////////////////////////////
        -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
        /////////FACE ARRIERE/////////
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        ///////////////////////////////
        0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        -0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f,
        0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        /////////////FACE BAS/////////////
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        ///////////////////////////////////
        -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, 0.0f, -1.0f, 0.0f,
        -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f,
        ///////////FACE GAUCHE/////////////
        -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, -0.5f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, -0.5, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
            //////////////////////////////////
            -0.5f, 0.5f, 0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
    };
    VAO* vao = new VAO(vertices, vertices.size(), 8, GL_STATIC_DRAW);
    vao->SetAttribute(0, 3, 8, 0);
    vao->SetAttribute(1, 2, 8, 3);
    vao->SetAttribute(2, 3, 8, 5);
    //VAO* vaoLight = new VAO(vertices, vertices.size(), GL_STATIC_DRAW);
    //vaoLight->SetAttribute(0, 3, 5, 0);

    /*Texture textureDiff("texture-diffuse.png");
    Texture textureSpec("texture-specular.png");*/

    Mesh* van = parser.ParseMesh("van.obj");

    /////////SHADOW/////////
    unsigned int depthMapFBO;
    glGenFramebuffers(1, &depthMapFBO);

    unsigned int depthMap; //Set up de la texture de profondeur (patch la classe Texture pour juste créer une texture)
    glGenTextures(1, &depthMap);
    glBindTexture(GL_TEXTURE_2D, depthMap);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0); //Remplissage de la texture profondeur
    glDrawBuffer(GL_NONE); //mettre ces deux-là en None permets de ne pas faire de calculs de couleurs
    glReadBuffer(GL_NONE);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    Shader shadowShader("shadowVertex.glsl", "shadowFragment.glsl");


    // Création des matrices de tranformation
    glm::vec3 cameraPos = glm::vec3(0, 0, -2.0f);
    glm::vec3 cameraUp = glm::vec3(0, 1, 0);
    float cameraYaw = -90;
    float cameraPitch = 0;
    glm::vec3 cameraFront = glm::normalize(glm::vec3(
        cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch)),  //Yaw   (x)
        sin(glm::radians(cameraPitch)),                                 //Pitch (y)
        sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch))   //Roll  (z)
    ));
    glm::mat4 model = glm::mat4(1.0f);
    glm::mat4 modelLight = glm::mat4(1.0f);
    glm::mat4 view = glm::mat4(1.0f);
    glm::mat4 cubeModel = glm::mat4(1.0f);
    view = glm::translate(view, cameraPos);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)WIDTH_SCREEN / (float)HEIGHT_SCREEN, 0.1f, 100.0f);
    model = glm::translate(model, glm::vec3(0, -0, 0));
    model = glm::scale(model, glm::vec3(0.3f, 0.3f, 0.3f));
    cubeModel = glm::translate(cubeModel, glm::vec3(0, -1, 0));
    cubeModel = glm::scale(cubeModel, glm::vec3(20, 0.1f, 20));


    // On les envoie dans le shader
    shader.SetMatrix4("projection", projection);
    shader.SetMatrix4("view", view);
    shader.SetMatrix4("model", model);
    shaderLight.SetMatrix4("view", view);
    shaderLight.SetMatrix4("projection", projection);
    shader.SetInt("material.diffuseTexture", 0);
    shader.SetInt("material.specularTexture", 1);

    shader.SetVector3("viewPos", cameraPos);

    /*Material cubeMaterial(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), 32.0f, textureDiff, textureSpec);
    shader.SetMaterial("material", cubeMaterial);*/

    PointLight* pLight = new PointLight(glm::vec3(-1.f, 3.f, 1.5f), glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1), 0.045f, 0.0075f);
    shader.SetPointLight("pLight", *pLight);

    /*DirLight* dLight = new DirLight(glm::vec3(-1, -1, 0), glm::vec3(0.25f, 0.25f, 0.25f), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1));
    shader.SetDirLight("dLight", *dLight);*/

    /*SpotLight* sLight = new SpotLight(glm::vec3(0, 1, 0), glm::vec3(0, -1, 0), glm::vec3(0.25f, 0.25f, 0.25), glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(1, 1, 1), 30, 20, 0.7, 1.8);
    shader.SetSpotLight("sLight", *sLight);*/
    modelLight = glm::translate(modelLight, pLight->position);

    float near_plane = 1.0f, far_plane = 7.5f;
    glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near_plane, far_plane);
    glm::mat4 lightView = glm::lookAt(
        glm::vec3(pLight->position),
        glm::vec3(0.0f, 0, 0),
        glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 lightSpaceMatrix = lightProjection * lightView;

    float baseMs = 1;
    float fastMs = 2;
    float ms;

    // van->Draw(&shader);

    window.setClearColor(0.2, 0.2, 0.2, 1);

    Texture t("texture-diffuse.png", GL_REPEAT);

    // Render loop
    while (window.isOpen()) {
        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            window.Close();
        }
        if (glfwGetKey(window.getWindow(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
            ms = fastMs * glfwGetTime();
        }
        else {
            ms = baseMs * glfwGetTime();
        }
        if (glfwGetKey(window.getWindow(), GLFW_KEY_W) == GLFW_PRESS) {
            cameraPos += ms * cameraFront;
        }
        if (glfwGetKey(window.getWindow(), GLFW_KEY_S) == GLFW_PRESS) {
            cameraPos -= ms * cameraFront;
        }
        if (glfwGetKey(window.getWindow(), GLFW_KEY_D) == GLFW_PRESS) {
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * ms;
        }
        if (glfwGetKey(window.getWindow(), GLFW_KEY_A) == GLFW_PRESS) {
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * ms;
        }
        if (glfwGetKey(window.getWindow(), GLFW_KEY_E) == GLFW_PRESS) {
            cameraPos += ms * cameraUp;
        }
        if (glfwGetKey(window.getWindow(), GLFW_KEY_Q) == GLFW_PRESS) {
            cameraPos -= ms * cameraUp;
        }
        if (glfwGetKey(window.getWindow(), GLFW_KEY_RIGHT) == GLFW_PRESS) {
            cameraYaw += 40 * glfwGetTime();
        }
        if (glfwGetKey(window.getWindow(), GLFW_KEY_LEFT) == GLFW_PRESS) {
            cameraYaw -= 40 * glfwGetTime();
        }
        if (glfwGetKey(window.getWindow(), GLFW_KEY_UP) == GLFW_PRESS) {
            cameraPitch += 40 * glfwGetTime();
        }
        if (glfwGetKey(window.getWindow(), GLFW_KEY_DOWN) == GLFW_PRESS) {
            cameraPitch -= 40 * glfwGetTime();
        }
        cameraFront = glm::normalize(glm::vec3(
            cos(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch)),  //Yaw   (x)
            sin(glm::radians(cameraPitch)),                                 //Pitch (y)
            sin(glm::radians(cameraYaw)) * cos(glm::radians(cameraPitch))   //Roll  (z)
        ));
        view = glm::translate(view, cameraPos);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shader.SetMatrix4("view", view);
        shaderLight.SetMatrix4("view", view);
        glfwSetTime(0);
        /*model = glm::rotate(model, 0.01f, glm::vec3(-0.1f, 0.1f, 0.1f));
        shader.SetMatrix4("model", model); */ 

        // Draw le triangle
        //shader.Use();

            //render pour la depth map
        shadowShader.SetMatrix4("lightSpaceMatrix", lightSpaceMatrix);
        glViewport(0, 0, SHADOW_WIDTH, SHADOW_HEIGHT);
        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glClear(GL_DEPTH_BUFFER_BIT);
        shadowShader.SetMatrix4("model", model);
        shadowShader.Use();
        van->Draw(&shadowShader);
        shadowShader.SetMatrix4("model", cubeModel);
        shadowShader.Use();
        vao->Draw();
        shadowShader.Shutdown();
        glBindFramebuffer(GL_FRAMEBUFFER, 0);

        shader.SetMatrix4("lightSpaceMatrix", lightSpaceMatrix);
        shader.SetInt("shadowMap", 2);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, depthMap);

        glViewport(0, 0, WIDTH_SCREEN, HEIGHT_SCREEN);
        window.Clear();
        shader.SetMatrix4("model", model);
        shader.Use();
        van->Draw(&shader);

        shader.SetMatrix4("model", cubeModel);
        shader.Use();
        t.Use(0);
        t.Use(1);
        vao->Draw();
        shader.Shutdown();

        shaderLight.SetMatrix4("model", modelLight);
        shaderLight.Use();
        vao->Draw();
        shaderLight.Shutdown();

        window.Display();
    }

    glfwTerminate();
    return 0;
}
