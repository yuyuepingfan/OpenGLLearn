#pragma once

#include <QObject>

class Widget : public QObject
{
	Q_OBJECT

public:
	Widget(QObject *parent);
	~Widget();
};
