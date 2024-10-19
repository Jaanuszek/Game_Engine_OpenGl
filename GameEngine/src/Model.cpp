#include "Model.h"

void Model::loadModel(std::string path) {
	Assimp::Importer importer;
	const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_JoinIdenticalVertices);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
		std::cout << "[Model::loadModel] ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
		return;
	}
	m_directory = path.substr(0, path.find_last_of('/'));

	processNode(scene->mRootNode, scene);
}

void Model::processNode(aiNode* node, const aiScene* scene) {
	for (unsigned int i = 0; i < node->mNumMeshes; i++) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		m_meshes.push_back(processMesh(mesh, scene));
	}
	for (unsigned int i = 0; i < node->mNumChildren; i++) {
		processNode(node->mChildren[i], scene);
	}
}

Mesh Model::processMesh(aiMesh* mesh, const aiScene* scene) {
	std::vector<Vertex> vertices;
	vertices.reserve(mesh->mNumVertices);
	std::vector<unsigned int> indices;
	indices.reserve(mesh->mNumFaces * 3);
	std::vector<TextureStruct> textures;
	textures.reserve(mesh->mMaterialIndex);

	for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		glm::vec3 vector; //using temporary vec3 because assimp maintains its own data typed
		vector.x = mesh->mVertices[i].x;
		vector.y = mesh->mVertices[i].y;
		vector.z = mesh->mVertices[i].z;
		vertex.Position = vector;
		if (mesh->mTextureCoords[0]) { //cheking if mesh contain texture coordinates
			glm::vec2 vec;
			vec.x = mesh->mTextureCoords[0][i].x;
			vec.y = mesh->mTextureCoords[0][i].y;
			vertex.TexCoords = vec;
		}
		else {
			vertex.TexCoords = glm::vec2(0.0f, 0.0f);
		}
		vector.x = mesh->mNormals[i].x;
		vector.y = mesh->mNormals[i].y;
		vector.z = mesh->mNormals[i].z;
		vertex.Normal = vector;
		vertices.push_back(vertex);
	}
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		std::vector<TextureStruct> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
		textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
		std::vector<TextureStruct> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
		textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
	}
	return Mesh(vertices, indices, textures);
}
std::vector<TextureStruct> Model::loadMaterialTextures(aiMaterial* mat, aiTextureType types, std::string typeName) {
	std::vector<TextureStruct> textures;
	for (unsigned int i = 0; i < mat->GetTextureCount(types); i++) {
		aiString str;
		mat->GetTexture(types, i, &str);
		bool skip = false;
		for (unsigned int j = 0; j < m_textures_loaded.size(); j++) {
			if (std::strcmp(m_textures_loaded[j].path.data(), str.C_Str()) == 0) {
				textures.push_back(m_textures_loaded[j]);
				skip = true;
				break;
			}
		}
		if (!skip) {
			TextureStruct textureStruct;
			textureStruct.id = Texture::TextureFromFile(str.C_Str(), m_directory);
			textureStruct.type = typeName;
			textureStruct.path = str.C_Str();
			textures.push_back(textureStruct);
			m_textures_loaded.push_back(textureStruct);
		}
	}
	return textures;
}
Model::Model(const char* path)
{
	loadModel(path);
}

Model::~Model()
{
}

void Model::DrawModel(Shader& shader, Camera& camera)
{
	for (unsigned int i = 0; i < m_meshes.size(); i++)
	{
		m_meshes[i].Draw(shader, camera);
	}
}