#include "include/core/Widget.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#include "Program.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <glm/glm.hpp>
#include <glm/geometric.hpp>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "FPManipulator.h"
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
"uniform mat4 model;\n"\
"uniform mat4 view;\n"\
"uniform mat4 projection;\n"\
"out vec3 ourColor;\n"\
"out vec2 TexCoord;\n"\
"void main()\n"\
"{\n"\
"	gl_Position = projection * view * model * vec4(aPos, 1.0);\n"\
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

//glm::mat4 projection;
void framwbuffer_size_callback(GLFWwindow * window, int w, int h)
{
	glViewport(0, 0, w, h);
	//projection = glm::perspective(glm::radians(45.0f), float(w) / float(h), -3.f, 100.f);
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
	FPManipulator * fp = new FPManipulator(nullptr);
	double startTM = glfwGetTime();
	
	glm::mat4 view;
	view = glm::lookAt(glm::vec3(0.0f, 0.0f, 10.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 projection(1.0f);

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
		/*glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glFrontFace(GL_CCW);*/
		
		//fp->getView();
		/*double endTM = glfwGetTime();
		double parma = endTM - startTM;*/
		glm::mat4 model(1.0f);
		//model = glm::translate(model, glm::vec3(glm::sin(parma), 0, 0));
		//view = glm::lookAt(glm::vec3(0, 0.0f, /*3.0f + 7.0f * glm::abs(glm::sin(parma)*/10.0f),
		//	glm::vec3(0.0f, 0.0f, 0.0f),
		//	glm::vec3(0.0f, 1.0f, 0.0f));
		fp->processEvent(_window);
		view = fp->getView();
		projection = glm::perspective(glm::radians(45.0f), float(1800) / float(800), 3.f, 10.f);
		processEvent(_window);
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		program.UseProgram();
		int modelIndex = glGetUniformLocation(program.getIndex(), "model");
		int projectionIndex = glGetUniformLocation(program.getIndex(), "projection");
		int viewIndex = glGetUniformLocation(program.getIndex(), "view");

		glUniformMatrix4fv(modelIndex, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(projectionIndex, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewIndex, 1, GL_FALSE, glm::value_ptr(view));
		
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int)));
//		processEvent(_window);
		program2.UseProgram();
		int modelIndex2 = glGetUniformLocation(program2.getIndex(), "model");
		int projectionIndex2 = glGetUniformLocation(program2.getIndex(), "projection");
		int viewIndex2 = glGetUniformLocation(program2.getIndex(), "view");

		glUniformMatrix4fv(modelIndex2, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(projectionIndex2, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(viewIndex2, 1, GL_FALSE, glm::value_ptr(view));

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

