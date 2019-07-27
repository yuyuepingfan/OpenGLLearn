#include "OpenGLLearn.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	OpenGLLearn w;
	w.show();
	return a.exec();
}
