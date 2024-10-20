#include "GuiHandler.h"

template<typename EnumType>
void GuiHandler::drawCombo(const std::vector<std::string>& options, int& selectedOption, EnumType& enumValue, const char* text) {
	if (ImGui::BeginCombo(text, options[selectedOption].c_str())) {
		for (int i = 0; i < options.size(); i++) {
			bool is_selected = (selectedOption == i);
			if (ImGui::Selectable(options[i].c_str(), is_selected)) {
				selectedOption = i;
				enumValue = static_cast<EnumType>(i);
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}

void GuiHandler::drawCombo(const std::vector<std::string>& options, int& selectedOption, const char* text) {
	if (ImGui::BeginCombo(text, options[selectedOption].c_str())) {
		for (int i = 0; i < options.size(); i++) {
			bool is_selected = (selectedOption == i);
			if (ImGui::Selectable(options[i].c_str(), is_selected)) {
				selectedOption = i;
			}
			if (is_selected)
				ImGui::SetItemDefaultFocus();
		}
		ImGui::EndCombo();
	}
}
void GuiHandler::Init(GLFWwindow* window) {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init((char*)glGetString(330));
}
void GuiHandler::StartFrame() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}
void GuiHandler::EndFrame() {
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
GuiHandler::GuiHandler(GuiHandlerParams params) : m_shaderFiles(params.shaderFiles), m_textureFiles(params.textureFiles), m_modelFiles(params.modelFiles),
m_selectedShader(params.selectedShader), m_selectedTexture(params.selectedTexture), m_selectedModel(params.selectedModel), m_shaderType(params.shaderType),
m_renderObject(params.renderObject), m_translation(params.translation), m_viewTranslation(params.viewTranslation),
m_lightCubeTranslation(params.lightCubeTranslation), m_angle(params.angle), m_clearColor(params.clearColor)
{
}

GuiHandler& GuiHandler::operator=(const GuiHandler& other) {
	if (this == &other) return *this;
	m_shaderFiles = other.m_shaderFiles;
	m_textureFiles = other.m_textureFiles;
	m_modelFiles = other.m_modelFiles;
	m_selectedShader = other.m_selectedShader;
	m_selectedTexture = other.m_selectedTexture;
	m_selectedModel = other.m_selectedModel;
	m_shaderType = other.m_shaderType;
	m_renderObject = other.m_renderObject;
	m_translation = other.m_translation;
	m_viewTranslation = other.m_viewTranslation;
	m_lightCubeTranslation = other.m_lightCubeTranslation;
	m_angle = other.m_angle;
	return *this;
}

GuiHandler::~GuiHandler()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GuiHandler::DrawMainGui(){
	ImGui::Begin("Game_Engine");
	drawCombo(m_shaderFiles, m_selectedShader, m_shaderType, "Select a shader");
	if (m_selectedShader == 0) {
		ImGui::Begin("Choose a texture");
		drawCombo(m_textureFiles, m_selectedTexture, "Select a texture");
		ImGui::End();
	}
	if (ImGui::Button("Render Cube")) {
		m_renderObject = RenderObject::Cube;
	}
	ImGui::SameLine();
	if (ImGui::Button("Render Cuboid")) {
		m_renderObject = RenderObject::Cuboid;
	}
	ImGui::SameLine();
	if (ImGui::Button("Render Cylinder")) {
		m_renderObject = RenderObject::Cylinder;
	}
	if (ImGui::Button("Render Pyramid")) {
		m_renderObject = RenderObject::Pyramid;
	}
	ImGui::SameLine();
	if (ImGui::Button("Render Sphere")) {
		m_renderObject = RenderObject::Sphere;
	}
	if (ImGui::Button("Render Cone")) {
		m_renderObject = RenderObject::Cone;
	}
	ImGui::SameLine();
	if (ImGui::Button("Render Torus")) {
		m_renderObject = RenderObject::Torus;
	}
	if (ImGui::Button("Render custom model")) {
		m_renderObject = RenderObject::Assimp;
	}
	if (m_renderObject == RenderObject::Assimp) {
		ImGui::Begin("Choose a model");
		drawCombo(m_modelFiles, m_selectedModel, "Select a model");
		ImGui::End();
	}
	ImGui::SliderFloat3("Translation A", &m_translation.x, -1.0f, 1.0f);
	ImGui::SliderFloat("View Translation A x", &m_viewTranslation.x, -1.0f, 1.0f);
	ImGui::SliderFloat("View Translation A y", &m_viewTranslation.y, -1.0f, 1.0f);
	ImGui::SliderFloat("View Translation A z", &m_viewTranslation.z, -10.0f, 10.0f);
	ImGui::SliderFloat("Angle", &m_angle, 0.0f, 360.0f);
	ImGui::SliderFloat3("Light Cube Translation x", &m_lightCubeTranslation.x, -1.0f, 1.0f);
	ImGui::SliderFloat4("Background Color", &m_clearColor.x, 0.0f, 1.0f);
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}