#ifndef MODEL_H
#define MODEL_H
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model {
private:
	std::vector<Mesh> m_meshes;
	std::string m_directory;
	std::vector<TextureStruct> m_textures_loaded;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<TextureStruct> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
public:
	Model(const char* path);
	~Model();
	void DrawModel(Shader& shader, Camera& camera);
};

#endif
