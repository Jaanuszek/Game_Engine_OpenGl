#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

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
#include "Texture.h"

#include "tests/TestClearColor.h"


enum class RenderObject {
	Cube,
	Pyramid
};

void SetupRenderObjects(RenderObject object, VAO& vao, VBO& vbo, VBL& layout, EBO& ebo);


float verticesCube[] = {
	-0.5f,-0.5f,-0.5f, 0.0f,0.0f, 1.0f,0.0f,0.0f, //left bottom back 0
	0.5f, -0.5f,-0.5f, 1.0f,0.0f, 0.0f,1.0f,0.0f, //right bottom back 1
	0.5f,  0.5f,-0.5f, 1.0f,1.0f, 0.0f,0.0f,1.0f, //right top back 2
	-0.5f, 0.5f,-0.5f, 0.0f,1.0f, 0.5f,0.5f,0.5f, //left top back 3

	-0.5f,-0.5f,0.5f, 0.0f,0.0f, 0.2f,0.5f,0.7f, //left bottom front 4
	0.5f, -0.5f,0.5f, 1.0f,0.0f, 1.0f,1.0f,0.0f, //right bottom front 5
	0.5f,  0.5f,0.5f, 1.0f,1.0f, 0.0f,1.0f,1.0f, //right top front	6
	-0.5f, 0.5f,0.5f, 0.0f,1.0f, 0.7f,0.5f,0.2f //left top front	7
};

unsigned int indicesCube[] = {
	//back wall
	0,1,2,
	2,3,0,
	//front wall
	4,5,6,
	6,7,4,
	//left wall
	0,3,7,
	7,4,0,
	//right wall
	1,2,6,
	6,5,1,
	//bottom wall
	0,1,5,
	5,4,0,
	//top wall
	3,2,6,
	6,7,3
};

float verticesPyramid[] = {
	//adding colors as layout 2
	-0.5f,-0.5f,-0.5f,0.0f,0.0f, 1.0f,0.0f,0.0f, //left bottom back 0
	0.5f,-0.5f,-0.5f,1.0f,0.0f, 0.0f, 1.0f, 0.0f, //right bottom back 1
	0.5f,0.5f,-0.5f,1.0f,1.0f, 0.0f, 0.0f,1.0f, //right top back 2
	-0.5f,0.5f,-0.5f,0.0f,1.0f, 0.5f,0.5f,0.5f, //left top back 3

	0.0f,0.0f,0.5f,0.5f,0.5f, 1.0f,1.0f,0.0f //top of the pyramid 4
};
unsigned int indicesPyramid[] = {
	//back wall
	0,1,2,
	2,3,0,
	//left wall
	0,3,4,
	//right wall
	1,2,4,
	//front wall
	0,1,4,
	2,3,4
};

