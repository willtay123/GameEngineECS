#pragma once
#include "ResourceLoader.h"
#include <Tools/Logger.h>
#include <sstream>

#include "assimp/Importer.hpp"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "DataStructs/Vertex.h"


ResourceLoader::~ResourceLoader() {

}

std::shared_ptr<Texture> ResourceLoader::LoadTexture(const string& filepath) {
	Logger::LogInfo("Loading a texture");

	std::shared_ptr<Texture> texture;

	GLuint textureID;
	int width, height, mipLevel = 0;

	// Use SOIL to load an image file directly as a new OpenGL texture
	textureID = SOIL_load_OGL_texture(
		filepath.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_INVERT_Y | SOIL_FLAG_MULTIPLY_ALPHA
	);

	// Check for errors loading in texture
	if (textureID == 0) {
		// Loading failed
		string text = string("Failed to load texture - " + filepath);
		Logger::LogError(text);
		text = string("SOIL loading error: ").append(SOIL_last_result());
		Logger::LogError(text);
		return NULL;
	}
	else {
		// Get useful texture parameters
		mipLevel = 0;
		glBindTexture(GL_TEXTURE_2D, textureID);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_WIDTH, &width);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_HEIGHT, &height);

		// Unbind texture
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	// Create a texture object
	texture = std::shared_ptr<Texture>(new Texture(textureID, width, height, mipLevel));

	return texture;

	std::stringstream ss = std::stringstream();
	ss << "Texture ID of loaded texure: ";
	ss << textureID;
	string text = ss.str();
	Logger::LogInfo(text);
}

std::shared_ptr<Geometry> ResourceLoader::LoadGeometry(const string& filepath) {
	return LoadOBJ(filepath);
}

std::shared_ptr<IResource> ResourceLoader::LoadResource(const string& filepath) {
	return nullptr;
}

std::shared_ptr<Geometry> ResourceLoader::LoadOBJ(const string& filepath) {
	Logger::LogInfo("Loading Geometry from OBJ");

	Assimp::Importer importer;
	const  aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate);
	aiMesh* mesh = scene->mMeshes[0];

	std::vector<TriangleIndices> triangles;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	for (UINT i = 0; i < mesh->mNumVertices; i++) {
		Vertex vertex;
		temp_vertices.push_back(vec3(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		));

		temp_normals.push_back(vec3(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z
		));

		temp_uvs.push_back(vec2(
			mesh->mTextureCoords[0][i].x,
			mesh->mTextureCoords[0][i].y
		));
	}

	vector<unsigned int> temp_indices;
	for (UINT i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];

		temp_indices.push_back(face.mIndices[0]);
		temp_indices.push_back(face.mIndices[1]);
		temp_indices.push_back(face.mIndices[2]);
	}

	return std::make_shared<Geometry>();
}