#pragma once

#include <vector>
#include <glm/glm.hpp>

class AAObject;
class AAModel;
class AAHelper
{
public:
	AAHelper();
	~AAHelper();

	static AAObject* findObjectInListByName(char * name, std::vector<AAObject* > objs);

	static glm::vec3 CalculateModelCenter(AAModel*);
};

