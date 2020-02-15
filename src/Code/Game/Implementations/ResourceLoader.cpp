#pragma once
#include "ResourceLoader.h"
#include <Tools/Logger.h>
#include <sstream>


Texture* ResourceLoader::LoadTexture(string filepath) {
	Logger::LogInfo("Loading a texture");

	Texture* texture;

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
	texture = new Texture(textureID, width, height, mipLevel);

	return texture;

	std::stringstream ss = std::stringstream();
	ss << "Texture ID of loaded texure: ";
	ss << textureID;
	string text = ss.str();
	Logger::LogInfo(text);
}

Geometry* ResourceLoader::LoadGeometry(string filepath) {
	return LoadOBJ(filepath);
}

IResource* ResourceLoader::LoadResource(string filepath) {
	return NULL;
}

Geometry* ResourceLoader::LoadOBJ(string filepath) {
	Geometry* model;

	Logger::LogInfo("Loading Geometry from OBJ");

	ifstream inFile(filepath);
	if (!inFile) {
		string text = string("unable to load model - " + filepath);
		Logger::LogError(text);
		throw std::exception("Unable to load model, file missing?");
		return NULL;
	}

	std::vector<TriangleIndices> triangles;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	string line;
	string firstWord;

	while (std::getline(inFile, line)) {
		// Turn line into easily processed stream
		std::stringstream linestream(line);

		// Check that the line isn't empty
		if (linestream.rdbuf()->in_avail() > 0) {
			// Get the starting word of the line to decide action
			linestream >> firstWord;

			if (firstWord == "v") {
				// Vertex line
				float x, y, z;
				linestream >> x >> y >> z;

				temp_vertices.push_back(glm::vec3(x, y, z));
			}
			else if (firstWord == "vt") {
				// Texture line
				float x, y;
				linestream >> x >> y;

				temp_uvs.push_back(glm::vec2(x, y));
			}
			else if (firstWord == "vn") {
				// Normal line
				float x, y, z;
				linestream >> x >> y >> z;

				temp_normals.push_back(glm::vec3(x, y, z));
			}
			else if (firstWord == "f") {
				// Face line
				string group;
				TriangleIndices triangle;

				// Process string "v/vt/vn" into data
				for (int i = 0; i < 3; i += 1) {
					linestream >> group;

					std::size_t found = group.find("/");

					// V
					string number = group.substr(0, found);
					int numberAsInt = std::atoi(number.c_str());
					group = group.erase(0, found + 1);
					triangle.vertices[i] = numberAsInt - 1;

					// T
					number = group.substr(0, found);
					numberAsInt = std::atoi(number.c_str());
					group = group.erase(0, found + 1);
					triangle.uvs[i] = numberAsInt - 1;

					// N
					number = group.substr(0, group.size());
					numberAsInt = std::atoi(number.c_str());
					triangle.normals[i] = numberAsInt - 1;
				}

				triangles.push_back(triangle);
			}
			else {
				//ignore
			}
		}
	}

	vector<unsigned short> indices;
	vector<vec2> uvs;
	vector<vec3> vertices, normals;

	//model = new Geometry(vertices, uvs, normals, indices);
	model = new Geometry(temp_vertices, temp_uvs, temp_normals, triangles);

	return model;
}