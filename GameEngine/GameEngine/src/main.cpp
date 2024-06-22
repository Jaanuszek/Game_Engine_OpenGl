#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "Renderer.h"
#include "VBO.h"
#include "VBL.h"
#include "EBO.h"
#include "VAO.h"
#include "Shader.h"

int main() {
	if (!glfwInit())
		return -1;


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 600, "Game Engine", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	gladLoadGL();
	{
		float vertices[] = {
			-0.5f, -0.5f, //0
			 0.5f,  -0.5f, //1
			 0.5f, 0.5f, //2
			 -0.5f, 0.5f, //3
		};

		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};

		VAO vao;
		VBO vbo(vertices, 8 * sizeof(float));

		VBL layout;
		layout.Push(GL_FLOAT,2);
		vao.AddBuffer(vbo, layout);

		EBO ebo(indices, 6);

		Shader shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		vao.Unbind();
		vbo.Unbind();
		ebo.Unbind();
		shader.Unbind();

		Renderer renderer;


		float r = 0.0f;
		float increment = 0.01f;
		while (!glfwWindowShouldClose(window)) {
			renderer.Clear();

			shader.Bind();
			shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

			renderer.Draw(vao,ebo,shader);


			if (r > 1.0f) {
				increment = -0.01f;
			}
			else if (r < 0.0f) {
				increment = 0.01f;
			}
			r += increment;

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}