#ifndef RENDERING_MANAGER_H
#define RENDERING_MANAGER_H

#include <map>
#include "Mesh.h"
#include "Shader.h"
#include "VBO.h"
#include "factories/ObjectFactory.h"
#include "Model.h"
#include "MeshRegistry.h"
#include "MeshUpdater.h"

class RenderingManager {
private:
	std::map<ShaderType, std::shared_ptr<Shader>>& m_shadersMap;
	void HandleRendering(Mesh& mesh, std::map<ShaderType, std::shared_ptr<Shader>> chosedShader, const ShadersParams& shaderParams,
		const std::vector<TextureStruct>& updatedTexture);
public:
	RenderingManager(std::map<ShaderType, std::shared_ptr<Shader>>& shadersMap);
	RenderingManager(const RenderingManager& other);
	RenderingManager& operator=(const RenderingManager& other);
	RenderingManager& operator=(RenderingManager&& other) noexcept;
	void RenderObjectFromMap(MeshRegistry& meshRegistry, RenderObject renderObject, const ShadersParams& shadersParams);
	static void BindTextureAndDrawModel(Shader& shader, const glm::mat4& mvp, Model& model, std::shared_ptr<Camera> camera);
	static void BindTextureAndDrawMesh(Shader& shader, const glm::mat4& mvp, Mesh& mesh, std::shared_ptr<Camera> camera);
};

#endif // !RENDERING_MANAGER_H
