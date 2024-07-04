#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>
//#include <fstream>
//#include <string>
//#include <sstream>

#include "Renderer.h"
#include "VBO.h"
#include "VBL.h"
#include "EBO.h"
#include "VAO.h"
#include "Shader.h"
#include "Texture.h"

#include "Cube.h"
#include "Pyramid.h"
#include "Sphere.h"

#include "Camera.h"

#include "tests/TestClearColor.h"


enum class RenderObject {
	Cube,
	Pyramid,
	Sphere
};

void SetupRenderObjects(RenderObject object, VAO& vao, VBO& vbo, VBL& layout, EBO& ebo);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);

Cube cube;
const float *verticesCube = cube.GetVertices();
const unsigned int* indicesCube = cube.GetIndices();
Pyramid pyramid;
const float* verticesPyramid = pyramid.GetVertices();
const unsigned int* indicesPyramid = pyramid.GetIndices();

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool cameraOn = false;

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

		vao1.Unbind();
		vbo1.Unbind();
		ebo1.Unbind();
		shader1.Unbind();

		Sphere sphere(1.0f,24,48);
		std::vector<float> verticesSphere = sphere.GetVertices();
		std::vector<unsigned int> indicesSphere= sphere.GetIndices();
		VAO vaoSphere;
		VBO vboSphere(verticesSphere.data(), verticesSphere.size() * sizeof(float));
		VBL layoutSphere;
		layoutSphere.Push(GL_FLOAT, 3);
		layoutSphere.Push(GL_FLOAT, 3);
		vaoSphere.AddBuffer(vboSphere, layoutSphere);
		EBO eboSphere(indicesSphere.data(), indicesSphere.size());

		Shader shaderSphere("res/shaders/Sphere.shader");
		shaderSphere.Bind();

		vaoSphere.Unbind();
		vboSphere.Unbind();
		eboSphere.Unbind();
		shaderSphere.Unbind();

		Renderer renderer;

		float r = 0.0f;
		float increment = 0.01f;

		glm::vec3 translationA(0.0f, 0.0f, 0.0f);
		glm::vec3 viewTranslation(0.0f, 0.0f, -3.0f);
		float angle = 0.0f;

		RenderObject renderObject = RenderObject::Cube;

		Camera camera(glm::vec3(0.0f,0.0f,3.0f), translationA);
		//glfwSetWindowUserPointer(window, &camera);
		//glfwSetCursorPosCallback(window, mouse_callback);

		//glfwSetWindowUserPointer(window, &camera);
		//glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
		//	void* userPointer = glfwGetWindowUserPointer(window);
		//	static_cast<Camera*>(userPointer)->mouse_callback(window, xpos, ypos);
		//	});
		//glfwMakeContextCurrent(window);
		//glfwSwapInterval(1);

		while (!glfwWindowShouldClose(window)) {


			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			renderer.Clear();
			if (cameraOn) {
				//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				camera.processInput(window,deltaTime);
			}
			else {
				//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			{
				glm::mat4 proj = glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 100.0f);
				glm::mat4 view;
				glm::mat4 model = glm::mat4(1.0f); //model is a second step according to book xd
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
				model = glm::translate(model, translationA);
				glm::mat4 mvp;
				if (!cameraOn) {
					view = glm::translate(glm::mat4(1.0f), viewTranslation);
					mvp = proj * view * model;
				}
				else {
					camera.mouse_callback(window, 960.0f / 2.0f, 540.0f / 2.0f);
					mvp = camera.CalculateMVP(proj, model);
				}

				if (renderObject != RenderObject::Sphere) {
					shader1.Bind();
					shader1.SetUniformMat4f("u_MVP", mvp);
					renderer.Draw(vao1, ebo1, shader1);
				}
				else {
					shaderSphere.Bind();
					shaderSphere.SetUniformMat4f("u_MVP", mvp);
					renderer.Draw(vaoSphere, eboSphere, shaderSphere);
				}
			}

			{
			ImGui::Begin("Jabol");
			if (ImGui::Button("Camera On/Off")) {
				cameraOn = !cameraOn;
			}
			if(ImGui::Button("Render Cube")) {
				renderObject = RenderObject::Cube;
				SetupRenderObjects(renderObject, vao1, vbo1, layout1, ebo1);
			}
			ImGui::SameLine();
			if(ImGui::Button("Render Pyramid")) {
				renderObject = RenderObject::Pyramid;
				SetupRenderObjects(renderObject, vao1, vbo1, layout1, ebo1);
			}
			ImGui::SameLine();
			if (ImGui::Button("Render Sphere")) {
				renderObject = RenderObject::Sphere;
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
	if (object == RenderObject::Cube) {
		vbo.Update(verticesCube, 8 * 8 * sizeof(float));
		ebo.Update(indicesCube, 36);
	}
	else if (object == RenderObject::Pyramid) {
		vbo.Update(verticesPyramid, 5 * 8 * sizeof(float));
		ebo.Update(indicesPyramid, 18);
	}
}

//void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
//	Camera* camera = static_cast<Camera*>(glfwGetWindowUserPointer(window));
//	if (camera) {
//		camera->mouse_callback(window, xpos, ypos);
//	}
//}