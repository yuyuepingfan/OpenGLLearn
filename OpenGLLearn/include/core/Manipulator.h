#pragma once

#include <QObject>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

class Manipulator : public QObject
{
	Q_OBJECT

public:
	Manipulator(QObject *parent);
	~Manipulator();

	virtual glm::mat4 getView() = 0;
	virtual bool processEvent(GLFWwindow * _window) = 0;

};
