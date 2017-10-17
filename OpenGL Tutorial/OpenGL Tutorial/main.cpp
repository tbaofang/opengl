#include<iostream>
#include"Display.h"
#include<GL/glew.h>
#include"Mesh.h"
#include"Shader.h"
using namespace std;

int main(int argc,char** argv)
{
	Display display(800, 600, "aaaaaaaaaa");

	Vertex vertices[] = { Vertex(glm::vec3(-0.5,-0.5,0)),
		Vertex(glm::vec3(0,0.5,0)),
		Vertex(glm::vec3(0.5,-0.5,0)) };
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	Shader shader("./res/basicShader");
	//Shader shader("basicShader");


	while (!display.isClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);
		
		shader.Bind();
		mesh.Draw();

		display.Update();
	}
	return 0;
}