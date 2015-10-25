#include "AAScene.h"
#include "AACamera.h"


AAScene::AAScene()
{
	this->camera = new AACamera("cam1");
}


AAScene::~AAScene()
{
}

const AACamera* AAScene::getAciveCamera() const
{
	return this->camera;
}
const std::vector<AAModel*> AAScene::getModels() const
{
	return this->objects;
}
