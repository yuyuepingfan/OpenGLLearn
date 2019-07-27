#include "OpenGLLearn.h"
#include <QtWidgets/QApplication>
#include <GL/glew.h>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OpenGLLearn w;
	w.show();
	return a.exec();
}
