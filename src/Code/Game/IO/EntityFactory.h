#pragma once

#include <string>
#include "pugixml/pugixml.hpp"
#include "GLM/glm/vec3.hpp"
#include "GLM/glm/vec4.hpp"
#include "Managers/EntityManager.h"
#include "Objects/Entity.h"

using namespace EngineECS;
using namespace pugi;
using std::string;
using glm::vec3;
using glm::vec4;

class EntityFactory {
private:
	static Entity* LoadEntity(xml_node& entityNode);
	static IComponent* LoadComponent(xml_node& componentNode);

	static string LoadAttributeString(const xml_node& stringNode);
	static vec4 LoadAttributeVec4(const xml_node& vecNode);
	static vec3 LoadAttributeVec3(const xml_node& vecNode);

	static IComponent* LoadComponentTransform(xml_node& transformComponent);
	static IComponent* LoadComponentModelGL(xml_node& modelNode);
	static IComponent* LoadComponentTexture(xml_node& textureNode);
	static IComponent* LoadComponentPhysics(xml_node& physicsNode);
	static IComponent* LoadComponentSphereCollider(xml_node& colliderNode);
	static IComponent* LoadComponentScore(xml_node& scoreNode);

public:
	static void LoadFromFile(string sceneName, string filepath);
};