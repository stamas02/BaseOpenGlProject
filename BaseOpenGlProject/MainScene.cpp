#include "MainScene.h"
#include "MyCube.h"
#include "AAInput.h"

MainScene::MainScene() : AAScene()
{
	MyCube* cube = new MyCube("body");
	this->objects.push_back(cube);
}


MainScene::~MainScene()
{
}

void MainScene::update()
{
	for (AAObject* obj : this->objects)
		obj->update();

	
	if(AAInput::isKeyDown(GLFW_KEY_UP))
		this->camera->moveForward(0.1f);
	if (AAInput::isKeyDown(GLFW_KEY_DOWN))
		this->camera->moveBackward(0.1f);
	if (AAInput::isKeyDown(GLFW_KEY_RIGHT))
		this->camera->moveRight(0.1f);
	if (AAInput::isKeyDown(GLFW_KEY_LEFT))
		this->camera->moveLeft(0.1f);

	std::pair<double, double> currentMousePos = AAInput::getMousePos();
	double x_delta = previousMousePos.first - currentMousePos.first;
	double y_delta = previousMousePos.second - currentMousePos.second;
	if (x_delta != 0)
		this->camera->rotateLeft(x_delta);
	if (y_delta != 0)
		this->camera->rotateDown(y_delta);

	previousMousePos = currentMousePos;
}