int main() {
	if (!glfwInit())
		return -1;


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(960, 540, "Game Engine", NULL, NULL);
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
			-0.5f, -0.5f, 0.0f, 0.0f,
			0.5f, -0.5f, 1.0f, 0.0f, 
			0.5f, 0.5f, 1.0f, 1.0f, 
			-0.5f, 0.5f, 0.0f, 1.0f
		};

		unsigned int indices[] = {
			0,1,2,
			2,3,0
		};



		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
		GLCall(glEnable(GL_DEPTH_TEST));

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui::StyleColorsDark();
		ImGui_ImplOpenGL3_Init((char*)glGetString(330));

		VAO vao1;
		//cube
		VBO vbo1(verticesCube, 8 * 8 * sizeof(float));
		VBL layout1;
		layout1.Push(GL_FLOAT, 3);
		layout1.Push(GL_FLOAT, 2);
		layout1.Push(GL_FLOAT, 3);
		vao1.AddBuffer(vbo1, layout1);
		EBO ebo1(indicesCube, 36);

		VAO vao2;
		//pyramid
		VBO vbo2(verticesPyramid, 5 * 8 * sizeof(float));
		VBL layout2;
		layout2.Push(GL_FLOAT, 3);
		layout2.Push(GL_FLOAT, 2);
		layout2.Push(GL_FLOAT, 3);
		vao2.AddBuffer(vbo2, layout2);
		EBO ebo2(indicesPyramid, 18);

		//glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
		//glm::perspective(fov, aspect, near, far)
		//ascpet = width/height
		//near  - how close to the camera
		//far - how far from the camera
		//glm::mat4 proj = glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f); // first step
		//moving object slightly backwards in the scene
		//if we want to move object to the right we need to move the camera to the left if backwards to the front and so on
		//
		//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -3.0f)); // third step

		Shader shader1("res/shaders/Basic.shader");
		shader1.Bind();
		shader1.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		Texture texture1("res/textures/pudzilla.png");
		texture1.Bind();
		shader1.SetUniform1i("u_Texture", 0);

		Shader shader2("res/shaders/Basic.shader");
		shader2.Bind();
		shader2.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		Texture texture2("res/textures/pudzilla.png");
		texture2.Bind();
		shader2.SetUniform1i("u_Texture", 0);

		vao1.Unbind();
		vao2.Unbind();
		vbo1.Unbind();
		vbo2.Unbind();
		ebo1.Unbind();
		ebo2.Unbind();
		shader1.Unbind();
		shader2.Unbind();

		Renderer renderer;

		float r = 0.0f;
		float increment = 0.01f;

		glm::vec3 translationA(0.0f, 0.0f, 0.0f);
		glm::vec3 viewTranslation(0.0f, 0.0f, -3.0f);
		float angle = 0.0f;

		RenderObject renderObject = RenderObject::Cube;
		bool plsWork = true;

		while (!glfwWindowShouldClose(window)) {
			renderer.Clear();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			{
				glm::mat4 proj = glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f);
				glm::mat4 view = glm::translate(glm::mat4(1.0f), viewTranslation);
				glm::mat4 model = glm::mat4(1.0f); //model is a second step according to book xd
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
				model = glm::translate(model, translationA);

				glm::mat4 mvp = proj * view * model; // mvp - model view projection, due to matrix multiplication is reversed from (right to left)
				if (renderObject == RenderObject::Cube) {
					shader1.Bind();
					shader1.SetUniformMat4f("u_MVP", mvp);
					renderer.Draw(vao1, ebo1, shader1);
				}
				else if (renderObject == RenderObject::Pyramid) {
					shader2.Bind();
					shader2.SetUniformMat4f("u_MVP", mvp);
					renderer.Draw(vao2, ebo2, shader2);
				}
			}

			{
			ImGui::Begin("Jabol");
			if(ImGui::Button("Render Cube")) {
				renderObject = RenderObject::Cube;
			}
			ImGui::SameLine();
			if(ImGui::Button("Render Pyramid")) {
				renderObject = RenderObject::Pyramid;
			}
			ImGui::SliderFloat3("Translation A", &translationA.x, -1.0f, 1.0f);  
			ImGui::SliderFloat("View Translation A x", &viewTranslation.x, -1.0f, 1.0f);
			ImGui::SliderFloat("View Translation A y", &viewTranslation.y, -1.0f, 1.0f);
			ImGui::SliderFloat("View Translation A z", &viewTranslation.z, -10.0f, 10.0f);
			ImGui::SliderFloat("Angle", &angle, 0.0f, 360.0f);
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
			}

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			glfwSwapBuffers(window);

			glfwPollEvents();
		}
	}
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}

void SetupRenderObjects(RenderObject object, VAO& vao, VBO& vbo, VBL& layout, EBO& ebo) {
	//vao.Bind();
	if (object == RenderObject::Cube) {
		VBO vbo(verticesCube, 8 * 8 * sizeof(float));
		VBL layout;
		layout.Push(GL_FLOAT, 3);
		layout.Push(GL_FLOAT, 2);
		layout.Push(GL_FLOAT, 3);
		vao.AddBuffer(vbo, layout);
		EBO ebo(indicesCube, 36);
	}
	else if (object == RenderObject::Pyramid) {
		VBO vbo(verticesPyramid, 5 * 8 * sizeof(float));
		VBL layout;
		layout.Push(GL_FLOAT, 3);
		layout.Push(GL_FLOAT, 2);
		layout.Push(GL_FLOAT, 3);
		vao.AddBuffer(vbo, layout);
		EBO ebo(indicesPyramid, 18);
	}
}