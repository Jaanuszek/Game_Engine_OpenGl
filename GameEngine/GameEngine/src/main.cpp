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
void keyboard_callback(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

float width = 960.0f;
float height = 540.0f;

Cube cube;
const float *verticesCube = cube.GetVertices();
const unsigned int* indicesCube = cube.GetIndices();
Pyramid pyramid;
const float* verticesPyramid = pyramid.GetVertices();
const unsigned int* indicesPyramid = pyramid.GetIndices();


glm::vec3 translationA(0.0f, 0.0f, 0.0f);
glm::vec3 viewTranslation(0.0f, 0.0f, -3.0f);
glm::vec3 lightCubeTranslation(-1.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f), translationA);
bool cameraOn = false;
bool firstMouse = true;
float lastX = width / 2.0f;
float lastY = height / 2.0f;

int main() {
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(width, height, "Game Engine", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetKeyCallback(window, key_callback);
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
		VBO vbo1(verticesCube, cube.GetVerticesSize()* sizeof(float));
		VBL layout1;
		layout1.Push(GL_FLOAT, 3);
		layout1.Push(GL_FLOAT, 2);
		layout1.Push(GL_FLOAT, 3);
		vao1.AddBuffer(vbo1, layout1);
		EBO ebo1(indicesCube, cube.GetIndicesSize());

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
		//shader1.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

		Texture texture1("res/textures/monkey.png");
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
		layoutSphere.Push(GL_FLOAT, 2);
		layoutSphere.Push(GL_FLOAT, 3);
		vaoSphere.AddBuffer(vboSphere, layoutSphere);
		EBO eboSphere(indicesSphere.data(), indicesSphere.size());

		Shader shaderSphere("res/shaders/Sphere.shader");
		shaderSphere.Bind();

		Texture textureSphere("res/textures/monkey.png");
		textureSphere.Bind();
		shaderSphere.SetUniform1i("u_Texture", 0);

		vaoSphere.Unbind();
		vboSphere.Unbind();
		eboSphere.Unbind();
		shaderSphere.Unbind();

		VAO lightCubeVAO;
		VBO lightCubeVBO(verticesCube, cube.GetVerticesSize() * sizeof(float));
		VBL lightCubeLayout;
		lightCubeLayout.Push(GL_FLOAT, 3);
		lightCubeLayout.Push(GL_FLOAT, 2);
		lightCubeLayout.Push(GL_FLOAT, 3);
		lightCubeVAO.AddBuffer(lightCubeVBO, lightCubeLayout);
		EBO lightCubeEBO(indicesCube, cube.GetIndicesSize());

		Shader lightCubeShader("res/shaders/LightCube.shader");
		lightCubeShader.Bind();
		lightCubeShader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

		lightCubeVAO.Unbind();
		lightCubeVBO.Unbind();
		lightCubeEBO.Unbind();
		lightCubeShader.Unbind();

		Renderer renderer;

		float r = 0.0f;
		float increment = 0.01f;

		float angle = 0.0f;

		RenderObject renderObject = RenderObject::Cube;

		while (!glfwWindowShouldClose(window)) {

			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			renderer.Clear();

			if (cameraOn) {
				keyboard_callback(window);
			}
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();
			{
				glm::mat4 proj = glm::perspective(glm::radians(45.0f), width / height, 0.1f, 100.0f);
				glm::mat4 view;
				glm::mat4 model = glm::mat4(1.0f); //model is a second step according to book xd
				model = glm::rotate(model, glm::radians(angle), glm::vec3(0.5f, 1.0f, 0.0f));
				model = glm::translate(model, translationA);
				glm::mat4 mvp;
				//light cube
				glm::mat4 viewLightCube = glm::translate(glm::mat4(1.0f), glm::vec3(-0.0f, 0.0f, -3.0f));
				glm::mat4 modelLightCube = glm::translate(glm::mat4(1.0f), lightCubeTranslation);
				modelLightCube = glm::scale(modelLightCube, glm::vec3(0.2f));
				glm::mat4 mvpLightCube;
				if (!cameraOn) {
					view = glm::translate(glm::mat4(1.0f), viewTranslation);
					mvp = proj * view * model;
					mvpLightCube = proj * viewLightCube * modelLightCube;
					lightCubeShader.Bind();
					lightCubeShader.SetUniformMat4f("u_MVP", mvpLightCube);
					renderer.Draw(lightCubeVAO, lightCubeEBO, lightCubeShader);
				}
				else {
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
			ImGui::SliderFloat3("Light Cube Translation x", &lightCubeTranslation.x, -1.0f, 1.0f);
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
		vbo.Update(verticesCube, cube.GetVerticesSize() * sizeof(float));
		ebo.Update(indicesCube, cube.GetIndicesSize());
	}
	else if (object == RenderObject::Pyramid) {
		vbo.Update(verticesPyramid, pyramid.GetVerticesSize()* sizeof(float));
		ebo.Update(indicesPyramid, pyramid.GetIndicesSize());
	}
}

void keyboard_callback(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.processInput(Camera_Movement::FORWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.processInput(Camera_Movement::BACKWARD, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.processInput(Camera_Movement::LEFT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.processInput(Camera_Movement::RIGHT, deltaTime);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		camera.processInput(Camera_Movement::ACCELERATION, deltaTime);
	}
	else {
		camera.processInput(Camera_Movement::NONE, deltaTime);
	}
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn) {
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	if (cameraOn) {
		camera.processMouseMovement(xoffset, yoffset);
	}
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		cameraOn = !cameraOn;
		if (cameraOn) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
			firstMouse = true;
		}
		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}