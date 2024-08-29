#include <iostream>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/constants.hpp>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "Mesh.h"
#include "Renderer.h"
#include "objects/Cuboid.h"
#include "objects/Cube.h"
#include "objects/Cylinder.h"
#include "objects/Pyramid.h"
#include "objects/Sphere.h"
#include "IO/InputHandler.h"
#include "MeshFactory.h"

enum class RenderObject {
	Cube,
	Cuboid,
	Cylinder,
	Pyramid,
	Sphere
};

float width = 960.0f;
float height = 540.0f;

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
		//Shader shader1("res/shaders/LightningShader.shader");
		Shader shader1("../../assets/shaders/LightningShader.shader");
		shader1.Bind();
		shader1.SetUniform3f("u_objectColor", 1.0f, 0.2f, 0.8f);
		shader1.SetUniform3f("u_lightColor", 1.0f, 1.0f, 1.0f);
		shader1.SetUniform3f("u_lightPos", lightCubeTranslation);
		shader1.Unbind();
		Shader shaderSphere("../../assets/shaders/Sphere.shader");

		Shader lightCubeShader("../../assets/shaders/LightCube.shader");
		lightCubeShader.Bind();
		lightCubeShader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

		Texture textures[] = {
			Texture("../../assets/textures/monkey.png", "diffuse")
		};

		Texture texturesSphere[] = {
			Texture("../../assets/textures/monkey.png", "diffuse")
		};
		Cube cube;
		float cuboidWidht = 0.75, cuboidHeight = 0.5, cuboidDepth = 0.5;
		Cuboid cuboid(cuboidWidht,cuboidHeight,cuboidDepth);
		Cylinder cylinder;
		Pyramid pyramid;
		Sphere sphere;
		MeshFactory meshFactory;

		
		std::vector <Texture> texVec(textures, textures + sizeof(textures) / sizeof(Texture));
		std::vector <Texture> texVecSph(texturesSphere, texturesSphere + sizeof(texturesSphere) / sizeof(Texture));
		Mesh meshCube = meshFactory.CreateMesh(cube, texVec);
		Mesh meshCuboid = meshFactory.CreateMesh(cuboid, texVec);
		Mesh meshLight = meshFactory.CreateMesh(cube, texVec);
		Mesh meshPyramid = meshFactory.CreateMesh(pyramid, texVec);
		Mesh meshSphere = meshFactory.CreateMesh(sphere, texVecSph);
		Mesh meshCylinder = meshFactory.CreateMesh(cylinder, texVec);

		Renderer renderer;

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

				switch (renderObject) {
					case RenderObject::Cube:
						shader1.Bind();
						shader1.SetUniform3f("u_lightPos", lightCubeTranslation);
						shader1.SetUniformMat4f("u_MVP", mvp);
						//shader1.SetUniformMat4f("u_view", view);
						shader1.SetUniform3f("u_viewPos", camera->GetCameraPos());
						shader1.SetUniformMat4f("u_model", model);//lightnig purposes
						meshCube.Draw(shader1, *camera);
						break;
					case RenderObject::Cuboid:
						shader1.Bind();
						shader1.SetUniform3f("u_lightPos", lightCubeTranslation);
						shader1.SetUniformMat4f("u_MVP", mvp);
						//shader1.SetUniformMat4f("u_view", view);
						shader1.SetUniform3f("u_viewPos", camera->GetCameraPos());
						shader1.SetUniformMat4f("u_model", model);//lightnig purposes
						meshCuboid.Draw(shader1, *camera);
						break;
					case RenderObject::Pyramid:
						shader1.Bind();
						shader1.SetUniform3f("u_lightPos", lightCubeTranslation);
						shader1.SetUniformMat4f("u_MVP", mvp);
						//shader1.SetUniformMat4f("u_view", view);
						shader1.SetUniform3f("u_viewPos", camera->GetCameraPos());
						shader1.SetUniformMat4f("u_model", model);//lightnig purposes
						meshPyramid.Draw(shader1, *camera);
						break;
					case RenderObject::Sphere:
						shaderSphere.Bind();
						shaderSphere.SetUniformMat4f("u_MVP", mvp);
						meshSphere.Draw(shaderSphere, *camera);
						break;
					case RenderObject::Cylinder:
						shader1.Bind();
						shader1.SetUniform3f("u_lightPos", lightCubeTranslation);
						shader1.SetUniformMat4f("u_MVP", mvp);
						//shader1.SetUniformMat4f("u_view", view);
						shader1.SetUniform3f("u_viewPos", camera->GetCameraPos());
						shader1.SetUniformMat4f("u_model", model);//lightnig purposes
						meshCylinder.Draw(shader1, *camera);
						break;
					default:
						shader1.Bind();
						shader1.SetUniform3f("u_lightPos", lightCubeTranslation);
						shader1.SetUniformMat4f("u_MVP", mvp);
						//shader1.SetUniformMat4f("u_view", view);
						shader1.SetUniform3f("u_viewPos", camera->GetCameraPos());
						shader1.SetUniformMat4f("u_model", model);//lightnig purposes
						meshCube.Draw(shader1, *camera);
						break;
				}
				lightCubeShader.Bind();
				lightCubeShader.SetUniformMat4f("u_MVP", mvpLightCube);						
				meshLight.Draw(lightCubeShader, *camera);
			}
			{
			ImGui::Begin("Jabol");
			if (ImGui::Button("Camera On/Off")) {
				inputHandler.setCameraOn(!inputHandler.getCameraOn());
			}
			if(ImGui::Button("Render Cube")) {
				renderObject = RenderObject::Cube;
			}
			ImGui::SameLine();
			if (ImGui::Button("Render Cuboid")) {
				renderObject = RenderObject::Cuboid;
			}
			//if I wnat to make it work i need to create function that will get reference to the cuboid vertices and change them
			// but there is problemwith that, because cuboid is endered only once, so I need to create new cuboid every time I want to change it
			// GL_DYNAMIC_DRAW
			// leave it right now, but come to this later!!!
			//if (renderObject == RenderObject::Cuboid) {
			//	ImGui::SliderFloat("Cuboid width", &cuboidWidht, 0.0f, 1.0f);
			//	ImGui::SliderFloat("Cuboid height", &cuboidHeight, 0.0f, 1.0f);
			//	ImGui::SliderFloat("Cuboid depth", &cuboidDepth, 0.0f, 1.0f);
			//}
			ImGui::SameLine();
			if (ImGui::Button("Render Cylinder")) {
				renderObject = RenderObject::Cylinder;
			}

			if(ImGui::Button("Render Pyramid")) {
				renderObject = RenderObject::Pyramid;
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
