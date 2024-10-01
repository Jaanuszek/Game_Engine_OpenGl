#include "GuiHandler.h"

template<typename EnumType>
void GuiHandler::drawCombo(std::vector<std::string>& options, int& selectedOption, EnumType& enumValue, const char* text) {
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

void GuiHandler::drawCombo(std::vector<std::string>& options, int& selectedOption, const char* text) {
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

GuiHandler::GuiHandler(std::vector<std::string>& shaderFiles, std::vector<std::string>& textureFiles, std::vector<std::string>& modelFiles,
	int& selectedShader, int& selectedTexture, int& selectedModel, ShaderType& shaderType, RenderObject& renderObject,
	glm::vec3& translation, glm::vec3& viewTranslation, glm::vec3& lightCubeTranslation, float& angle)
	: m_shaderFiles(shaderFiles), m_textureFiles(textureFiles), m_modelFiles(modelFiles),
	m_selectedShader(selectedShader), m_selectedTexture(selectedTexture), m_selectedModel(selectedModel), m_shaderType(shaderType),
	m_renderObject(renderObject), m_translation(translation), m_viewTranslation(viewTranslation),
	m_lightCubeTranslation(lightCubeTranslation), m_angle(angle) 
{

}

GuiHandler::~GuiHandler()
{
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
	ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	ImGui::End();
}