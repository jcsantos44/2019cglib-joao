/**
 * @file appColoredCube.cpp
 * @brief Drawing a colored cube.
 * @author Ricardo Dutra da Silva
 */

//#include <cg.h>
#include <iostream>
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "shader.h"


/* Globals */
GLuint VAO, VBO, CBO;


/* Functions. */
void Init(void);
void Display(void);
void Keyboard(unsigned char, int, int);
void setVertexBuffer(GLfloat* vertices, int size);
void setColorBuffer(GLfloat* colors, int size);
void LoadCube(void);
void LoadTriangle(void);

GLfloat rotationX = 0.0f;
GLfloat rotationY = 0.0f;
GLfloat rotationZ = 0.0f;

void Init()
{
	/* Load mesh to be drawn in buffer */
	LoadCube();

	/* Load and compile shaders. */
	GLuint program = LoadShaders("simple3.vert", "simple3.frag");
	glUseProgram(program);

	/* Compute a fix transformation matrix. */
	glm::mat4 trans = glm::mat4(1.0f);
	trans = glm::rotate(trans, glm::radians(15.0f), glm::vec3(0.0, 0.0, 1.0));
	trans = glm::rotate(trans, glm::radians(15.0f), glm::vec3(0.0, 1.0, 0.0));
	trans = glm::rotate(trans, glm::radians(15.0f), glm::vec3(1.0, 0.0, 0.0));
	
	/* Bind transformation matrix. */
	unsigned int transformLoc = glGetUniformLocation(program, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));
		
	/* Enable depth test (UNCOMMENT THIS PLEASE). */
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
}

int main(int argc, char** argv)
{
	/* Init GLUT and GL. */
	glutInit(&argc, argv);

	/* Init display mode. */
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH);

	/* Window size. */
	glutInitWindowSize(512, 512);

	/* OpenGL Context. */
	glutInitContextVersion(3, 3);
	glutInitContextProfile(GLUT_CORE_PROFILE);

	/* Create window. */
	glutCreateWindow(argv[0]);

	/* Init GLEW. */
	if (glewInit())
       	{
		fprintf(stderr, "Unable to initialize GLEW ... exiting.");
		exit(EXIT_FAILURE);
	}
	
	/* Init GL drawing. */
	Init();

	/* Bind callback functions. */
	glutKeyboardFunc(Keyboard);
	glutDisplayFunc(Display);

	/* Give control to GLUT.*/
	glutMainLoop();
}

void Display(void)
{
	/* Clear buffers for drawing. */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* Draw. */
	glBindVertexArray(VAO);
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	/* Force to display. */
	glFlush();
}

void Keyboard(unsigned char key, int x, int y)
{
	/* Closing a window using the keyboard. */
	switch (key)
	{
		/* Escape key.*/
	case 27:
		glutLeaveMainLoop();
		//exit(0);
	/* q key. */
	case 'q':
	case 'Q':
		exit(0);
	case 'a':
		rotationY++;
		LoadTriangle();
		//std::cout << "A";
		break;
	case 'd':
		rotationY--;
		//std::cout << "D";
		break;
	case 's':
		rotationX--;
		LoadCube();
		//std::cout << "S";
		break;
	case 'w':
		rotationX++;
		//std::cout << "W";
		break;
	}

}

void setVertexBuffer(GLfloat* vertices, int size)
{
	std::cout << size << std::endl;
	/* Create vertex array object (VAO). */
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	/* Create vertex buffer object (VBO). */
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	/* Copy data to VBO. */
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0); //modificado para melhor entendimento
	glEnableVertexAttribArray(0);
}

