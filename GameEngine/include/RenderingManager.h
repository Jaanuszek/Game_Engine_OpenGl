#ifndef RENDERING_MANAGER_H
#define RENDERING_MANAGER_H

#include <map>
#include "Mesh.h"
#include "Shader.h"
#include "VBO.h"
#include "factories/ObjectFactory.h"
#include "Model.h"

class RenderingManager {
private:
	std::map<ShaderType, std::shared_ptr<Shader>> m_shadersMap;
	std::map<RenderObject, std::pair<std::shared_ptr<Mesh>, std::unique_ptr<IObjectFactory>>> m_meshMap;
public:
	static void HandleRendering(Mesh& mesh, std::map<ShaderType, std::shared_ptr<Shader>> chosedShader, const ShadersParams& shaderParams,
		const std::vector<TextureStruct>& updatedTexture);
	static void RenderObjectFromMap(std::map<RenderObject, std::pair<std::shared_ptr<Mesh>, std::unique_ptr<IObjectFactory>>>& meshMap,
		std::map<ShaderType, std::shared_ptr<Shader>> chosedShader, const ShadersParams& shaderParams);
	static void BindTextureAndDrawModel(Shader& shader, const glm::mat4& mvp, Model& model, std::shared_ptr<Camera> camera);
	static void BindTextureAndDrawMesh(Shader& shader, const glm::mat4& mvp, Mesh& mesh, std::shared_ptr<Camera> camera);
};

#endif // !RENDERING_MANAGER_H
