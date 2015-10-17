#include "AAObject.h"


AAObject::AAObject()
{
}


AAObject::~AAObject()
{
}

//setters
void AAObject::setPosition(glm::vec3 position)
{
	this->position = position;
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
	/*
	this->forward = glm::mat3(glm::rotate(degree, vect)) * this->forward;
	this->up = glm::mat3(glm::rotate(degree, vect)) * this->up;
	this->right = glm::mat3(glm::rotate(degree, vect)) * this->right;
	this->worldRotationMatrix = glm::rotate(-degree, vect)*this->worldRotationMatrix;
	*/
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
	this->rotate(degree, this->getLeftVector());
}

void AAObject::rotateRight(float degree)
{
	this->rotate(-degree, this->getLeftVector());
}