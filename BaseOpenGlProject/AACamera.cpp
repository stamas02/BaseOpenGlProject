#include "AACamera.h"


AACamera::AACamera()
{
	glm::mat4 modelTransformationMatrix;
	glm::mat4 projectionMatrix;
	this->worldTransformationMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.0f, 0.0f, 0.0f));
	this->worldProjectionMatrix = glm::perspective(60.0f, 1024.0f / 768.0f, 1.0f, 100.0f);
	this->worldRotationMatrix = glm::rotate(glm::mat4(), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	this->forward = this->globalForward;
	this->right = this->globalRight;
	this->up = this->globalUp;
}

AACamera::AACamera(glm::mat4 modelTransformationMatrix, glm::mat4 projectionMatrix)
{
	this->worldTransformationMatrix = modelTransformationMatrix;
	this->worldProjectionMatrix = projectionMatrix;
}

AACamera::~AACamera()
{

}

void AACamera::setPosition(glm::vec3 position)
{
	this->position = position;
	this->worldTransformationMatrix = glm::translate(glm::mat4(1.f), this->position);
}

void AACamera::setWorldTransformationMatrix(glm::mat4 modelTransformationMatrix)
{
	this->worldTransformationMatrix = modelTransformationMatrix;
}
void AACamera::setWorldProjectionMatrix(glm::mat4 pojectionMatrix)
{
	this->worldProjectionMatrix = pojectionMatrix;
}


//Getters
const glm::vec3 AACamera::getPosition() const
{
	return this->position;
}
const glm::vec3 AACamera::getForwardVector() const
{
	return this->forward;
}
const glm::vec3 AACamera::getBackwardVector() const
{
	return this->forward*-1.0f;
}
const glm::vec3 AACamera::getRightVector() const
{
	return this->right*1.0f;
}
const glm::vec3 AACamera::getLeftVector() const
{
	return this->right*-1.0f;
}

const glm::mat4 AACamera::getWorldTransformationMatrix() const
{
	return this->worldTransformationMatrix;
}
const glm::mat4 AACamera::getWorldProjectionMatrix() const
{
	return this->worldProjectionMatrix;
}
const glm::mat4 AACamera::getWorldRotationMatrix() const
{
	return this->worldRotationMatrix;
}


void AACamera::moveForward(float scalar)
{
	this->setPosition(this->getPosition() + this->getForwardVector()*scalar);
}
void AACamera::moveBackward(float scalar)
{
	this->setPosition(this->getPosition() + this->getBackwardVector()*scalar);
}
void AACamera::moveLeft(float scalar)
{
	this->setPosition(this->getPosition() + this->getLeftVector()*scalar);
}
void AACamera::moveRight(float scalar)
{
	this->setPosition(this->getPosition() + this->getRightVector()*scalar);
}

void AACamera::rotate(float degree, glm::vec3 vect)
{
	this->forward = glm::mat3(glm::rotate(degree, vect)) * this->forward;
	this->up = glm::mat3(glm::rotate(degree, vect)) * this->up;
	this->right = glm::mat3(glm::rotate(degree, vect)) * this->right;
	this->worldRotationMatrix = glm::rotate(-degree, vect)*this->worldRotationMatrix;
}

void AACamera::rotateUp(float degree)
{
	this->rotate(degree, this->globalRight);
}

void AACamera::rotateDown(float degree)
{
	this->rotate(-degree, this->globalRight);
}

void AACamera::rotateLeft(float degree)
{
	this->rotate(degree, this->globalUp);
}

void AACamera::rotateRight(float degree)
{
	this->rotate(-degree, this->globalUp);
}
