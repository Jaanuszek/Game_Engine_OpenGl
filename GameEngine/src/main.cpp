#include <iostream>
#include <map>
#include "wtypes.h"
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
#include "objects/Cone.h"
#include "objects/Pyramid.h"
#include "objects/Sphere.h"
#include "objects/Torus.h"
#include "IO/InputHandler.h"
#include "MeshFactory.h"

enum class RenderObject {
	Cube,
	Cuboid,
	Cylinder,
	Cone,
	Pyramid,
	Sphere,
	Torus
};

void BindShaderWithLightning(Shader& shader, const glm::vec3& lightPos, const glm::mat4& mvp, const glm::mat4& model, Camera* camera);
void DrawObjectWithShader(Mesh& mesh, Shader& shader, const glm::mat4& mvp);
void HandleRendering(Mesh& mesh, std::map<std::string, std::shared_ptr<Shader>> shader, bool textureChosen, const glm::vec3& lightPos, const glm::mat4& mvp,
	const glm::mat4& model, Camera* camera);
void GetDesktopResolution(float& horizontal, float& vertical);

float width = 0;
float height = 0;


glm::vec3 translationA(0.0f, 0.0f, 0.0f);
glm::vec3 viewTranslation(0.0f, 0.0f, -3.0f);
glm::vec3 lightCubeTranslation(-1.0f, 1.0f, 0.0f);

float deltaTime = 0.0f;
float lastFrame = 0.0f;

auto camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 3.0f), translationA);
auto renderer = std::make_shared<Renderer>();

