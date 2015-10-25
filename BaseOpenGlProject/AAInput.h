#pragma once
#include "wrapper_glfw.h"
#include <vector>

class AAScene;
class AAObject;


class AAInput
{
	friend GLWrapper;
public:
	AAInput();
	~AAInput();
	 

	
	
	static bool isKeyDown(int key);
	static bool isKeyUp(int key);
	static std::pair<double, double> getMousePos();

private:
	static void keyboardCallback(GLFWwindow* window, int k, int s, int action, int mods);
	static void mouseCallback(GLFWwindow* window, double x, double y);
	static void lock();

	static std::vector<int> keys_down;
	static std::vector<int> keys_up;
	static std::pair<double,double> mouse_pos;

	static std::vector<int> keys_down_locked;
	static std::vector<int> keys_up_locked;
	static std::pair<double, double> mouse_pos_locked;
};

