#include "RenderingManager.h"

void RenderingManager::HandleRendering(Mesh& mesh, std::map<ShaderType, std::shared_ptr<Shader>> chosedShader, const ShadersParams& shaderParams,
	const std::vector<TextureStruct>& updatedTexture) {
	Shader::SetShader(chosedShader, shaderParams);
	mesh.updateTexture(updatedTexture);
	mesh.Draw(*chosedShader.find(shaderParams.shaderType)->second, *shaderParams.camera);
}
void RenderingManager::BindTextureAndDrawModel(Shader& shader, const glm::mat4& mvp, Model& model, std::shared_ptr<Camera> camera) {
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);
	model.DrawModel(shader, *camera);
}
void RenderingManager::BindTextureAndDrawMesh(Shader& shader, const glm::mat4& mvp, Mesh& mesh, std::shared_ptr<Camera> camera) {
	shader.Bind();
	shader.SetUniformMat4f("u_MVP", mvp);
	mesh.Draw(shader, *camera);
}