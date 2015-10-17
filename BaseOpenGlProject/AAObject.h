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
	const virtual glm::vec3 getPosition() const;
	const virtual glm::vec3 getForwardVector() const;
	const virtual glm::vec3 getBackwardVector() const;
	const virtual glm::vec3 getUpVector() const;
	const virtual glm::vec3 getDownVector() const;
	const virtual glm::vec3 getRightVector() const;
	const virtual glm::vec3 getLeftVector() const;
	const virtual glm::mat4 getObjectTransformationMatrix() const;
	const virtual glm::mat4 getObjectScaleMatrix() const;
	const virtual glm::mat4 getObjectRotationMatrix() const;


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
	glm::vec3 up;
};

