#include "AAModelFactory.h"
#include "AAModel.h"
#include "AAHelper.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>




AAModelFactory::AAModelFactory()
{
}


std::vector<AAModel*> AAModelFactory::CreateModel(const char* filePath, AAModel* root)
{
	std::vector<AAModel*> models;

	std::string content;
	std::ifstream fileStream(filePath, std::ios::in);

	string currentlyReading = "";

	std::vector<glm::vec4> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec4> total_vertices;
	std::vector<glm::vec2> total_uvs;
	std::vector<glm::vec3> total_normals;

	if (!fileStream.is_open()) {
		std::cerr << "Could not read file " << filePath << ". File does not exist." << std::endl;
	}

	std::string line = "";
	while (!fileStream.eof()) {
		std::getline(fileStream, line);
		try{
			if (line[0] == 'o'){
				if(currentlyReading != ""){
					AAModel* model = nullptr;

					if (strcmp(root->getName(),currentlyReading.c_str())==0) model = root;
					else{
						char* garbage = new char[currentlyReading.size()+1];
						garbage[currentlyReading.size()] = 0;
						memcpy(garbage, currentlyReading.c_str(), currentlyReading.size());
						model = new AAModel(garbage);
					}
					model->setVerecies(total_vertices);
					model->setNormals(total_normals);
					model->setUvs(total_uvs);
					total_vertices.clear();
					total_normals.clear();
					total_uvs.clear();
					if (model != root)
						models.push_back(model);
				}
				currentlyReading = line.erase(0, 2);
			}
			else if ((line[0] == 'v') && (line[1] == 'n')){
				float tmpx, tmpy, tmpz;
				int check = sscanf_s(line.c_str(), "vn %f %f %f", &tmpx, &tmpy, &tmpz);
				if (check != 3)
					throw "Error reading notmal: Value Error";
				normals.push_back(glm::vec3(tmpx, tmpy, tmpz));
			}
			else if ((line[0] == 'v') && (line[1] == 't')){
				float tmpx, tmpy;
				int check = sscanf_s(line.c_str(), "vt %f %f", &tmpx, &tmpy);
				if (check != 2)
					throw "Error reading uv coordinates: Value Error";
				uvs.push_back(glm::vec2(tmpx, tmpy));
			}
			else if (line[0] == 'v'){
				float tmpx, tmpy, tmpz;
				int check = sscanf_s(line.c_str(), "v %f %f %f", &tmpx, &tmpy, &tmpz);
				if (check != 3)
					throw "Error reading vertex: Value Error";
				vertices.push_back(glm::vec4(tmpx, tmpy, tmpz, 1.0f));
			}
			else if (line[0] == 'f'){
				int v_1, v_2, v_3, n_1, n_2, n_3, u_1, u_2, u_3;
				int num = sscanf_s(line.c_str(), "f %i/%i/%i %i/%i/%i %i/%i/%i", &v_1, &u_1, &n_1, &v_2, &u_2, &n_2, &v_3, &u_3, &n_3);
				if (num == 9){
					total_vertices.push_back(vertices[v_1-1]);
					total_vertices.push_back(vertices[v_2-1]);
					total_vertices.push_back(vertices[v_3-1]);
					total_uvs.push_back(uvs[u_1-1]);
					total_uvs.push_back(uvs[u_2-1]);
					total_uvs.push_back(uvs[u_3-1]);
					total_normals.push_back(normals[n_1-1]);
					total_normals.push_back(normals[n_2-1]);
					total_normals.push_back(normals[n_3-1]);
				}
				else{
					num = sscanf_s(line.c_str(), "f %i//%i %i//%i %i//%i", &v_1, &n_1, &v_2, &n_2, &v_3, &n_3);
					if (num == 3){
						total_vertices.push_back(vertices[v_1-1]);
						total_vertices.push_back(vertices[v_2-1]);
						total_vertices.push_back(vertices[v_3-1]);
						total_normals.push_back(normals[n_1-1]);
						total_normals.push_back(normals[n_2-1]);
						total_normals.push_back(normals[n_3-1]);
					}
					else
						throw "Error reading faces: Value Error";
					
				}
			}
		}
		catch (string e){
			std::cerr << e << endl;
		}
	}
	fileStream.close();



	if (currentlyReading != ""){
		AAModel* model = nullptr;

		if (strcmp(root->getName(), currentlyReading.c_str()) == 0) model = root;
		else{
			char* garbage = new char[currentlyReading.size() + 1];
			garbage[currentlyReading.size()] = 0;
			memcpy(garbage, currentlyReading.c_str(), currentlyReading.size());
			model = new AAModel(garbage);
		}
		model->setVerecies(total_vertices);
		model->setNormals(total_normals);
		model->setUvs(total_uvs);
		total_vertices.clear();
		total_normals.clear();
		total_uvs.clear();
		if (model != root)
			models.push_back(model);
	}
	buildChildParentTransformations(models, root);
	for (AAModel * m : models)
		m->loadIntoOpenGl();

	root->loadIntoOpenGl();

	return models;
}

