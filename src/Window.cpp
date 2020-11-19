#include "Window.h"


Window::Window(int width, int height)
{
	windowWidth = width;
	windowHeight = height;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}
	
	xChange = 0.0f;
	yChange = 0.0f;
}

int Window::Initialise()
{
	//Initialisation GLFW
	if (glfwInit() != GLFW_TRUE) {
		printf("GLFW Initialisation failed");
		glfwTerminate();
		return 1;
	}

	//--------SETUP GLFW WINDOW PROPERTY-----------

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	//core profile= No Backward Compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//Allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	// Create the window
	mainWindow = glfwCreateWindow(windowWidth, windowHeight, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		printf("Error creating GLFW window!");
		glfwTerminate();
		return false;
	}

	//Get Buffer Size Information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	/* Make the window's context current */
	glfwMakeContextCurrent(mainWindow);

	// Handle Key + Mouse Input
	createCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);		//locking cursor to screen, disabling cursor

	
	glfwSwapInterval(1);        //syncing device framerate with the open gl;

	glewExperimental = GL_TRUE;         //Allow modern extension features...not used most of the times, but still

	//can only be called after glfwmakecontextcurrent
	if (glewInit() != GLEW_OK) {
		printf("Glew initialisation fails");
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	std::cout<<glGetString(GL_VERSION);

	//Setup viewPort size
	glViewport(0, 0, bufferWidth, bufferHeight);
	glEnable(GL_DEPTH_TEST);

	glfwSetWindowUserPointer(mainWindow, this);
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	//std::cout << key << ", " << code << ", " << ", " << action << ", " << mode << "\n";

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			std::cout << key<<", ";
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			std::cout << key<<", ";
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	//const float mS = 0.5;

	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		std::cout <<"xpos and ypos: "<< xPos << ", "<<yPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	std::cout <<"xchange, ychange:"<< theWindow->xChange << ", " << theWindow->yChange<<"\n";
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
}
