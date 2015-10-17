#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "AAObject.h"

class AACamera : AAObject
{
public:
	AACamera(glm::mat4 modelTransformationMatrix, glm::mat4 projectionMatrix);
	AACamera();
	~AACamera();

	//setters
	void setPosition(glm::vec3 position);
	void setWorldTransformationMatrix(glm::mat4 modelTransformationMatrix);
	void setWorldProjectionMatrix(glm::mat4 projectionMatrix);

	//getters
	const glm::vec3 getPosition() const;
	const glm::vec3 getForwardVector() const;
	const glm::vec3 getBackwardVector() const;
	const glm::vec3 getRightVector() const;
	const glm::vec3 getLeftVector() const;
	const glm::mat4 getWorldTransformationMatrix() const;
	const glm::mat4 getWorldProjectionMatrix() const;
	const glm::mat4 getWorldRotationMatrix() const;

	void moveForward(float scalar);
	void moveBackward(float scalar);
	void moveLeft(float scalar);
	void moveRight(float scalar);
	void rotate(float degree, glm::vec3 vect);
	void rotateUp(float degree);
	void rotateDown(float degree);
	void rotateLeft(float degree);
	void rotateRight(float degree);

private:
	glm::mat4 worldTransformationMatrix;
	glm::mat4 worldRotationMatrix;
	glm::mat4 worldProjectionMatrix;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;

	const glm::vec3 globalUp = glm::vec3(0.0f, 1.0f, 0.0f);
	const glm::vec3 globalRight = glm::vec3(1.0f, 0.0f, 0.0f);
	const glm::vec3 globalForward = glm::vec3(0.0f, 0.0f, 1.0f);

};

