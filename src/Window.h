#pragma once

#include "GLCheckError.h"
#include <GLFW\glfw3.h>
#include <iostream>

class Window
{
private:
	GLFWwindow* mainWindow;

	int windowWidth, windowHeight;
	int bufferWidth, bufferHeight;

	bool keys[1024];

	GLfloat lastX;
	GLfloat lastY;
	GLfloat xChange;
	GLfloat yChange;
	bool mouseFirstMoved=true;

	void createCallbacks();
	static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
	static void handleMouse(GLFWwindow* window, double xPos, double yPos);


public:
	Window(int width, int height);

	int Initialise();

    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

    void swapBuffers() { glfwSwapBuffers(mainWindow); }

	int getBufferWidth() { return bufferWidth; }
	int getBufferHeight() { return bufferHeight; }

	

	bool* getsKeys() { return keys; }
	GLfloat getXChange();
	GLfloat getYChange();

	

	~Window();
};