#include <iostream>
#include <map>
#include <filesystem>
#include "wtypes.h" // for GetDesktopWindow
#include "glad/glad.h"
#include <GLFW/glfw3.h>
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
#include "factories/IObjectFactory.h"
#include "factories/ObjectFactory.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "GuiHandler.h"
#include "Model.h"
#include "TextureManager.h"
#include "ModelManager.h"

std::vector<std::string> getFilesNamesFromDirectory(const std::string& pathToModels);
void SetShader(std::map<ShaderType, std::shared_ptr<Shader>>& shadersMap, ShaderType shaderType,
	const glm::vec3 lightPos,const glm::mat4& mvp, Camera* camera, const glm::mat4& model);
void HandleRendering(Mesh& mesh, std::map<ShaderType, std::shared_ptr<Shader>> chosedShader, ShaderType shaderType,
	const glm::vec3& lightPos, const glm::mat4& mvp, const glm::mat4& model, Camera* camera, std::vector<TextureStruct> updateDTexture);
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

// Files names
std::vector<std::string> stringShaderFiles = getFilesNamesFromDirectory("../../assets/shaders");
std::vector<std::string> stringModelsFiles = getFilesNamesFromDirectory("../../assets/models");
std::vector<std::string> stringTexturesFiles = getFilesNamesFromDirectory("../../assets/textures");

// ImGui Variables
static int currentShaderImGui = 1;
static int currentObjectImGui = 0;
static int currentTextureImGui = 0;
static int currentCustomModelImGui = 0;

int main() {
	if (!glfwInit())
		return -1;
	Assimp::Importer importer;
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
	//enable vsync
	glfwSwapInterval(1); 

	std::cout << "OpenGL version, and graphics card driver version: ";
	std::cout << glGetString(GL_VERSION) << std::endl;
	std::cout << "\033[31m" << "MAKE SURE YOU RUN THIS PROGRAM WITH DEDICATED GRAPHICS CARD!!" << "\033[0m" << std::endl;
	std::cout << "Graphics card: ";
	std::cout << glGetString(GL_RENDERER) << std::endl;

	InputHandler inputHandler(window);
	inputHandler.setCamera(camera);
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

		Shader basicShader("../../assets/shaders/Basic.shader");

		Shader lightningShader("../../assets/shaders/LightningShader.shader");
		//is these lines below necessary?
		lightningShader.Bind();
		lightningShader.SetUniform3f("u_objectColor", 1.0f, 0.2f, 0.8f);
		lightningShader.SetUniform3f("u_lightColor", 1.0f, 1.0f, 1.0f);
		lightningShader.SetUniform3f("u_lightPos", lightCubeTranslation);
		lightningShader.Unbind();
		Shader shaderSphere("../../assets/shaders/Sphere.shader");

		Shader lightCubeShader("../../assets/shaders/LightCube.shader");
		lightCubeShader.Bind();
		lightCubeShader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
		lightCubeShader.Unbind();
		
		Shader customModelShader("../../assets/shaders/CustomModel.shader");
		customModelShader.Bind();
		customModelShader.Unbind();

		std::map<ShaderType, std::shared_ptr<Shader>> shadersMap = {
			{ShaderType::Basic, std::make_shared<Shader>(basicShader)},
			{ShaderType::Lightning, std::make_shared<Shader>(lightningShader)},
			{ShaderType::LightCube, std::make_shared<Shader>(lightCubeShader)},
			{ShaderType::CustomModel, std::make_shared<Shader>(customModelShader)},
			{ShaderType::Sphere, std::make_shared<Shader>(shaderSphere)}
		};
		TextureManager textureManager("../../assets/textures");
		std::vector<TextureStruct> allTexturesStruct = textureManager.GetAllTexturesStruct();
		TextureStruct structSelectedTexture = allTexturesStruct.front();
		std::vector<TextureStruct> vecSelectedTexture = { structSelectedTexture };

		ModelManager modelManager("../../assets/models");
		std::vector<Model> allModelsVector = modelManager.GetAllModelsVector();
		Model selectedModel = allModelsVector.front();

		Cube cube;
		Cuboid cuboid(0.75f, 0.5f, 0.5f);
		Cylinder cylinder;
		Cone cone(0.5f, 1.0f, 48, 48);
		Pyramid pyramid;
		Sphere sphere(0.5f, 48, 48);
		Torus torus(0.2f,0.5f,48,50);

		auto ConeFactory = ObjectFactory::GetFactory(RenderObject::Cone, cone);
		std::shared_ptr<Mesh> meshCone = ConeFactory->CreateMesh(vecSelectedTexture);
		auto CubeFactory = ObjectFactory::GetFactory(RenderObject::Cube, cube);
		std::shared_ptr<Mesh> meshCube = CubeFactory->CreateMesh(vecSelectedTexture);
		std::shared_ptr<Mesh> meshLight = CubeFactory->CreateMesh(vecSelectedTexture);
		auto CuboidFactory = ObjectFactory::GetFactory(RenderObject::Cuboid, cuboid);
		std::shared_ptr<Mesh> meshCuboid = CuboidFactory->CreateMesh(vecSelectedTexture);
		auto CylinderFactory = ObjectFactory::GetFactory(RenderObject::Cylinder, cylinder);
		std::shared_ptr<Mesh> meshCylinder = CylinderFactory->CreateMesh(vecSelectedTexture);
		auto PyramidFactory = ObjectFactory::GetFactory(RenderObject::Pyramid, pyramid);
		std::shared_ptr<Mesh> meshPyramid = PyramidFactory->CreateMesh(vecSelectedTexture);
		auto SphereFactory = ObjectFactory::GetFactory(RenderObject::Sphere, sphere);
		std::shared_ptr<Mesh> meshSphere = SphereFactory->CreateMesh(vecSelectedTexture);
		auto TorusFactory = ObjectFactory::GetFactory(RenderObject::Torus, torus);
		std::shared_ptr<Mesh> meshTorus = TorusFactory->CreateMesh(vecSelectedTexture);

		std::map<RenderObject, std::shared_ptr<Mesh>> meshMap = {
			{RenderObject::Cube, meshCube},
			{RenderObject::Cuboid, meshCuboid},
			{RenderObject::Cylinder, meshCylinder},
			{RenderObject::Cone, meshCone},
			{RenderObject::Pyramid, meshPyramid},
			{RenderObject::Sphere, meshSphere},
			{RenderObject::Torus, meshTorus}
		};
		float angle = 0.0f;

		RenderObject renderObject = RenderObject::Cube;
		ShaderType shaderType = ShaderType::Lightning;
		GuiHandler gui(stringShaderFiles, stringTexturesFiles, stringModelsFiles,
			currentShaderImGui, currentTextureImGui, currentCustomModelImGui,
			shaderType, renderObject, translationA, viewTranslation, lightCubeTranslation, angle);

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
				// Do something with this calculations
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

				// Chosing active texture
				if (currentTextureImGui >= 0 && currentTextureImGui < allTexturesStruct.size()) {
					structSelectedTexture = allTexturesStruct.at(currentTextureImGui);
				}
				vecSelectedTexture.clear();
				vecSelectedTexture.push_back(structSelectedTexture);

				if (currentCustomModelImGui >= 0 && currentCustomModelImGui < allModelsVector.size()) {
					selectedModel = allModelsVector.at(currentCustomModelImGui);
				}

				if (renderObject != RenderObject::Assimp) {
					// rendering objects using map
					Mesh& selectedMesh = *meshMap.find(renderObject)->second; // add if statement to check if it is in map
					HandleRendering(selectedMesh, shadersMap, shaderType, lightCubeTranslation, mvp, model, camera.get(), vecSelectedTexture);
					if (renderObject == RenderObject::Sphere) {
						sphere.UpdateParams();
						meshSphere->updateMesh(sphere.GetVertices(), sphere.GetIndices(), vecSelectedTexture);
					}
					if (renderObject == RenderObject::Cone) {
						cone.UpdateParams();
						meshCone->updateMesh(cone.GetVertices(), cone.GetIndices(), vecSelectedTexture);
					}
					if (renderObject == RenderObject::Torus) {
						torus.UpdateParams();
						meshTorus->updateMesh(torus.GetVertices(), torus.GetIndices(), vecSelectedTexture);
					}
					if (renderObject == RenderObject::Cylinder) {
						cylinder.UpdateParams();
						meshCylinder->updateMesh(cylinder.GetVertices(), cylinder.GetIndices(), vecSelectedTexture);
					}
					if (renderObject == RenderObject::Cuboid) {
						cuboid.UpdateParams();
						meshCuboid->updateMesh(cuboid.GetVertices(), cuboid.GetIndices(), vecSelectedTexture);
					}
				}
				else {
					//render assimp model
					customModelShader.Bind();
					customModelShader.SetUniformMat4f("u_MVP", mvp);
					selectedModel.Draw(customModelShader, *camera);
				}
				// rendering light cube
				lightCubeShader.Bind();
				lightCubeShader.SetUniformMat4f("u_MVP", mvpLightCube);
				meshLight->Draw(lightCubeShader, *camera);
			}
			// Draw whole Gui
			gui.DrawMainGui();
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

