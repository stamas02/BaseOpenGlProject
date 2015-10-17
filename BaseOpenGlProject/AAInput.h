#pragma once
#include "wrapper_glfw.h"
class AAInput
{
public:
	AAInput();
	~AAInput();
	 
	static void keyboardCallback(GLFWwindow* window, int k, int s, int action, int mods);
	static void mouseCallback(GLFWwindow* window, double x, double y);

	

};