void setColorBuffer(GLfloat* colors, int size)
{
	/* Create color buffer object (CBO). */
	glGenBuffers(1, &CBO);
	glBindBuffer(GL_ARRAY_BUFFER, CBO);
	glBufferData(GL_ARRAY_BUFFER, size, colors, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
}

void LoadCube()
{
	/* Some vertices for the cube. */
	GLfloat vertices[] = 
	{
		//Front Face
		0.5f, 0.5f, -0.5f, 1.0f,   //Top-Right
		0.5f, -0.5f, -0.5f, 1.0f,  //Botton-Right
		-0.5f, -0.5f, -0.5f, 1.0f, //Botton-Left

		-0.5f, -0.5f, -0.5f, 1.0f, //Botton-Left
		0.5f, 0.5f, -0.5f, 1.0f,   //Top-Right
		-0.5f, 0.5f, -0.5f, 1.0f,  //Top-Left
		//////////////

		//Back face
		0.5f, 0.5f, 0.5f, 1.0f,   //Top-Right
		0.5f, -0.5f, 0.5f, 1.0f,  //Botton-Right
		-0.5f, -0.5f, 0.5f, 1.0f, //Botton-Left

		-0.5f, -0.5f, 0.5f, 1.0f, //Botton-Left
		0.5f, 0.5f, 0.5f, 1.0f,   //Top-Right
		-0.5f, 0.5f, 0.5f, 1.0f,  //Top-Left
		/////////////

		//Top face
		-0.5f, 0.5f, 0.5f, 1.0f,  //Front-Left
		-0.5f, 0.5f, -0.5f, 1.0f, //Back-Left
		0.5f, 0.5f, -0.5f, 1.0f,  //Back-Right

		0.5f, 0.5f, -0.5f, 1.0f,  //Back-Right
		-0.5f, 0.5f, 0.5f, 1.0f,   //Front-Left
		0.5f, 0.5f, 0.5f, 1.0f,   //Front-Right

		///////////////

		//Bottom face
		-0.5f, -0.5f, 0.5f, 1.0f,  //Front-Left
		-0.5f, -0.5f, -0.5f, 1.0f, //Back-Left
		0.5f, -0.5f, -0.5f, 1.0f,  //Back-Right

		0.5f, -0.5f, -0.5f, 1.0f,  //Back-Right
		-0.5f, -0.5f, 0.5f, 1.0f,   //Front-Left
		0.5f, -0.5f, 0.5f, 1.0f,   //Front-Right
		///////////////

		//Left face
		-0.5f, 0.5f, 0.5f, 1.0f,  //Top-Front
		-0.5f, 0.5f, -0.5f, 1.0f, //Top-Back
		-0.5f, -0.5f, -0.5f, 1.0f,  //Bottom-Back

		-0.5f, -0.5f, -0.5f, 1.0f,  //Bottom-Back
		-0.5f, 0.5f, 0.5f, 1.0f,   //Top-Front
		-0.5f, -0.5f, 0.5f, 1.0f,   //Bottom-Front
		///////////////

		//Right face
		0.5f, 0.5f, 0.5f, 1.0f,  //Top-Front
		0.5f, 0.5f, -0.5f, 1.0f, //Top-Back
		0.5f, -0.5f, -0.5f, 1.0f,  //Bottom-Back

		0.5f, -0.5f, -0.5f, 1.0f,  //Bottom-Back
		0.5f, 0.5f, 0.5f, 1.0f,   //Top-Front
		0.5f, -0.5f, 0.5f, 1.0f   //Bottom-Front
		/////////////
	};
	setVertexBuffer(vertices, sizeof(vertices));

	/* Some color for the cube. */
	GLfloat colors[] = {
		0.583f, 0.771f, 0.014f, 1.0f,
		0.609f, 0.115f, 0.436f, 1.0f,
		0.327f, 0.483f, 0.844f, 1.0f,
		0.327f, 0.483f, 0.844f, 1.0f,
		0.583f, 0.771f, 0.014f, 1.0f,
		0.609f, 0.115f, 0.436f, 1.0f,

		0.583f, 0.771f, 0.014f, 1.0f,
		0.609f, 0.115f, 0.436f, 1.0f,
		0.327f, 0.483f, 0.844f, 1.0f,
		0.327f, 0.483f, 0.844f, 1.0f,
		0.583f, 0.771f, 0.014f, 1.0f,
		0.609f, 0.115f, 0.436f, 1.0f,

		0.583f, 0.771f, 0.014f, 1.0f,
		0.609f, 0.115f, 0.436f, 1.0f,
		0.327f, 0.483f, 0.844f, 1.0f,
		0.327f, 0.483f, 0.844f, 1.0f,
		0.583f, 0.771f, 0.014f, 1.0f,
		0.609f, 0.115f, 0.436f, 1.0f,

		0.583f, 0.771f, 0.014f, 1.0f,
		0.609f, 0.115f, 0.436f, 1.0f,
		0.327f, 0.483f, 0.844f, 1.0f,
		0.327f, 0.483f, 0.844f, 1.0f,
		0.583f, 0.771f, 0.014f, 1.0f,
		0.609f, 0.115f, 0.436f, 1.0f,

		0.583f, 0.771f, 0.014f, 1.0f,
		0.609f, 0.115f, 0.436f, 1.0f,
		0.327f, 0.483f, 0.844f, 1.0f,
		0.327f, 0.483f, 0.844f, 1.0f,
		0.583f, 0.771f, 0.014f, 1.0f,
		0.609f, 0.115f, 0.436f, 1.0f,

		0.583f, 0.771f, 0.014f, 1.0f,
		0.609f, 0.115f, 0.436f, 1.0f,
		0.327f, 0.483f, 0.844f, 1.0f,
		0.327f, 0.483f, 0.844f, 1.0f,
		0.583f, 0.771f, 0.014f, 1.0f,
		0.609f, 0.115f, 0.436f, 1.0f
	};
	setColorBuffer(colors, sizeof(colors));
}

void LoadTriangle()
{
	///* Vertices for triangle 
	GLfloat vertices[] =
	{
		0.0f, 0.5f, 0.0f, 1.0f,
		-0.5f, -0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 0.0f, 1.0f
	};
	setVertexBuffer(vertices, sizeof(vertices));

	GLfloat colors[] =
	{
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f
	};
	setColorBuffer(colors, sizeof(colors));
}