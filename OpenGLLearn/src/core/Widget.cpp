#include "include/core/Widget.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Program.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//char * vglsl =
//"#version 330 core\n"\
//"layout (location = 0) in vec3 aPos;\n"\
//"void main()\n"\
//"{\n"\
//"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"\
//"}\n";

char * vglsl =
"#version 330 core\n"\
"layout (location = 0) in vec3 aPos;\n"\
"layout (location = 1) in vec3 aColor;\n"\
"layout (location = 2) in vec2 aTexCoord;\n"\
"out vec3 ourColor;\n"\
"out vec2 TexCoord;\n"\
"void main()\n"\
"{\n"\
"	gl_Position = vec4(aPos, 1.0);\n"\
"	ourColor = aColor;\n"\
"	TexCoord = aTexCoord;\n"\
"}\n";

char * fragGlsl =
"#version 330 core\n"\
"out vec4 FragColor\n;"\
"in vec3 ourColor;\n"\
"in vec2 TexCoord;\n"\
"uniform sampler2D ourTexture;\n"\
"void main()\n"\
"{\n"
"	FragColor = texture(ourTexture, TexCoord);\n"\
"}\n";


//char * fragGlsl =
//"#version 330 core\n"
//"out vec4 FragColor;\n"
//"void main()\n"
//"{\n"
//"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
//"}\n";


void framwbuffer_size_callback(GLFWwindow * window, int w, int h)
{
	glViewport(0, 0, w, h);
}


Widget::Widget(double width /*= 800*/,\
	double height /*= 600*/, std::string text /*= "widget"*/, QObject *parent /*= nullptr*/)
	: QObject(parent)
{
	//��ʼ��glfw����
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
		-0.5f, -0.5f, 0.0f,		1.0f, 0.0f, 0.0f,	0.0f, 0.0f,\
		0.5f, -0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 0.0f,\
		0.0f, 0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	0.5f, 0.5f,\
		0.5f, 0.5f, 0.0f,		0.0f, 1.0f, 0.0f,	1.0f, 1.0f\
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
	unsigned int texture;
	glGenTextures(1, &texture);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indexs), indexs, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	
	//
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	unsigned char * data = stbi_load("hello.jpeg", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width\
		,height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	Shader vs(vglsl, Shader::SrcType::Src, Shader::Type::Vertex);
	Shader fs(fragGlsl, Shader::SrcType::Src, Shader::Type::Frag);
	Program program;
	program.AttachShader(&vs, &fs);
	Program program2;
	program2.AttachShader(&vs, &fs);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, \
		8 * sizeof(float), 0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, \
		8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, \
		8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	while (!glfwWindowShouldClose(_window))
	{
		processEvent(_window);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		program.UseProgram();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));
//		processEvent(_window);
		program2.UseProgram();
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
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