std::vector<std::string> getFilesNamesFromDirectory(const std::string& pathToModels) {
	std::vector<std::string> stringFilesNames;
	for (const auto& entry : std::filesystem::directory_iterator(pathToModels)) {
		std::string fileName = entry.path().filename().string();
		fileName = fileName.substr(0, fileName.find_last_of('.'));
		stringFilesNames.push_back(fileName);
	}
	return stringFilesNames;
}

void SetShader(std::map<ShaderType, std::shared_ptr<Shader>>& shadersMap, ShaderType shaderType, 
	const glm::vec3 lightPos,const glm::mat4& mvp, Camera* camera, const glm::mat4& model) {
	auto shader = shadersMap.find(shaderType);
	if (shader != shadersMap.end()) {
		shader->second->Bind();
		shader->second->SetUniform3f("u_lightPos", lightPos);
		shader->second->SetUniformMat4f("u_MVP", mvp);
		shader->second->SetUniform3f("u_viewPos", camera->GetCameraPos());
		shader->second->SetUniformMat4f("u_model", model);
	}
	else {
		std::cout << "Shader not found" << std::endl;
		return;
	}
}
void HandleRendering(Mesh& mesh, std::map<ShaderType, std::shared_ptr<Shader>> chosedShader, ShaderType shaderType,
	const glm::vec3& lightPos, const glm::mat4& mvp,const glm::mat4& model, Camera* camera, std::vector<TextureStruct> updatedTexture) {
	SetShader(chosedShader, shaderType, lightPos, mvp, camera, model);
	mesh.updateTexture(updatedTexture);
	mesh.DrawStruct(*chosedShader.find(shaderType)->second, *camera);
}
void GetDesktopResolution(float& horizontal, float& vertical) {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}