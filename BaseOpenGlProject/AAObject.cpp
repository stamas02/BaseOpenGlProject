#include "AAObject.h"
#include "AAWorld.h"

AAObject::AAObject(const char *name)
{
	this->name = name;
	glm::mat4 modelTransformationMatrix;
	glm::mat4 projectionMatrix;
	this->objectTransformationMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, 0.0f));
	this->objectScaleMatrix = glm::scale(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, 0.0f));
	this->objectRotationMatrix = glm::rotate(glm::mat4(), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	this->forward = AAWorld::getForwardVector();
	this->up = AAWorld::getUpVector();
}


AAObject::~AAObject()
{
}

//setters
void AAObject::setPosition(glm::vec3 position)
{
	this->position = position;
	this->objectTransformationMatrix = glm::translate(glm::mat4(1.f), this->position);
}

void AAObject::setObjectTransformationMatrix(glm::mat4 modelTransformationMatrix)
{
	this->objectTransformationMatrix = modelTransformationMatrix;
}

void AAObject::setObjectRotationMatrix(glm::mat4 objectRotationMatrix)
{
	this->objectTransformationMatrix = objectRotationMatrix;
}

void AAObject::setObjectScaleMatrix(glm::mat4 objectScaleMatrix)
{
	this->objectScaleMatrix = objectScaleMatrix;
}

//getters
const glm::vec3 AAObject::getPosition() const
{
	return this->position;
}

const glm::vec3 AAObject::getForwardVector() const
{
	return this->forward;
}

const glm::vec3 AAObject::getBackwardVector() const
{
	return this->getForwardVector() * -1.0f;
}

const glm::vec3 AAObject::getUpVector() const
{
	return this->up;
}

const glm::vec3 AAObject::getDownVector() const
{
	return this->getUpVector() * -1.0f;
}

const glm::vec3 AAObject::getRightVector() const
{
	return glm::cross(this->getForwardVector(), this->getUpVector());
}

const glm::vec3 AAObject::getLeftVector() const
{
	return this->getRightVector() * -1.0f;
}

const glm::mat4 AAObject::getObjectTransformationMatrix() const
{
	return this->objectTransformationMatrix;
}

const glm::mat4 AAObject::getObjectScaleMatrix() const
{
	return this->objectScaleMatrix;
}

const glm::mat4 AAObject::getObjectRotationMatrix() const
{
	return this->objectRotationMatrix;
}

const char * AAObject::getName()
{
	return this->name;
}


//Member function **********************************************************
void AAObject::moveForward(float scalar)
{
	this->setPosition(this->getPosition() + this->getForwardVector()*scalar);
}
void AAObject::moveBackward(float scalar)
{
	this->setPosition(this->getPosition() + this->getBackwardVector()*scalar);
}
void AAObject::moveLeft(float scalar)
{
	this->setPosition(this->getPosition() + this->getLeftVector()*scalar);
}
void AAObject::moveRight(float scalar)
{
	this->setPosition(this->getPosition() + this->getRightVector()*scalar);
}

void AAObject::rotate(float degree, glm::vec3 vect)
{
	
	this->forward = glm::mat3(glm::rotate(degree, vect)) * this->forward;
	this->up = glm::mat3(glm::rotate(degree, vect)) * this->up;
	this->objectRotationMatrix = glm::rotate(degree, vect)*this->objectRotationMatrix;
	//this->objectRotationMatrix = glm::lookAt(this->getPosition(), this->getForwardVector() - this->getPosition(), this->up);
}

void AAObject::rotateUp(float degree)
{
	this->rotate(degree, this->getRightVector());
}

void AAObject::rotateDown(float degree)
{
	this->rotate(-degree, this->getRightVector());
}

void AAObject::rotateLeft(float degree)
{
	this->rotate(degree, this->getUpVector());
}

void AAObject::rotateRight(float degree)
{
	this->rotate(-degree, this->getUpVector());
}

