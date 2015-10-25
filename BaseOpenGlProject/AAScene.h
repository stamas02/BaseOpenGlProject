#pragma once
#include <vector>
#include "AAModel.h"
#include "AACamera.h"


class AAScene
{
public:
	AAScene();
	~AAScene();
	const AACamera* getAciveCamera() const;
	const std::vector<AAModel*> getModels() const;
	virtual void update() = 0;

protected:

	AACamera* camera;
	std::vector<AAModel*> objects;

};

