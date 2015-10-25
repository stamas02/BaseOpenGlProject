#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "AAObject.h"

class AACamera : public AAObject
{
public:
	AACamera(const char * name);
	~AACamera();

	//setters
	void setWorldProjectionMatrix(glm::mat4 projectionMatrix);

	//getters
	const glm::mat4 getWorldTransformationMatrix() const;
	const glm::mat4 getWorldProjectionMatrix() const;
	const glm::mat4 getWorldRotationMatrix() const;


	void rotate(float degree, glm::vec3 vect) override;
	void rotateUp(float degree) override;
	void rotateDown(float degree) override;
	void rotateLeft(float degree) override;
	void rotateRight(float degree) override;


	void update() override{};

private:
	glm::mat4 worldProjectionMatrix;

};

