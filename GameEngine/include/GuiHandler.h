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
	glm::vec3& scaleVector;
    bool& isObjectBeingUpdated;
    glm::vec4& clearColor;

    GuiHandlerParams(
        std::vector<std::string>& shaderFiles,
        std::vector<std::string>& textureFiles,
        std::vector<std::string>& modelFiles,
        int& selectedShader,
        int& selectedTexture,
        int& selectedModel,
        ShaderType& shaderType,
        RenderObject& renderObject,
        glm::vec3& translation,
        glm::vec3& viewTranslation,
        glm::vec3& lightCubeTranslation,
        float& angle,
        glm::vec3& scaleVector,
        bool& isObjectBeingUpdated,
        glm::vec4& clearColor
    ) : shaderFiles(shaderFiles),
        textureFiles(textureFiles),
        modelFiles(modelFiles),
        selectedShader(selectedShader),
        selectedTexture(selectedTexture),
        selectedModel(selectedModel),
        shaderType(shaderType),
        renderObject(renderObject),
        translation(translation),
        viewTranslation(viewTranslation),
        lightCubeTranslation(lightCubeTranslation),
        angle(angle),
		scaleVector(scaleVector),
        isObjectBeingUpdated(isObjectBeingUpdated),
		clearColor(clearColor)
        {}
	GuiHandlerParams(const GuiHandlerParams& other) : shaderFiles(other.shaderFiles),
		textureFiles(other.textureFiles),
		modelFiles(other.modelFiles),
		selectedShader(other.selectedShader),
		selectedTexture(other.selectedTexture),
		selectedModel(other.selectedModel),
		shaderType(other.shaderType),
		renderObject(other.renderObject),
		translation(other.translation),
		viewTranslation(other.viewTranslation),
		lightCubeTranslation(other.lightCubeTranslation),
		angle(other.angle),
		scaleVector(other.scaleVector),
		isObjectBeingUpdated(other.isObjectBeingUpdated),
		clearColor(other.clearColor)
        {}
	GuiHandlerParams& operator=(const GuiHandlerParams& other) {
        if (this != &other) {
            shaderFiles = other.shaderFiles;
            textureFiles = other.textureFiles;
            modelFiles = other.modelFiles;
            selectedShader = other.selectedShader;
            selectedTexture = other.selectedTexture;
            selectedModel = other.selectedModel;
            shaderType = other.shaderType;
            renderObject = other.renderObject;
            translation = other.translation;
            viewTranslation = other.viewTranslation;
            lightCubeTranslation = other.lightCubeTranslation;
            angle = other.angle;
			scaleVector = other.scaleVector;
            isObjectBeingUpdated = other.isObjectBeingUpdated;
			clearColor = other.clearColor;
            return *this;
        }
	}
    GuiHandlerParams& operator=(const GuiHandlerParams&& other) noexcept{
        if (this != &other) {
            shaderFiles = other.shaderFiles;
            textureFiles = other.textureFiles;
            modelFiles = other.modelFiles;
            selectedShader = other.selectedShader;
            selectedTexture = other.selectedTexture;
            selectedModel = other.selectedModel;
            shaderType = other.shaderType;
            renderObject = other.renderObject;
            translation = other.translation;
            viewTranslation = other.viewTranslation;
            lightCubeTranslation = other.lightCubeTranslation;
            angle = other.angle;
			scaleVector = other.scaleVector;
            isObjectBeingUpdated = other.isObjectBeingUpdated;
			clearColor = other.clearColor;
            return *this;
        }
    }
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
	glm::vec3& m_scaleVector;
    glm::vec4& m_clearColor;
	// drawing option list
	template<typename EnumType>
	void drawCombo(const std::vector<std::string>& options, int& selectedOption, EnumType& enumValue, const char* text);
	void drawCombo(const std::vector<std::string>& options, int& selectedOption, const char* text);
public:
	GuiHandler(GuiHandlerParams params);
	GuiHandler& operator=(const GuiHandler& other);
	~GuiHandler();
	static void Init(GLFWwindow* window);
	static void StartFrame();
	static void EndFrame();
	void DrawMainGui();
};

#endif