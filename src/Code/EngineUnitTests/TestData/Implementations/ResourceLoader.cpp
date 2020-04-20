#pragma once
#include "pch.h"
#include "ResourceLoader.h"
#include <Tools/Logger.h>


ResourceLoader::~ResourceLoader() {

}

std::shared_ptr<Texture> ResourceLoader::LoadTexture(const string& filepath) {
	Logger::LogInfo("Loading a texture");

	std::shared_ptr<Texture> texture;

	// Create a texture object
	texture = std::make_shared<Texture>(0);

	return texture;
}

std::shared_ptr<Geometry> ResourceLoader::LoadGeometry(const string& filepath) {
	return LoadOBJ(filepath);
}

std::shared_ptr<IResource> ResourceLoader::LoadResource(const string& filepath) {
	Logger::LogInfo("Loading Resource");

	shared_ptr<IResource> resource = std::make_shared<IResource>();
	return resource;
}

std::shared_ptr<Geometry> ResourceLoader::LoadOBJ(const string& filepath) {
	Logger::LogInfo("Loading Geometry from OBJ");

	std::shared_ptr<Geometry> model = std::make_shared<Geometry>();

	return model;
}