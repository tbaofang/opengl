#pragma once
#include<string>
#include<GL/glew.h>
using namespace std;
class Shader
{
public:
	Shader(const string& fileName);

	void Bind();

	~Shader();
private:
	static const unsigned int NUM_SHADERS = 2;
	GLuint m_program;
	GLuint m_shaders[NUM_SHADERS];
};
