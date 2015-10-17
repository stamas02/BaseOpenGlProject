/* Link to static libraries, could define these as linker inputs in the project settings instead
if you prefer */
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

/* Include the header to the GLFW wrapper class which
also includes the OpenGL extension initialisation*/
#include "wrapper_glfw.h"
#include <iostream>

/* GLM core */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>
#include "AACamera.h"
#include "AAModelFactory.h"


GLuint positionBufferObject, colourObject;
GLuint program;
GLuint vao;

/* Position and view globals */
GLfloat angle_x, angle_x_inc;

/* Uniforms*/
GLuint modellTransformMatrixID;
GLuint projectionMatrixID;
GLuint RotationMatrixID;

AACamera* myCamera;

/*
This function is called before entering the main rendering loop.
Use it for all your initialisation stuff
*/
void init(GLWrapper *glw)
{

	angle_x = 0;
	angle_x_inc = 0;

	// Generate index (name) for one vertex array object
	glGenVertexArrays(1, &vao);

	// Create the vertex array object and make it current
	glBindVertexArray(vao);
	
	/*
	AAModelLoader loader;
	std::vector<glm::vec3> vertexPositions = AAModelLoader::LoadObj<glm::vec3, glm::vec3, glm::vec3>("cube.obj");
	*/
	/* Create a vertex buffer object to store vertices */
	glGenBuffers(1, &positionBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), static_cast<void*>(&vertexPositions[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);



	try
	{
		program = glw->LoadShader("lab2.vert", "lab2.frag");
	}
	catch (std::exception &e)
	{
		std::cout << "Caught exception: " << e.what() << std::endl;
		std::cin.ignore();
		exit(0);
	}

	glEnable(GL_DEPTH_TEST);
	modellTransformMatrixID = glGetUniformLocation(program, "worldTransformMatrix");
	projectionMatrixID = glGetUniformLocation(program, "worldprojectionMatrix");
	RotationMatrixID = glGetUniformLocation(program, "worldrotationMatrix");
	myCamera = new AACamera();
}

//Called to update the display.
//You should call glfwSwapBuffers() after all of your rendering to display what you rendered.
void display()
{
	/* Define the background colour */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/* Clear the colour and frame buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);

	glBindBuffer(GL_ARRAY_BUFFER, positionBufferObject);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)(2*sizeof(glm::vec3)));

	glUniformMatrix4fv(modellTransformMatrixID, 1, GL_FALSE, &myCamera->getWorldTransformationMatrix()[0][0]);
	glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, &myCamera->getWorldProjectionMatrix()[0][0]);
	glUniformMatrix4fv(RotationMatrixID, 1, GL_FALSE, &myCamera->getWorldRotationMatrix()[0][0]);


	
	glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(0);
	glUseProgram(0);

	/* Modify our animation variables */
	angle_x += angle_x_inc;
}


/* Called whenever the window is resized. The new window size is given, in pixels. */
static void reshape(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

/* change view angle, exit upon ESC */
static void keyCallback(GLFWwindow* window, int k, int s, int action, int mods)
{
	if (action != GLFW_PRESS) return;

	if (k == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	
	
	if (k == GLFW_KEY_UP) myCamera->moveForward(0.1f);
	if (k == GLFW_KEY_DOWN) myCamera->moveBackward(0.1f);
	if (k == GLFW_KEY_RIGHT) myCamera->moveRight(0.1f);
	if (k == GLFW_KEY_LEFT) myCamera->moveLeft(0.1f);

}


/* change view angle, exit upon ESC */
static void mouseCallback(GLFWwindow* window, double x, double y)
{/*
	myCamera->rotateUp(10.0f);
	myCamera->rotateDown(10.0f);
	myCamera->rotateLeft(10.0f);
	myCamera->rotateRight(10.);
	*/

}

/* An error callback function to output GLFW errors*/
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

/* Entry point of program */
int main(int argc, char* argv[])
{
	GLWrapper *glw = new GLWrapper(1024, 768, "Lab2: Hello 3D");;

	if (!ogl_LoadFunctions())
	{
		fprintf(stderr, "ogl_LoadFunctions() failed. Exiting\n");
		return 0;
	}

	/* Note it you might want to move this call to the wrapper class */
	glw->setErrorCallback(error_callback);

	glw->setRenderer(display);
	glw->setKeyCallback(keyCallback);
	glw->setMouseCallback(mouseCallback);
	glw->setReshapeCallback(reshape);

	init(glw);

	glw->eventLoop();

	delete(glw);
	return 0;
}



