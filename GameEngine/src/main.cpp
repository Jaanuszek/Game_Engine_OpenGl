#include <iostream>
#include <map>
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
#include "GuiHandler.h"
#include "Model.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "IO/FileHandler.h"
#include "Calculations.h"

void GetDesktopResolution(float& horizontal, float& vertical);
void SetActiveTexture(static int currentTextureImGui, const std::vector<TextureStruct>& allTextures,
	std::vector<TextureStruct>& vecSelectedTexture, TextureStruct& structSelectedTexture);
void SetActiveModel(static int currentCustomModelImGui, const std::vector<Model>& allModelsVector, Model& selectedModel);
void UpdateObjectParams(const RenderObject& renderObject, IObjectFactory& objectFactory,
	const std::map<RenderObject, std::shared_ptr<Mesh>>& meshMap, const std::vector<TextureStruct>& selectedTexture);
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
std::vector<std::string> stringShaderFiles = FileHandler::getFilesNamesFromDirectory("../../assets/shaders");
std::vector<std::string> stringModelsFiles = FileHandler::getFilesNamesFromDirectory("../../assets/models");
std::vector<std::string> stringTexturesFiles = FileHandler::getFilesNamesFromDirectory("../../assets/textures");

// ImGui Variables
static int currentShaderImGui = 1;
static int currentObjectImGui = 0;
static int currentTextureImGui = 0;
static int currentCustomModelImGui = 0;
bool isObjectUpdated = false;

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
		lightningShader.Bind();
		lightningShader.SetUniform3f("u_objectColor", 0.5f, 0.5f, 0.1f);
		lightningShader.SetUniform3f("u_lightColor", 1.0f, 1.0f, 1.0f);
		lightningShader.SetUniform3f("u_lightPos", lightCubeTranslation);
		lightningShader.Unbind();
		Shader lightCubeShader("../../assets/shaders/LightCube.shader");
		lightCubeShader.Bind();
		lightCubeShader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
		lightCubeShader.Unbind();
		Shader customModelShader("../../assets/shaders/CustomModel.shader");

		std::map<ShaderType, std::shared_ptr<Shader>> shadersMap = {
			{ShaderType::Basic, std::make_shared<Shader>(basicShader)},
			{ShaderType::Lightning, std::make_shared<Shader>(lightningShader)},
			{ShaderType::LightCube, std::make_shared<Shader>(lightCubeShader)},
			{ShaderType::CustomModel, std::make_shared<Shader>(customModelShader)},
		};
		std::map<std::string, std::shared_ptr<Shader>> shadersMapStr;
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

        GuiHandlerParams guiParams{
            stringShaderFiles,
            stringTexturesFiles,
            stringModelsFiles,
            currentShaderImGui,
            currentTextureImGui,
            currentCustomModelImGui,
            shaderType,
            renderObject,
            translationA,
            viewTranslation,
            lightCubeTranslation,
            angle,
			isObjectUpdated
        };

        GuiHandler gui(guiParams);

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
				glm::mat4 proj = Calculations::CalculateProjectionMatrix(width, height);
				glm::mat4 view;
				glm::mat4 model = Calculations::CalculateModelMatrix(angle, glm::vec3(0.5f, 1.0f, 0.0f), translationA);
				glm::mat4 mvp;
				glm::mat4 viewLightCube = Calculations::CalculateViewMatrix(glm::vec3(-0.0f, 0.0f, -3.0f));
				glm::mat4 modelLightCube = Calculations::CalculateModelMatrix(lightCubeTranslation);
				modelLightCube = glm::scale(modelLightCube, glm::vec3(0.2f));
				glm::mat4 mvpLightCube;
				if (!inputHandler.getCameraOn()) {
					view = Calculations::CalculateViewMatrix(viewTranslation);
					mvp = Calculations::CalculateMVPMatrix(proj, view, model);
					mvpLightCube = Calculations::CalculateMVPMatrix(proj, viewLightCube, modelLightCube);
				}
				else {
					mvp = camera->CalculateMVP(proj, model);
					mvpLightCube = camera->CalculateMVP(proj, modelLightCube);
				}
				// Set shader parameters
				ShadersParams shadersParams = { shaderType, mvp, model, lightCubeTranslation, camera.get() };
				SetActiveTexture(currentTextureImGui, allTexturesStruct, vecSelectedTexture, structSelectedTexture);
				SetActiveModel(currentCustomModelImGui, allModelsVector, selectedModel);

				if (renderObject != RenderObject::Assimp) {
					// rendering objects using map
					Mesh& selectedMesh = *meshMap.find(renderObject)->second; // add if statement to check if it is in map
					Mesh::HandleRendering(selectedMesh, shadersMap, shadersParams, vecSelectedTexture);
					UpdateObjectParams(renderObject, *TorusFactory, meshMap, vecSelectedTexture);
				}
				else {
					//render assimp model
					customModelShader.Bind();
					customModelShader.SetUniformMat4f("u_MVP", mvp);
					selectedModel.DrawModel(customModelShader, *camera);
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
void GetDesktopResolution(float& horizontal, float& vertical) {
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);
	horizontal = desktop.right;
	vertical = desktop.bottom;
}

void SetActiveTexture(static int currentTextureImGui, const std::vector<TextureStruct>& allTextures,
	std::vector<TextureStruct>& vecSelectedTexture, TextureStruct& structSelectedTexture) {
	if (currentTextureImGui >= 0 && currentTextureImGui < allTextures.size()) {
		structSelectedTexture = allTextures.at(currentTextureImGui);
	}
	vecSelectedTexture.clear();
	vecSelectedTexture.push_back(structSelectedTexture);
}
void SetActiveModel(static int currentCustomModelImGui, const std::vector<Model>& allModelsVector, Model& selectedModel) {
	if (currentCustomModelImGui >= 0 && currentCustomModelImGui < allModelsVector.size()) {
		selectedModel = allModelsVector.at(currentCustomModelImGui);
	}
}

void UpdateObjectParams(const RenderObject& renderObject, IObjectFactory& objectFactory,
	const std::map<RenderObject, std::shared_ptr<Mesh>>& meshMap, const std::vector<TextureStruct>& selectedTexture){
	Solid& solid = objectFactory.GetSolidObject();
	bool isUpdated = solid.GetIsUpdated();
	//add something like this!!!!
	//if (solid == nulptr) {
	//	throw std::runtime_error("Solid object is null");
	//}
	//if (isUpdated) {
		auto it = meshMap.find(renderObject);
		if (it == meshMap.end()) {
			throw std::runtime_error("RenderObject not found in meshMap");
		}
		solid.UpdateParams();
		it->second->updateMesh(solid.GetVertices(), solid.GetIndices(), selectedTexture);
	//}
}