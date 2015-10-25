#include "AACamera.h"
#include "AAWorld.h"


AACamera::AACamera(const char * name) : AAObject(name)
{
	this->worldProjectionMatrix = glm::perspective(60.0f, 1024.0f / 768.0f, 0.1f, 1000.0f);
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


void AACamera::rotate(float degree, glm::vec3 vect)
{
	glm::mat3 rotation = glm::mat3(glm::rotate(degree, vect));
	this->forward = rotation * this->forward;
	this->up = rotation * this->up;
	//this->objectRotationMatrix = glm::rotate(degree, vect)*this->objectRotationMatrix;

	this->objectRotationMatrix = glm::lookAt(glm::vec3(0,0,0), -this->getForwardVector(), this->up);
}

void AACamera::rotateUp(float degree)
{
	this->rotate(-degree, this->getLeftVector());
}

void AACamera::rotateDown(float degree)
{
	this->rotate(degree, this->getLeftVector());
}

void AACamera::rotateLeft(float degree)
{
	this->rotate(-degree, AAWorld::getUpVector());
}

void AACamera::rotateRight(float degree)
{
	this->rotate(degree, AAWorld::getUpVector());
}


AACamera::~AACamera()
{

}
