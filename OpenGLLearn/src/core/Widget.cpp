#include "include/core/Widget.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

void framwbuffer_size_callback(GLFWwindow * window, int w, int h)
{
	glViewport(0, 0, w, h);
}


Widget::Widget(double width /*= 800*/,\
	double height /*= 600*/, std::string text /*= "widget"*/, QObject *parent /*= nullptr*/)
	: QObject(parent)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window = glfwCreateWindow(width, height, text.c_str(), NULL, NULL);
	if (_window == nullptr)
	{
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(_window);
	glfwSetFramebufferSizeCallback(_window, framwbuffer_size_callback);
}






Widget::~Widget()
{
	glfwTerminate();
}

void Widget::realise()
{
	while (!glfwWindowShouldClose(_window))
	{
		processEvent(_window);
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}

void Widget::processEvent(GLFWwindow * w)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

