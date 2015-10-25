#include "AAInput.h"


std::vector<int> AAInput::keys_down;
std::vector<int> AAInput::keys_up;
std::pair<double, double> AAInput::mouse_pos;

std::vector<int> AAInput::keys_down_locked;
std::vector<int> AAInput::keys_up_locked;
std::pair<double, double> AAInput::mouse_pos_locked;

AAInput::AAInput()
{
}


AAInput::~AAInput()
{
}

//static
void AAInput::keyboardCallback(GLFWwindow* window, int k, int s, int action, int mods)
{
	if (action == GLFW_PRESS)
		AAInput::keys_down.push_back(k);
	if (action == GLFW_RELEASE)
	{
		AAInput::keys_up.push_back(k);
		std::vector<int> tmp;
		for (int val : AAInput::keys_down){
			if (val != k)
				tmp.push_back(val);
		}
		AAInput::keys_down = tmp;
	}
}

//static
void AAInput::mouseCallback(GLFWwindow* window, double x, double y)
{
	AAInput::mouse_pos.first = x;
	AAInput::mouse_pos.second = y;
}

bool AAInput::isKeyDown(int key)
{
	return std::find(AAInput::keys_down_locked.begin(), AAInput::keys_down_locked.end(), key) != AAInput::keys_down_locked.end();
}
bool AAInput::isKeyUp(int key)
{
	return std::find(AAInput::keys_up_locked.begin(), AAInput::keys_up_locked.end(), key) != AAInput::keys_up_locked.end();
}
std::pair<double, double> AAInput::getMousePos()
{
	return AAInput::mouse_pos_locked;
}
void AAInput::lock()
{
	AAInput::mouse_pos_locked = AAInput::mouse_pos;
	AAInput::keys_up_locked = AAInput::keys_up;
	AAInput::keys_down_locked = AAInput::keys_down;

	AAInput::keys_up.clear();
}