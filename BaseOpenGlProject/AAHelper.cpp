#include "AAHelper.h"
#include "AAObject.h"
#include "AAModel.h"

AAHelper::AAHelper()
{
}


AAHelper::~AAHelper()
{
}


AAObject* AAHelper::findObjectInListByName(char * name, std::vector<AAObject* > objs)
{
	for (AAObject* obj : objs){
		if (obj->getName() == name)
			return obj;
	}
	return nullptr;
}

glm::vec3 AAHelper::CalculateModelCenter(AAModel* model)
{
	glm::vec3 result(0, 0, 0);
	long num = 0;
	std::vector<glm::vec4> verecies = model->getVerecies();
	for (glm::vec4 vect : verecies)
	{
		result.x += vect.x;
		result.y += vect.y;
		result.z += vect.z;
		num++;
		if (num >= 100)
		{
			result.x /= num;
			result.y /= num;
			result.z /= num;
			num = 1;
		}
	}
	result.x /= num;
	result.y /= num;
	result.z /= num;
	return result;
}