#pragma once
#include "AAModel.h"

class MyCube : public AAModel
{
public:
	MyCube(char * name);
	~MyCube();
	void update();

private:
	AAModel* front_left_wheel;
	AAModel* front_right_wheel;
	AAModel* rear_left_wheel;
	AAModel* rear_right_wheel;

};

