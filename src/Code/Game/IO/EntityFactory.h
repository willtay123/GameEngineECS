#pragma once

#include <string>
#include "pugixml/pugixml.hpp"
#include "Managers/EntityManager.h"
#include "Objects/Entity.h"

#include "Components/ComponentTransform.h"

using namespace EngineECS;
using namespace pugi;
using std::string;

class EntityFactory {
private:
	static Entity* LoadEntity(xml_node& entityNode);
	static IComponent* LoadComponent(xml_node& componentNode);

	static vec4 LoadVec4(const xml_node& vecNode);
	static vec3 LoadVec3(const xml_node& vecNode);

	static IComponent* LoadComponentTransform(xml_node& transformComponent);

public:
	static void LoadFromFile(string sceneName, string filepath);
};