int main() {
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	GetDesktopResolution(width, height);
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
	//Renderer renderer;
	inputHandler.setRenderer(renderer);

	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) {
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
	glfwSetWindowUserPointer(window, &inputHandler);
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
		//is these lines below necessary?
		shader1.Bind();
		shader1.SetUniform3f("u_objectColor", 1.0f, 0.2f, 0.8f);
		shader1.SetUniform3f("u_lightColor", 1.0f, 1.0f, 1.0f);
		shader1.SetUniform3f("u_lightPos", lightCubeTranslation);
		shader1.Unbind();
		Shader shaderSphere("../../assets/shaders/Sphere.shader");

		Shader lightCubeShader("../../assets/shaders/LightCube.shader");
		lightCubeShader.Bind();
		lightCubeShader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
		lightCubeShader.Unbind(); //????

		//maybe It will be faster if I create hashmap with shaders, but right now its not necessary
		std::map<std::string, std::shared_ptr<Shader>> shaders = {
			{"LightningShader", std::make_shared<Shader>(shader1)},
			{"SphereShader", std::make_shared<Shader>(shaderSphere)},
			{"LightCubeShader", std::make_shared<Shader>(lightCubeShader)}
		};
		Texture textures[] = {
			Texture("../../assets/textures/monkey.png", "diffuse")
		};

		Texture texturesSphere[] = {
			Texture("../../assets/textures/monkey.png", "diffuse")
		};
		Cube cube;
		float cuboidWidht = 0.75, cuboidHeight = 0.5, cuboidDepth = 0.5;
		Cuboid cuboid(cuboidWidht, cuboidHeight, cuboidDepth);
		Cylinder cylinder;
		Cone cone;
		Pyramid pyramid;
		Sphere sphere;
		float minorRadius = 0.2f, majorRadius = 0.5f;
		int sectors = 48, side = 48;
		int maxAmountSectors = sectors;
		int maxAmountSide = side;
		Torus torus(minorRadius,majorRadius,sectors,side);
		MeshFactory meshFactory;

		// Do something with that
		std::vector <Texture> texVec(textures, textures + sizeof(textures) / sizeof(Texture));
		std::vector <Texture> texVecSph(texturesSphere, texturesSphere + sizeof(texturesSphere) / sizeof(Texture));
		Mesh meshCube = meshFactory.CreateMesh(cube, texVec);
		Mesh meshCuboid = meshFactory.CreateMesh(cuboid, texVec);
		Mesh meshLight = meshFactory.CreateMesh(cube, texVec);
		Mesh meshPyramid = meshFactory.CreateMesh(pyramid, texVec);
		Mesh meshSphere = meshFactory.CreateMesh(sphere, texVecSph);
		Mesh meshCylinder = meshFactory.CreateMesh(cylinder, texVec);
		Mesh meshCone = meshFactory.CreateMesh(cone, texVec);
		Mesh meshTorus = meshFactory.CreateMesh(torus, texVec);
		std::map<RenderObject, std::shared_ptr<Mesh>> meshMap = {
			{RenderObject::Cube, std::make_shared<Mesh>(meshCube)},
			{RenderObject::Cuboid, std::make_shared<Mesh>(meshCuboid)},
			{RenderObject::Cylinder, std::make_shared<Mesh>(meshCylinder)},
			{RenderObject::Cone, std::make_shared<Mesh>(meshCone)},
			{RenderObject::Pyramid, std::make_shared<Mesh>(meshPyramid)},
			{RenderObject::Sphere, std::make_shared<Mesh>(meshSphere)},
			{RenderObject::Torus, std::make_shared<Mesh>(meshTorus)}
		};
		float angle = 0.0f;

		RenderObject renderObject = RenderObject::Cube;

		while (!glfwWindowShouldClose(window)) {
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			renderer->Clear();
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
				bool textureChosen = inputHandler.getTexture();
				// rendering objects using map
				Mesh& selectedMesh = *meshMap.find(renderObject)->second; // add if statement to check if it is in map
				HandleRendering(selectedMesh, shaders, textureChosen, lightCubeTranslation, mvp, model, camera.get());
				if (renderObject == RenderObject::Torus) {
					bool torusUpdated = false;
					torusUpdated |= ImGui::SliderFloat("torus minor radius", &minorRadius, 0.0f, 1.0f);
					torusUpdated |= ImGui::SliderFloat("torus major radius", &majorRadius, 0.0f, 1.0f);
					torusUpdated |= ImGui::InputInt("torus sectors", &sectors, 1, maxAmountSectors);
					torusUpdated |= ImGui::InputInt("torus side", &side, 1, maxAmountSide);
					if (sectors < 3) sectors = 3;
					if (sectors > maxAmountSectors)
						sectors = maxAmountSectors;
					if (side < 3) side = 3;
					if (side > maxAmountSide)
						side = maxAmountSide;
					if (torusUpdated) {
						torus.Update(minorRadius, majorRadius, (unsigned int)sectors, (unsigned int)side);
						std::vector <Vertex> verticesTemp = torus.GetVertices();
						std::vector <unsigned int> indicesTemp = torus.GetIndices();

						meshTorus.updateMesh(torus.GetVertices(), torus.GetIndices(), texVec);
					}
				}
				// rendering light cube
				lightCubeShader.Bind();
				lightCubeShader.SetUniformMat4f("u_MVP", mvpLightCube);
				meshLight.Draw(lightCubeShader, *camera);
			}
			{
				ImGui::Begin("Jabol");
				if (ImGui::Button("Camera On/Off")) {
					inputHandler.setCameraOn(!inputHandler.getCameraOn());
				}
				if (ImGui::Button("Render Cube")) {
					renderObject = RenderObject::Cube;
				}
				ImGui::SameLine();
				if (ImGui::Button("Render Cuboid")) {
					renderObject = RenderObject::Cuboid;
				}
				ImGui::SameLine();
				if (ImGui::Button("Render Cylinder")) {
					renderObject = RenderObject::Cylinder;
				}

				if (ImGui::Button("Render Pyramid")) {
					renderObject = RenderObject::Pyramid;
				}
				ImGui::SameLine();
				if (ImGui::Button("Render Sphere")) {
					renderObject = RenderObject::Sphere;
				}
				if (ImGui::Button("Render Cone")) {
					renderObject = RenderObject::Cone;
				}
				ImGui::SameLine();
				if (ImGui::Button("Render Torus")) {
					renderObject = RenderObject::Torus;
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

void BindShaderWithLightning(Shader& shader, const glm::vec3& lightPos, const glm::mat4& mvp, const glm::mat4& model, Camera* camera) {
	shader.Bind();
	shader.SetUniform3f("u_lightPos", lightPos);
	shader.SetUniformMat4f("u_MVP", mvp);
	shader.SetUniform3f("u_viewPos", camera->GetCameraPos());
	shader.SetUniformMat4f("u_model", model);
}
void DrawObjectWithShader(Mesh& mesh, Shader& shader, const glm::mat4& mvp) {
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);
	mesh.Draw(shader, *camera);
}
void HandleRendering(Mesh& mesh, std::map<std::string, std::shared_ptr<Shader>> shader, bool textureChosen, const glm::vec3& lightPos, const glm::mat4& mvp,
	const glm::mat4& model, Camera* camera) {
	if (textureChosen) {
		auto it = shader.find("LightningShader");
		if (it != shader.end()) {
			std::shared_ptr<Shader>& shaderWithLight = it->second;
			BindShaderWithLightning(*shaderWithLight, lightPos, mvp, model, camera);
			mesh.Draw(*shaderWithLight, *camera);
		}
		else {
			std::cerr << "LightningShader not found" << std::endl;
			return;
		}
	}
	else {
		auto it = shader.find("SphereShader");
		if (it != shader.end()) {
			std::shared_ptr<Shader>& shaderWithoutLight = it->second;
			DrawObjectWithShader(mesh, *shaderWithoutLight, mvp);
		}
		else {
			std::cerr << "SphereShader not found" << std::endl;
			return;
		}
	}
}
void GetDesktopResolution(float& horizontal, float& vertical) {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}