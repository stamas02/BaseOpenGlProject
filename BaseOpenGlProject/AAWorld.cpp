#include "AAWorld.h"


glm::vec3 AAWorld::up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 AAWorld::forward = glm::vec3(0.0f, 0.0f, 1.0f);

AAWorld::AAWorld()
{
}


AAWorld::~AAWorld()
{
}


glm::vec3 AAWorld::getForwardVector()
{
	return AAWorld::forward;
}
glm::vec3 AAWorld::getUpVector()
{
	return AAWorld::up;
}

