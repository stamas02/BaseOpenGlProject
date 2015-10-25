/* Link to static libraries, could define these as linker inputs in the project settings instead
if you prefer */
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "glloadD.lib")
#pragma comment(lib, "opengl32.lib")

/* Include the header to the GLFW wrapper class which
also includes the OpenGL extension initialisation*/
#include "wrapper_glfw.h"
#include <iostream>
#include <stack>

/* GLM core */
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <glm/gtc/type_ptr.hpp>
#include "AACamera.h"
#include "AAModelFactory.h"
#include "AAModel.h"
#include "MainScene.h"

GLuint positionBufferObject, colourObject;
GLuint program;
GLuint vao;

/* Position and view globals */
GLfloat angle_x, angle_x_inc;

/* Uniforms*/
GLuint wolrdTransformMatrixID;
GLuint wolrdProjectionMatrixID;
GLuint wolrdRotationMatrixID;

GLuint modelMatrixID;

MainScene* scene;

struct StackObj
{
	StackObj(AAModel* model, glm::mat4 modelMatrix)
	{
		this->model = model;
		this->modelMatrix = modelMatrix;
	}
	AAModel* model;
	glm::mat4 modelMatrix;
};

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
	
	scene = new MainScene();

	/*
	AAModelFactory modelFactory;

	modelFactory.CreateModel("cube.obj", &model);
	std::vector<glm::vec4> vertexPositions = model->getVerecies();
	*/

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
	wolrdTransformMatrixID = glGetUniformLocation(program, "worldTransformMatrix");
	wolrdProjectionMatrixID = glGetUniformLocation(program, "worldProjectionMatrix");
	wolrdRotationMatrixID = glGetUniformLocation(program, "worldRotationMatrix");

	modelMatrixID = glGetUniformLocation(program, "modelMatrix");
	
}

//Called to update the display.
//You should call glfwSwapBuffers() after all of your rendering to display what you rendered.
void display()
{
	scene->update();
	/* Define the background colour */
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/* Clear the colour and frame buffers */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);

	const std::vector<AAModel*> modells = scene->getModels();
	const AACamera* camera = scene->getAciveCamera();

	glUniformMatrix4fv(wolrdTransformMatrixID, 1, GL_FALSE, &camera->getWorldTransformationMatrix()[0][0]);
	glUniformMatrix4fv(wolrdProjectionMatrixID, 1, GL_FALSE, &camera->getWorldProjectionMatrix()[0][0]);
	glUniformMatrix4fv(wolrdRotationMatrixID, 1, GL_FALSE, &camera->getWorldRotationMatrix()[0][0]);
	std::stack<StackObj *> model_stack;
	for (AAModel* model : modells){
		model_stack.push(new StackObj(model,
			model->getObjectTransformationMatrix()*
			model->getObjectRotationMatrix()));
		while (model_stack.size() > 0)
		{
			StackObj * current_model_item = model_stack.top();
			model_stack.pop();
			AAModel* current_model = current_model_item->model;
			current_model->prepareToBeDrawn();
			glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, &current_model_item->modelMatrix[0][0]);
			//if (strcmp(current_model->getName(),"body") != 0)
				glDrawArrays(GL_TRIANGLES, 0, current_model->getSize());
			vector<AAModel * > all_children = current_model->getChildren();
			for (AAModel* child : all_children){
				model_stack.push(new StackObj(child,
					current_model_item->modelMatrix*child->getObjectTransformationMatrix()*child->getObjectRotationMatrix()
					));
			}
			delete current_model_item;
			
		}
	}

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
	

}


/* change view angle, exit upon ESC */
static void mouseCallback(GLFWwindow* window, double x, double y)
{


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



