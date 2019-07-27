#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OpenGLLearn.h"

class OpenGLLearn : public QMainWindow
{
	Q_OBJECT

public:
	OpenGLLearn(QWidget *parent = Q_NULLPTR);

private:
	Ui::OpenGLLearnClass ui;
};
