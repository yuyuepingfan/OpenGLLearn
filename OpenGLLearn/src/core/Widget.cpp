#include "include/core/Widget.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>


char * vglsl =
"#version 330 core\n"\
"layout (location = 0) in vec3 aPos;\n"\
"void main()\n"\
"{\n"\
"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"\
"}\n";

char * fragGlsl =
"#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}\n";


void framwbuffer_size_callback(GLFWwindow * window, int w, int h)
{
	glViewport(0, 0, w, h);
}


Widget::Widget(double width /*= 800*/,\
	double height /*= 600*/, std::string text /*= "widget"*/, QObject *parent /*= nullptr*/)
	: QObject(parent)
{
	//³õÊ¼»¯glfw´°¿Ú
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	
	_window = glfwCreateWindow(width, height, text.c_str(), NULL, NULL);
	if (_window == nullptr)
	{
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(_window);


	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error:glewInit()" << std::endl;
		return;
	}
	glfwSetFramebufferSizeCallback(_window, framwbuffer_size_callback);
}






Widget::~Widget()
{
	glfwTerminate();
}

void Widget::realise()
{


	float vertices[] = { \
		- 0.5f, -0.5f, 0.0f,\
		0.5f, -0.5f, 0.0f,\
		0.0f, 0.5f, 0.0f,\
		0.5f, 0.5f, 0.0f
	};
	unsigned int indexs[] = {
		0, 1, 2,
		1, 2, 3
	};


	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int EBO;
	glGenBuffers(1, &EBO);


	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vglsl, NULL);
	glCompileShader(vertexShader);

	int sucess;
	char infoLog[512] = { 0 };
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &sucess);
	if (!sucess)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "Error::Shader::Vertex::Compilation_Failed" << infoLog << std::endl;
	}

	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragGlsl, NULL);
	glCompileShader(fragmentShader);

	sucess = 0;
	memset(infoLog, 0, sizeof(infoLog));
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &sucess);

	if (!sucess)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "Error:Shader::Frag::Compilation_Failed" << infoLog << std::endl;
	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	sucess = 0;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &sucess);
	if (!sucess)
	{
		memset(infoLog, 0, sizeof(infoLog));
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		return;
	}

	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glUseProgram(0);


	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexs), indexs, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, \
		3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glUseProgram(shaderProgram);

	glBindVertexArray(0);
	//glUseProgram(0);
	


	while (!glfwWindowShouldClose(_window))
	{
		processEvent(_window);
		glBindVertexArray(VAO);
		glUseProgram(shaderProgram);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		glfwSwapBuffers(_window);
		glfwPollEvents();
	}
}

void Widget::processEvent(GLFWwindow * w)
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

