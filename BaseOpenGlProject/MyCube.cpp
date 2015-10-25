#include "MyCube.h"
#include "AAWorld.h"


MyCube::MyCube(char * name) : AAModel(name)
{

	this->loadModel("golf.obj");
	front_left_wheel = this->getChildByName("front_wheel_left");
	front_right_wheel = this->getChildByName("front_wheel_right");
	rear_left_wheel = this->getChildByName("rear_wheel_right");
	rear_right_wheel = this->getChildByName("rear_wheel_left");

}


MyCube::~MyCube()
{
}

void MyCube::update()
{
	this->rotateDown(0.1f);
	//glm::vec3 pos = this->getPosition();
	//pos.x += 0.1f;
	//this->setPosition(pos);
	front_left_wheel->rotateLeft(0.1f);
}
