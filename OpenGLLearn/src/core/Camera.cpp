#include "Camera.h"

Camera::Camera(QObject *parent)
	: QObject(parent)
{
}

Camera::~Camera()
{
}

void Camera::setView(glm::mat4 & view)
{
	_view = view;
}

void Camera::setProjection(glm::mat4 & projection)
{
	_projection = projection;
}

glm::mat4 Camera::getView()
{
	return _view;
}

glm::mat4 Camera::geteProjection()
{
	return _projection;
}
