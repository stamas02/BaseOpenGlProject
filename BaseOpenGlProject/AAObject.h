#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class AAObject
{
public:
	AAObject();
	~AAObject();

	//setters
	void setPosition(glm::vec3 position);
	void setObjectTransformationMatrix(glm::mat4 modelTransformationMatrix);
	void setObjectRotationMatrix(glm::mat4 objectRotationMatrix);
	void setObjectScaleMatrix(glm::mat4 objectScaleMatrix);

	//getters
	const glm::vec3 getPosition() const;
	const glm::vec3 getForwardVector() const;
	const glm::vec3 getBackwardVector() const;
	const glm::vec3 getRightVector() const;
	const glm::vec3 getLeftVector() const;
	const glm::mat4 getWorldTransformationMatrix() const;
	const glm::mat4 getWorldProjectionMatrix() const;
	const glm::mat4 getWorldRotationMatrix() const;


	virtual void moveForward(float scalar);
	virtual void moveBackward(float scalar);
	virtual void moveLeft(float scalar);
	virtual void moveRight(float scalar);
	virtual void rotate(float degree, glm::vec3 vect);
	virtual void rotateUp(float degree);
	virtual void rotateDown(float degree);
	virtual void rotateLeft(float degree);
	virtual void rotateRight(float degree);

protected:
	glm::mat4 objectTransformationMatrix;
	glm::mat4 objectRotationMatrix;
	glm::mat4 objectScaleMatrix;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 right;
	glm::vec3 up;
};

