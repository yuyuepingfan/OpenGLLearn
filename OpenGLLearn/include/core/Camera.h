#pragma once

#include <QObject>
#include <glm/glm.hpp>

class Camera : public QObject
{
	Q_OBJECT

public:
	Camera(QObject *parent);
	~Camera();
	void setView(glm::mat4 & view);
	void setProjection(glm::mat4 & projection);
	glm::mat4 getView();
	glm::mat4 geteProjection();
private:
	glm::mat4 _view;
	glm::mat4 _projection;

};
