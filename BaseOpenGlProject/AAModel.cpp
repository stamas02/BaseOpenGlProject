#include "AAModel.h"


AAModel::AAModel(const char* name) : AAObject(name)
{

}


AAModel::~AAModel()
{
}

void AAModel::setVerecies(std::vector<glm::vec4> vertices)
{
	this->vertices = vertices;
}
void AAModel::setUvs(std::vector<glm::vec2> uvs)
{
	this->uvs = uvs;
}
void AAModel::setNormals(std::vector<glm::vec3> normals)
{
	this->normals = normals;
}


std::vector<glm::vec4> AAModel::getVerecies()
{
	return this->vertices;
}
std::vector<glm::vec2> AAModel::getUvs()
{
	return this->uvs;
}
std::vector<glm::vec3> AAModel::getNormals()
{
	return this->normals;
}

void AAModel::prepareToBeDrawn()
{
	glBindBuffer(GL_ARRAY_BUFFER, this->myOpenGlBufferObject);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0);
}

void AAModel::loadIntoOpenGl()
{
	/* Create a vertex buffer object to store vertices */
	glGenBuffers(1, &this->myOpenGlBufferObject);
	glBindBuffer(GL_ARRAY_BUFFER, this->myOpenGlBufferObject);
	glBufferData(GL_ARRAY_BUFFER, sizeof(this->vertices[0]) * this->vertices.size(), &this->vertices[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

std::vector<AAModel*> AAModel::getChildren()
{
	return this->children;

}
void AAModel::loadModel(char* obj_file)
{
	AAModelFactory factory;
	std::vector<AAModel*> loaded_models = factory.CreateModel(obj_file, this);
	this->children = loaded_models;
}

AAModel* AAModel::getChildByName(const char* name)
{
	for (AAModel* child : this->children){
		if (strcmp(child->getName(),name)==0)
			return child;
	}
	return nullptr;
}
bool AAModel::removeChildrenByName(const char* name)
{
	int idx = -1;
	for (int i = 0; i < this->children.size(); i++){
		if (this->children[i]->getName() == name)
			idx = i;
	}
	if (idx == -1)
		return false;

	this->children.erase(this->children.begin() + idx);

	return true;
}

unsigned long AAModel::getSize()
{
	return this->vertices.size();
}