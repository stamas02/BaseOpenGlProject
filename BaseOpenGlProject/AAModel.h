#pragma once
#include "AAObject.h"
#include "AAModelFactory.h"
#include <vector>
#include <glload/gl_4_0.h>

class AAModel : public AAObject
{
friend class AAModelFactory;
public:
	AAModel(const char* name);
	~AAModel();
	std::vector<glm::vec4> getVerecies();
	std::vector<glm::vec2> getUvs();
	std::vector<glm::vec3> getNormals();
	AAModel* getChildByName(const char* name);
	bool removeChildrenByName(const char* name);

	unsigned long getSize();
	virtual void update(){}
	void prepareToBeDrawn();
	std::vector<AAModel*> getChildren();

protected:
	void loadModel(char* obj_file);
	std::vector<AAModel*> children;
	GLuint myOpenGlBufferObject;
private:
	void setVerecies(std::vector<glm::vec4> vertices);
	void setUvs(std::vector<glm::vec2> uvs);
	void setNormals(std::vector<glm::vec3> normals);
	void loadIntoOpenGl();
	std::vector<glm::vec4> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;

	

};

