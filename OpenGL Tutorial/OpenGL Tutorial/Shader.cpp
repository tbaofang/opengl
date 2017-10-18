#include<iostream>
#include<fstream>
#include"Shader.h"
using namespace std;

static GLuint CreateShader(const string& text, GLenum shaderType);
static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage);
static string LoadShader(const string& fileName);

Shader::Shader(const string& fileName)
{
	m_program = glCreateProgram();

	m_shaders[0] = CreateShader(LoadShader(fileName + ".vs"),GL_VERTEX_SHADER);
	m_shaders[1] = CreateShader(LoadShader(fileName + ".fs"),GL_FRAGMENT_SHADER);

	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glAttachShader(m_program, m_shaders[i]);
	}
	glLinkProgram(m_program);
	CheckShaderError(m_program, GL_LINK_STATUS, true, "Error:Program Linking Invalid");

	glValidateProgram(m_program);
	CheckShaderError(m_program, GL_VALIDATE_STATUS, true, "Error:Program Validate invalid");

	m_uniforms[TRANSFORM_U] = glGetUniformLocation(m_program, "transform");
}

Shader::~Shader()
{
	for (unsigned int i = 0; i < NUM_SHADERS; i++)
	{
		glDetachShader(m_program, m_shaders[i]);
		glDeleteShader(m_shaders[i]);
	}
	glDeleteProgram(m_program);

}

void Shader::Bind()
{
	glUseProgram(m_program);
}

void Shader::Update(const Transform& transform,const Camera& camera)
{
	glm::mat4 model = camera.GetViewProjection() * transform.GetModel();
	glUniformMatrix4fv(m_uniforms[TRANSFORM_U], 1, GL_FALSE, &model[0][0]);
}

static GLuint CreateShader(const string& text, GLenum shaderType)
{
	GLuint shader = glCreateShader(shaderType);

	if (shader == 0)
	{
		cerr << "Error:Shader creation failure" << endl;
	}

	const GLchar* shaderSourceString[1];
	GLint shaderSourceStringLength[1];
	shaderSourceString[0] = text.c_str();
	shaderSourceStringLength[0] = text.length();

	glShaderSource(shader, 1, shaderSourceString, shaderSourceStringLength);
	glCompileShader(shader);

	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error:Shader compilation failed");

	return shader;

}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const string& errorMessage)
{
	GLint success = 0;
	GLchar error[1024] = { 0 };
	
	if (isProgram)
	{
		glGetProgramiv(shader, flag, &success);

	}
	else
	{
		glGetShaderiv(shader, flag, &success);

	}
	if (success == GL_FALSE)
	{
		if (isProgram)
		{
			glGetProgramInfoLog(shader, sizeof(error), NULL, error);

		}
		else
		{
			glGetShaderInfoLog(shader, sizeof(error), NULL, error);
		}
		cerr << errorMessage << ":'" << error << "'" << endl;
	}
}

static string LoadShader(const string& fileName)
{
	ifstream file;
	file.open((fileName).c_str());

	string output;
	string line;

	if (file.is_open())
	{
		while (file.good())
		{
			getline(file, line);
			output.append(line + "\n");

		}
	}
	else
	{
		cerr << "Unable to load shader:" << fileName << endl;
	}
	return output;
}