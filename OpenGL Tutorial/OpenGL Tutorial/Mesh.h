#pragma once
#include<glm/glm.hpp>
#include<GL/glew.h>

class Vertex
{
public:
	Vertex(const glm::vec3& pos) {
		this->pos = pos;
	}
private:
	glm::vec3 pos;
};

class Mesh
{
public:
	Mesh(Vertex* veritces, unsigned int numVertices);
	void Draw();
	~Mesh();
private:
	enum
	{
		POSITION_VB,
		NUM_BUFFERS
	};
	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};