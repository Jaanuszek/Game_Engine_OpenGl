#ifndef MODEL_H
#define MODEL_H
#include "Mesh.h"
#include <iostream>
#include <stb_image.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


class Model {
private:
	std::vector<Mesh> m_meshes;
	std::string directory;
	std::vector<TextureStruct> textures_loaded;

	void loadModel(std::string path);
	void processNode(aiNode* node, const aiScene* scene);
	Mesh processMesh(aiMesh* mesh, const aiScene* scene);
	std::vector<TextureStruct> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
public:
	Model(char* path);
	~Model();
	void Draw(Shader& shader, Camera& camera);
};

#endif
