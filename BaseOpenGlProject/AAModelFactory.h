#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <tuple>

using namespace std;
using FaceModel = std::tuple < std::tuple <int, int, int>, std::tuple <int, int, int>, std::tuple <int, int, int> >;

class AAModel;

struct VectorData
{
public:
	VectorData(int size, void* data)
	{
		this->size = size;
		this->data = data;
	}
	int size = 0;
	void * data;
};

class AAModelFactory
{
public:
	AAModelFactory();
	~AAModelFactory();

	std::vector<AAModel*> CreateModel(const char* filePath, AAModel* root);

private:	

	void buildChildParentTransformations(std::vector<AAModel*> childs, AAModel* parent);


	template<class T>
	static FaceModel stringToFace(string sface);
	static std::vector<glm::vec3> convertToPureVertecies(std::vector<glm::vec4>& vertices,
		std::vector<glm::vec2>& uvs,
		std::vector<glm::vec3> normals,
		std::vector<FaceModel> faces);

};

