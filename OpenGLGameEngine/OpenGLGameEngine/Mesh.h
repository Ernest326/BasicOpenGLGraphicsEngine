#pragma once

#include "Vector2.h"
#include "Vector3.h"

#include "Shader.h"

#include <vector>

struct Vertex {

	Vector3 Position;
	Vector3 Normal;
	Vector2 TexCoords;

	Vector3 Tangent;
	Vector3 Bitangent;

};

struct Texture {

	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
public:

	std::vector<Vertex> Vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> Textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(Shader shader);

private:

	unsigned int VAO, VBO, EBO;

	void setupMesh();

};

