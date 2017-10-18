#pragma once
#include<string>
#include<GL/glew.h>
#include"Transform.h"
#include"Camera.h"
using namespace std;
class Shader
{
public:
	Shader(const string& fileName);

	void Bind();

	void Update(const Transform& transform,const Camera& camera);

	~Shader();
private:
	static const unsigned int NUM_SHADERS = 2;
	enum
	{
		TRANSFORM_U,
		NUM_UNIFORM
	};
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
	GLuint m_uniforms[NUM_UNIFORM];
};
