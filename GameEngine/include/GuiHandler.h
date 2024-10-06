#ifndef GUI_HANDLER_H
#define GUI_HANDLER_H

#include <string>
#include <vector>

#include "VBO.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "glm/glm.hpp"

struct GuiHandlerParams {
	std::vector<std::string>& shaderFiles;
	std::vector<std::string>& textureFiles;
	std::vector<std::string>& modelFiles;
	int& selectedShader;
	int& selectedTexture;
	int& selectedModel;
	ShaderType& shaderType;
	RenderObject& renderObject;
	glm::vec3& translation;
	glm::vec3& viewTranslation;
	glm::vec3& lightCubeTranslation;
	float& angle;
	bool& isObjectBeingUpdated;
};


class GuiHandler {
private:
	std::vector<std::string>& m_shaderFiles;
	std::vector<std::string>& m_textureFiles;
	std::vector<std::string>& m_modelFiles;
	int& m_selectedShader;
	int& m_selectedTexture;
	int& m_selectedModel;
	ShaderType& m_shaderType;
	RenderObject& m_renderObject;
	glm::vec3& m_translation;
	glm::vec3& m_viewTranslation;
	glm::vec3& m_lightCubeTranslation;
	float& m_angle;
	// drawing option list
	template<typename EnumType>
	void drawCombo(const std::vector<std::string>& options, int& selectedOption, EnumType& enumValue, const char* text);
	void drawCombo(const std::vector<std::string>& options, int& selectedOption, const char* text);
public:
	GuiHandler(GuiHandlerParams params);
	~GuiHandler();
	void DrawMainGui();
};

#endif