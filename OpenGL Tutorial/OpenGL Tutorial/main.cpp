#include<iostream>
#include"Display.h"
#include<GL/glew.h>
#include"Mesh.h"
#include"Shader.h"
#include"Transform.h"
#include"Camera.h"
using namespace std;

#define WIDTH 800
#define HEIGHT 600

int main(int argc,char** argv)
{
	Display display(800, 600, "aaaaaaaaaa");

	Vertex vertices[] = { Vertex(glm::vec3(-0.5,-0.5,0)),
		Vertex(glm::vec3(0,0.5,0)),
		Vertex(glm::vec3(0.5,-0.5,0)) };
	Mesh mesh(vertices, sizeof(vertices) / sizeof(vertices[0]));

	Shader shader("./res/basicShader");
	Camera camera(glm::vec3(0, 0, -3), 70.0f, (float)WIDTH / (float)HEIGHT, 0.01f, 1000.0f);
	
	Transform transform;

	float counter = 0.0f;
	while (!display.isClosed())
	{
		display.Clear(0.0f, 0.15f, 0.3f, 1.0f);

		float sinCounter = sinf(counter);
		float cosCounter = cos(counter);

		transform.GetPos()->x = sinCounter;
		transform.GetPos()->y = sinCounter;
		transform.GetPos()->z = sinCounter;

		transform.GetRot()->x = counter * 100;
		transform.GetRot()->y = counter * 100;
		transform.GetRot()->z = counter * 100;

		transform.SetScale(glm::vec3(cosCounter, cosCounter, cosCounter));
		
		shader.Bind();

		shader.Update(transform,camera);
		mesh.Draw();


		display.Update();

		counter += 0.01f;
	}
	return 0;
}