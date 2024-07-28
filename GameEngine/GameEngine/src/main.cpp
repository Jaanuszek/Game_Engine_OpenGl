#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>

#include "Mesh.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <iostream>

#include "Renderer.h"

#include "Cube.h"
#include "Pyramid.h"
#include "Sphere.h"

#include "IO/InputHandler.h"

#include "tests/TestClearColor.h"




enum class RenderObject {
	Cube,
	Pyramid,
	Sphere
};

void SetupRenderObjects(RenderObject object, VAO& vao, VBO& vbo, VBL& layout, EBO& ebo);

float width = 960.0f;
float height = 540.0f;

Cube cube;
const float *verticesCube = cube.GetVertices();
const unsigned int* indicesCube = cube.GetIndices();
const Vertex* verticesCu = cube.GetVerticesStruct();
Pyramid pyramid;
const float* verticesPyramid = pyramid.GetVertices();
const unsigned int* indicesPyramid = pyramid.GetIndices();
const VertexPyramid* verticesPyr = pyramid.GetVerticesStruct();

const Vertex* verticesLigthCube = cube.GetVerticesStruct();
const unsigned int verticesLigthCubeSize = cube.GetVerticesSize();
const unsigned int* indicesLightCube = cube.GetIndices();
const unsigned int indicesLightCubeSize = cube.GetIndicesSize();

glm::vec3 translationA(0.0f, 0.0f, 0.0f);
glm::vec3 viewTranslation(0.0f, 0.0f, -3.0f);
glm::vec3 lightCubeTranslation(-1.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), translationA);

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
	gladLoadGL();
	glfwSwapInterval(1);
	InputHandler inputHandler(window);
	inputHandler.setCamera(camera);

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos){
		InputHandler* handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
			if (handler) {
				handler->mouse_callback(xpos, ypos);
			}
		});

	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		InputHandler* handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
			if (handler) {
				handler->key_callback(key, action);
			}
		});
	glfwSetWindowUserPointer(window,&inputHandler);

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
		VBO vbo1(verticesCu, cube.GetVerticesSize() * sizeof(VertexCube));
		VBL layout1;
		layout1.Push(GL_FLOAT, 3);
		layout1.Push(GL_FLOAT, 2);
		layout1.Push(GL_FLOAT, 3);
		layout1.Push(GL_FLOAT, 3); //Lightning purposes 
		vao1.AddBuffer(vbo1, layout1);
		EBO ebo1(indicesCube, cube.GetIndicesSize());

		Shader shader1("res/shaders/LightningShader.shader");
		shader1.Bind();
		shader1.SetUniform3f("u_objectColor", 1.0f, 0.2f, 0.8f);
		shader1.SetUniform3f("u_lightColor", 1.0f, 1.0f, 1.0f);
		shader1.SetUniform3f("u_lightPos", lightCubeTranslation);

		Texture texture1("res/textures/monkey.png", "");
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
		layoutSphere.Push(GL_FLOAT, 3); //lightning purposes	
		vaoSphere.AddBuffer(vboSphere, layoutSphere);
		EBO eboSphere(indicesSphere.data(), indicesSphere.size());

		Shader shaderSphere("res/shaders/Sphere.shader");
		shaderSphere.Bind();

		Texture textureSphere("res/textures/monkey.png", "");
		textureSphere.Bind();
		shaderSphere.SetUniform1i("u_Texture", 0);

		vaoSphere.Unbind();
		vboSphere.Unbind();
		eboSphere.Unbind();
		shaderSphere.Unbind();

		Shader lightCubeShader("res/shaders/LightCube.shader");
		lightCubeShader.Bind();
		lightCubeShader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

		Texture textures[] = {
			Texture("res/textures/monkey.png", "diffuse")
		};

		std::vector <Vertex> LightCubeverts(verticesLigthCube, verticesLigthCube +verticesLigthCubeSize/(sizeof(Vertex)/sizeof(float)));
		std::vector <unsigned int> LightCubeinds(indicesLightCube, indicesLightCube + indicesLightCubeSize);
		std::vector <Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
		Mesh mesh(LightCubeverts, LightCubeinds, tex);

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
			inputHandler.setDeltaTime(deltaTime);
			if (inputHandler.getCameraOn()) {
				inputHandler.cameraMovement_callback();
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
				if (!inputHandler.getCameraOn()) {
					view = glm::translate(glm::mat4(1.0f), viewTranslation);
					mvp = proj * view * model;
					mvpLightCube = proj * viewLightCube * modelLightCube;
				}
				else {
					mvp = camera->CalculateMVP(proj, model);
					mvpLightCube = camera->CalculateMVP(proj, modelLightCube);
				}
				if (renderObject != RenderObject::Sphere) {
					shader1.Bind();
					shader1.SetUniform3f("u_lightPos", lightCubeTranslation);
					shader1.SetUniformMat4f("u_MVP", mvp);
					shader1.SetUniformMat4f("u_view", view);
					shader1.SetUniform3f("u_viewPos", camera->GetCameraPos());
					shader1.SetUniformMat4f("u_model", model);//lightnig purposes
					renderer.Draw(vao1, ebo1, shader1);
				}
				else {
					shaderSphere.Bind();
					shaderSphere.SetUniformMat4f("u_MVP", mvp);
					renderer.Draw(vaoSphere, eboSphere, shaderSphere);
				}
				lightCubeShader.Bind();
				lightCubeShader.SetUniformMat4f("u_MVP", mvpLightCube);
				//renderer.Draw(lightCubeVAO, lightCubeEBO, lightCubeShader);
								
				mesh.Draw(lightCubeShader, *camera);
			}
			{
			ImGui::Begin("Jabol");
			if (ImGui::Button("Camera On/Off")) {
				inputHandler.setCameraOn(!inputHandler.getCameraOn());
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
		vbo.Update(verticesCu, cube.GetVerticesSize() * sizeof(VertexCube));
		ebo.Update(indicesCube, cube.GetIndicesSize());
	}
	else if (object == RenderObject::Pyramid) {
		vbo.Update(verticesPyr, pyramid.GetVerticesSize() * sizeof(VertexPyramid));
		ebo.Update(indicesPyramid, pyramid.GetIndicesSize());
	}
}
