#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class AAWorld
{
public:
	AAWorld();
	~AAWorld();

	static glm::vec3 getForwardVector();
	static glm::vec3 getUpVector();

private:
	static glm::vec3 up;
	static glm::vec3 forward;
};

