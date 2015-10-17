#pragma once

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <tuple>

using namespace std;
using FaceModel = std::tuple < std::tuple <int, int, int>, std::tuple <int, int, int>, std::tuple <int, int, int> >;


class AAModelLoader
{
public:
	AAModelLoader();
	~AAModelLoader();
	std::vector<glm::vec3> LoadObj(const char*);

private:	
	glm::vec3 stringToVector(string svector);
	FaceModel stringToFace(string sface);
	std::vector<glm::vec3> convertToPureVertecies(std::vector<glm::vec3>& vertices,
		std::vector<glm::vec3>& uvs,
		std::vector<glm::vec3> normals,
		std::vector<FaceModel> faces);

};

