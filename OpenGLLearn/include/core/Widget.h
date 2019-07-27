#pragma once

#include <QObject>
class GLFWwindow;
class Widget : public QObject
{
	Q_OBJECT

public:
	Widget(double width = 800, \
		double height = 600, std::string text = "widget", QObject *parent = nullptr);
	~Widget();

	void realise();
	void processEvent(GLFWwindow *);
private:
	GLFWwindow * _window;
};
