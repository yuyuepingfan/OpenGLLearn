#pragma once

#include <QObject>
#include "Shader.h"


class Program : public QObject
{
	Q_OBJECT

public:
	Program(QObject *parent = nullptr);
	~Program();
	void AttachShader(Shader * vshader, Shader * fshader);
	void UseProgram();
	GLuint getIndex() { return _index; }

private:
	GLuint _index;
};
