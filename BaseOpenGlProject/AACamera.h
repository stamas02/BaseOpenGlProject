#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "AAObject.h"

class AACamera : public AAObject
{
public:
	AACamera();
	~AACamera();

	//setters
	void setWorldProjectionMatrix(glm::mat4 projectionMatrix);

	//getters
	const glm::mat4 getWorldTransformationMatrix() const;
	const glm::mat4 getWorldProjectionMatrix() const;
	const glm::mat4 getWorldRotationMatrix() const;


	void rotateUp(float degree) override;
	void rotateDown(float degree) override;
	void rotateLeft(float degree) override;
	void rotateRight(float degree) override;

private:
	glm::mat4 worldProjectionMatrix;

};

