#pragma once

#include <QObject>
#include <gl/glew.h>

class Program;
class Shader : public QObject
{
	Q_OBJECT

public:
	enum Type {Vertex, Frag} ;
	enum SrcType {File, Src};

public:
	Shader(char * src, SrcType srcType, Type type, QObject *parent = nullptr);
	~Shader();
	
private:
	GLuint getIndex();

private:
	GLuint _index;

	friend class Program;
};
