#include "Window.h"
#include <cstdlib>
#include <iostream>

void frameBufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::Window(int width, int height, const char* name) : width(width), height(height), name(name) {
    initGLFW();

	window = glfwCreateWindow(width, height, name, nullptr, nullptr);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, frameBufferSizeCallback);
    glfwSwapInterval(1);

    // Charge les pointeurs des fonctions de OpenGL dans Glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glEnable(GL_DEPTH_TEST);
}

Window::~Window() {
    glfwTerminate();
}

void Window::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::setClearColor(float r, float g, float b, float a) {
    glClearColor(r, g, b, a);
}

int Window::getWidth() {
    return width;
}

int Window::getHeight() {
    return height;
}

const char* Window::getName() {
    return name;
}

GLFWwindow* Window::getWindow() {
    return window;
}

void Window::initGLFW() {
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

int Window::isOpen() {
    return !glfwWindowShouldClose(window);
}

void Window::Close() {
    glfwSetWindowShouldClose(window, true);
}

void Window::Display() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}