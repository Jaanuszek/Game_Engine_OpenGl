#include <iostream>
#include <map>
#include "glad/glad.h"
#include <GLFW/glfw3.h>
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
#include <assimp/Importer.hpp>
#include "GuiHandler.h"
#include "Model.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "IO/FileHandler.h"
#include "Calculations.h"
#include "SystemUtils.h"
#include "factories/MeshFactory.h"
#include "RenderingManager.h"
#include "MeshRegistry.h"

int width = 0;
int height = 0;
glm::vec4 clearColor(0.1f, 0.1f, 0.1f, 1.0f);

glm::vec3 translationA(0.0f, 0.0f, 0.0f);
glm::vec3 viewTranslation(0.0f, 0.0f, -3.0f);
glm::vec3 lightCubeTranslation(-1.0f, 1.0f, 0.0f);
float angle = 0.0f;
glm::vec3 scaleVector(1.0f, 1.0f, 1.0f);

double deltaTime = 0.0f;
double lastFrame = 0.0f;

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
	SystemUtils::GetDesktopResolution(width, height);
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

	//add excpetion handlers to this callbacks
	glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xpos, double ypos) noexcept{
		InputHandler* handler = static_cast<InputHandler*>(glfwGetWindowUserPointer(window));
		if (handler) {
			handler->mouse_callback(xpos, ypos);
		}
		});
	glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) noexcept{
		(void)scancode;
		(void)mods;
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
		GuiHandler::Init(window);

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
		std::vector<TextureStruct> vecSelectedTexture;
		TextureManager textureManager("../../assets/textures", vecSelectedTexture);

		std::shared_ptr<Model> selectedModel;
		ModelManager modelManager("../../assets/models", selectedModel);

		Cube cube;
		Cuboid cuboid(0.75f, 0.5f, 0.5f);
		Cylinder cylinder;
		Cone cone(0.5f, 1.0f, 48, 48);
		Pyramid pyramid;
		Sphere sphere(0.5f, 48, 48);
		Torus torus(0.2f,0.5f,48,50);
		std::vector<std::pair<RenderObject, Solid*>> objects = {
			{RenderObject::Cube, &cube},
			{RenderObject::Cuboid, &cuboid},
			{RenderObject::Cylinder, &cylinder},
			{RenderObject::Cone, &cone},
			{RenderObject::Pyramid, &pyramid},
			{RenderObject::Sphere, &sphere},
			{RenderObject::Torus, &torus}
		};
		std::shared_ptr<Mesh> meshLight = MeshFactory::CreateMeshFromFactory(RenderObject::Cube, cube, vecSelectedTexture).first;
		MeshRegistry meshRegistry(objects, vecSelectedTexture); // Tworzona mapa
		RenderingManager renderingManager(shadersMap);
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
			scaleVector,
			isObjectUpdated,
			clearColor
        };

        GuiHandler gui(guiParams);

		while (!glfwWindowShouldClose(window)) {
			double currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;
			renderer->Clear();
			inputHandler.setDeltaTime(deltaTime);
			if (inputHandler.getCameraOn()) {
				inputHandler.cameraMovement_callback();
			}
			GuiHandler::StartFrame();
			{
				// Calculations
				glm::mat4 proj = Calculations::CalculateProjectionMatrix(width, height);
				glm::mat4 view;
				glm::mat4 model = Calculations::CalculateModelMatrix(angle, glm::vec3(0.5f, 1.0f, 0.0f), translationA, scaleVector);
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
				// Rendering
				// Set shader parameters
				ShadersParams shadersParams = { shaderType, mvp, model, lightCubeTranslation, camera.get() };
				textureManager.SetActiveTexture(currentTextureImGui);
				modelManager.SetActiveCustomModel(currentCustomModelImGui);
				if (renderObject != RenderObject::Assimp) {
					renderingManager.RenderObjectFromMap(meshRegistry, renderObject, shadersParams);
					// rendering light cube
					RenderingManager::BindTextureAndDrawMesh(lightCubeShader, mvpLightCube, *meshLight, camera);
				}
				else {
					//render assimp model
					RenderingManager::BindTextureAndDrawModel(customModelShader, mvp, *selectedModel, camera);
				}
			}
			gui.DrawMainGui();
			GuiHandler::EndFrame();
			glClearColor(clearColor.x,clearColor.y,clearColor.z,clearColor.w);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}
