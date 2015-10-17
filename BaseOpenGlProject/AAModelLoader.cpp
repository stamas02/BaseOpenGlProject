#include "AAModelLoader.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>




AAModelLoader::AAModelLoader()
{
}

std::vector<glm::vec3> AAModelLoader::LoadObj(const char* filePath)
{
	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> uvs;
	std::vector<glm::vec3> normals;
	std::vector<FaceModel> faces;

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		int space_ixd = line.find(' ');
		if (space_ixd > -1)
		{
			string indicator = line.substr(0, space_ixd);
			string content  = line.substr(space_ixd + 1, line.size() - 1);
			try{
				if (indicator == "v"){
					glm::vec3 vector = stringToVector(content);
					vertices.push_back(vector);
				}
				else if (indicator == "vn"){
					glm::vec3 vector = stringToVector(content);
					normals.push_back(vector);
				}
				else if (indicator == "vt"){
					glm::vec3 vector = stringToVector(content);
					uvs.push_back(vector);
				}
				else if (indicator == "f"){
					FaceModel face = stringToFace(content);
					faces.push_back(face);
				}
			}
			catch (string e){
				std::cerr << e << endl;
			}

		}

	}
	fileStream.close();
	return convertToPureVertecies(vertices, uvs, normals, faces);

}

glm::vec3 AAModelLoader::stringToVector(string svector)
{
	glm::vec3 result;
	stringstream ss(svector);
	for (int i = 0; !ss.eof(); i++){
		float val;
		if (!(ss >> val))
			throw "Error reading vertex: Value Error";
		result[i] = val;
	}
	return result;
}
FaceModel AAModelLoader::stringToFace(string sface)
{
	std::replace(sface.begin(), sface.end(), '/', ' ');
	stringstream ss(sface);
	std::vector<int> tmp;
	for (int i = 0; i < 9; i++){
		int val;
		if (!(ss >> val))
			throw "Error reading face: Value Error";
		tmp.push_back(val);
	}
	std::tuple <int, int, int> vector_face = make_tuple(tmp[0], tmp[1], tmp[2]);
	std::tuple <int, int, int> uv_face = make_tuple(tmp[3], tmp[4], tmp[5]);
	std::tuple <int, int, int> normal_face = make_tuple(tmp[6], tmp[7], tmp[8]);
	return std::make_tuple(vector_face, uv_face, normal_face);
}


std::vector<glm::vec3> AAModelLoader::convertToPureVertecies(std::vector<glm::vec3>& vertices,
	std::vector<glm::vec3>& uvs,
	std::vector<glm::vec3> normals,
	std::vector<FaceModel> faces)
{
	std::vector<glm::vec3> result;
	for (FaceModel face : faces){
			result.push_back(vertices[(int)std::get<0>(std::get<0>(face))-1]);
			result.push_back(uvs[(int)std::get<1>(std::get<0>(face))-1]);
			result.push_back(normals[(int)std::get<2>(std::get<0>(face))-1]);

			result.push_back(vertices[(int)std::get<0>(std::get<1>(face))-1]);
			result.push_back(uvs[(int)std::get<1>(std::get<1>(face))-1]);
			result.push_back(normals[(int)std::get<2>(std::get<1>(face))-1]);

			result.push_back(vertices[(int)std::get<0>(std::get<2>(face))-1]);
			result.push_back(uvs[(int)std::get<1>(std::get<2>(face))-1]);
			result.push_back(normals[(int)std::get<2>(std::get<2>(face))-1]);
	}
	return result;
}


AAModelLoader::~AAModelLoader()
{

}

