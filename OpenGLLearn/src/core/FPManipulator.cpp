#include "FPManipulator.h"

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

FPManipulator::FPManipulator(QObject *parent)
	: Manipulator(parent)
{
	_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
}

FPManipulator::~FPManipulator()
{
}

glm::mat4 FPManipulator::getView()
{
	return _view;
}

bool FPManipulator::processEvent(GLFWwindow * _window)
{
	if (glfwGetKey(_window, GLFW_KEY_W) == GLFW_PRESS)
	{
		_view *= glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -0.001f));
	}
	if (glfwGetKey(_window, GLFW_KEY_S) == GLFW_PRESS)
	{
		_view *= glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0.001f));
	}
	if (glfwGetKey(_window, GLFW_KEY_A) == GLFW_PRESS)
	{
		_view *= glm::translate(glm::mat4(1.0f), glm::vec3(-0.001f, 0, 0.f));
	}
	if (glfwGetKey(_window, GLFW_KEY_D) == GLFW_PRESS)
	{
		_view *= glm::translate(glm::mat4(1.0f), glm::vec3(0.001f, 0, 0.f));
	}
	if (glfwGetKey(_window, GLFW_KEY_BACKSPACE) == GLFW_PRESS)
	{
		_view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f));
	}

	return false;
}
