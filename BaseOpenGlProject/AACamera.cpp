#include "AACamera.h"
#include "AAWorld.h"


AACamera::AACamera() : AAObject()
{
	this->worldProjectionMatrix = glm::perspective(60.0f, 1024.0f / 768.0f, 1.0f, 100.0f);
}


void AACamera::setWorldProjectionMatrix(glm::mat4 pojectionMatrix)
{
	this->worldProjectionMatrix = pojectionMatrix;
}


const glm::mat4 AACamera::getWorldProjectionMatrix() const
{
	return this->worldProjectionMatrix;
}
const glm::mat4 AACamera::getWorldTransformationMatrix() const
{
	return this->getObjectTransformationMatrix();
}
const glm::mat4 AACamera::getWorldRotationMatrix() const
{
	return this->getObjectRotationMatrix();
}



void AACamera::rotateUp(float degree)
{
	this->rotate(degree, glm::cross(AAWorld::getForwardVector(), AAWorld::getUpVector()));
}

void AACamera::rotateDown(float degree)
{
	this->rotate(-degree, glm::cross(AAWorld::getForwardVector(), AAWorld::getUpVector()));
}

void AACamera::rotateLeft(float degree)
{
	this->rotate(degree, AAWorld::getUpVector());
}

void AACamera::rotateRight(float degree)
{
	this->rotate(-degree, AAWorld::getUpVector());
}


AACamera::~AACamera()
{

}
