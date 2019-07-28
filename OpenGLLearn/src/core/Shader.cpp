#include "Shader.h"
#include <fstream>
#include <iostream>
#include <gl/glew.h>




Shader::Shader(char * str, SrcType srcType, Type type, QObject *parent /*= nullptr*/)
	: QObject(parent), _index(0)
{
	if (srcType == SrcType::File && str)
	{
		
		std::ifstream is(str, std::ifstream::binary);
		if (is) {
			is.seekg(0, is.end);
			int length = is.tellg();
			is.seekg(0, is.beg);

			char * buffer = new char[length];
			std::cout << "Reading" << length << "characters...";
			is.read(buffer, length);
			if (is) {
				std::cout << "all charactes read sucessfully.";
				if (type == Vertex)
					_index = glCreateShader(GL_VERTEX_SHADER);
				else if (type = Frag)
					_index = glCreateShader(GL_FRAGMENT_SHADER);
				glShaderSource(_index, 1, &buffer, NULL);
				glCompileShader(_index);

				int sucess = 0;
				char infoLog[512] = { 0 };
				glGetShaderiv(_index, GL_COMPILE_STATUS, &sucess);
				if (!sucess)
				{
					glGetShaderInfoLog(_index, 512, nullptr, infoLog);
					std::cout << "Error::Shader::Vertex::Compilation_Failed" << infoLog;
					return;
				}
			}
			else
			{
				std::cout << "error:only" << is.gcount() << "could be read";
				return;
			}
			is.close();
		}


	}
	else if (srcType == SrcType::Src && str)
	{
		if (type == Vertex)
			_index = glCreateShader(GL_VERTEX_SHADER);
		else if (type = Frag)
			_index = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(_index, 1, &str, NULL);
		glCompileShader(_index);

		int sucess = 0;
		char infoLog[512] = { 0 };
		glGetShaderiv(_index, GL_COMPILE_STATUS, &sucess);
		if (!sucess)
		{
			glGetShaderInfoLog(_index, 512, nullptr, infoLog);
			std::cout << "Error::Shader::Vertex::Compilation_Failed" << infoLog;
			return;
		}
	}
	
}

Shader::~Shader()
{
}

GLuint Shader::getIndex()
{
	return _index;
}
