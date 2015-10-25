#pragma once
#include "AAScene.h"

class MainScene : public AAScene
{
public:
	MainScene();

	~MainScene();
	void update();

private:
	std::pair<double, double> previousMousePos;
};