void AAModelFactory::buildChildParentTransformations(std::vector<AAModel*> childs, AAModel* parent)
{
	for (AAModel* model : childs){
		glm::vec3 center =  AAHelper::CalculateModelCenter(model);
		for (int i = 0; i < model->vertices.size(); i++){
			model->vertices[i].x -= center.x;
			model->vertices[i].y -= center.y;
			model->vertices[i].z -= center.z;
		}
		model->setPosition(center);
	}
}
/*
FaceModel AAModelFactory::stringToFace(string sface)
{
	std::vector<int> tmp;
	int num = sscanf(sface.c_str(), "%i/%i/%i %i/%i/%i %i/%i/%i", &tmp[0], &tmp[3], &tmp[6], &tmp[1], &tmp[4], &tmp[7], &tmp[2], &tmp[5], &tmp[8]);
	if (num != 9)
	{
		num = sscanf(sface.c_str(), "%i//%i %i//%i %i//%i", &tmp[0], &tmp[6], &tmp[1], &tmp[7], &tmp[2], &tmp[8]);
		if (num != 6)
			throw "Error reading face: Value Error";
	}
	if (num == 9){
		std::tuple <int, int, int> vector_face = make_tuple(tmp[0], tmp[1], tmp[2]);
		std::tuple <int, int, int> uv_face = make_tuple(tmp[3], tmp[4], tmp[5]);
		std::tuple <int, int, int> normal_face = make_tuple(tmp[6], tmp[7], tmp[8]);
	}


	return std::make_tuple(vector_face, uv_face, normal_face);
}*/


std::vector<glm::vec3> AAModelFactory::convertToPureVertecies(std::vector<glm::vec4>& vertices,
	std::vector<glm::vec2>& uvs,
	std::vector<glm::vec3> normals,
	std::vector<FaceModel> faces)
{
	std::vector<glm::vec3> result;
	for (FaceModel face : faces){/*
			result.push_back(vertices[(int)std::get<0>(std::get<0>(face))-1]);
			result.push_back(uvs[(int)std::get<1>(std::get<0>(face))-1]);
			result.push_back(normals[(int)std::get<2>(std::get<0>(face))-1]);

			result.push_back(vertices[(int)std::get<0>(std::get<1>(face))-1]);
			result.push_back(uvs[(int)std::get<1>(std::get<1>(face))-1]);
			result.push_back(normals[(int)std::get<2>(std::get<1>(face))-1]);

			result.push_back(vertices[(int)std::get<0>(std::get<2>(face))-1]);
			result.push_back(uvs[(int)std::get<1>(std::get<2>(face))-1]);
			result.push_back(normals[(int)std::get<2>(std::get<2>(face))-1]);*/
	}
	return result;
}


AAModelFactory::~AAModelFactory()
{

}

