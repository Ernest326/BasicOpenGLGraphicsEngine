#pragma once
#include <stb_image.h>

#include "Shader.h"
#include "Mesh.h"

#include <assimp\Importer.hpp>
#include <assimp\scene.h>
#include <assimp\postprocess.h>

class Model
{
public:

	Model(char* path);

	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;

	bool gammaCorrection;

	void Draw(Shader shader);

private:

	void LoadModel(std::string const& path);
	void ProcessNode(aiNode *node, const aiScene *scene);
	Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);

	std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);

	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma);

};

