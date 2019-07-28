#include "Program.h"
#include <GL/glew.h>
#include <iostream>

Program::Program(QObject *parent)
	: QObject(parent), _index(0)
{
	_index = glCreateProgram();
	
}

Program::~Program()
{
}

void Program::AttachShader(Shader * vshader, Shader * fshader)
{
	if (vshader && fshader)
	{
		glAttachShader(_index, vshader->getIndex());
		glAttachShader(_index, fshader->getIndex());
		glLinkProgram(_index);

		int sucess = 0;
		glGetProgramiv(_index, GL_LINK_STATUS, &sucess);
		if (!sucess)
		{
			char infoLog[512] = { 0 };
			glGetProgramInfoLog(_index, 512, NULL, infoLog);
			std::cout << "Error:Program::Compilation:" << infoLog;
			return;
		}


		glUseProgram(_index);
		glDeleteShader(vshader->getIndex());
		glDeleteShader(fshader->getIndex());
		glUseProgram(0);
	}
}

void Program::UseProgram()
{
	glUseProgram(_index);
}
