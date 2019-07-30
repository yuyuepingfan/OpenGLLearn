#pragma once

#include <QObject>
#include "Manipulator.h"
#include <glm/glm.hpp>
class FPManipulator : public Manipulator
{
	Q_OBJECT

public:
	FPManipulator(QObject *parent);
	~FPManipulator();

	virtual glm::mat4 getView();
	virtual bool processEvent(GLFWwindow * _window);

private:
	glm::mat4 _view;
	
	
};
