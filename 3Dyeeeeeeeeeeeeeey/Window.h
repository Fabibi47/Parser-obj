#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
	int width;
	int height;
	const char* name;
	GLFWwindow* window;
public:
	Window(int width, int height, const char* name);
	~Window();
	void initGLFW();
	void Clear();
	void setClearColor(float r, float g, float b, float a);
	void Close();
	void Display();
	int isOpen();
	int getWidth();
	int getHeight();
	const char* getName();
	GLFWwindow* getWindow();
};

