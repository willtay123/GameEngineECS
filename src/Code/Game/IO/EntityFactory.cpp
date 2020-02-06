#include "EntityFactory.h"


void EntityFactory::LoadFromFile(string sceneName, string filepath) {
	xml_document doc;
	xml_parse_result result = doc.load_file(filepath.c_str());
	if (!result) {
		return;
	}

	for (xml_node entityNode : doc.root().first_child().children()) {
		Entity* entity = LoadEntity(entityNode);

		EntityManager::AddEntity(sceneName.c_str(), entity);
	}
}

Entity* EntityFactory::LoadEntity(xml_node& entityNode) {
	xml_node nameNode = entityNode.child("name");

	string name = nameNode.text().as_string();
	vector<IComponent*> components;

	for (xml_node componentNode : entityNode.child("components")) {
		IComponent* component = LoadComponent(componentNode);
		components.push_back(component);
	}

	Entity* entity = new Entity(&name);

	for (int i = 0; i < components.size(); i++) {
		entity->AddComponent(components[i]);
	}
	
	return entity;
}

IComponent* EntityFactory::LoadComponent(xml_node& componentNode) {
	IComponent* component;
	string componentName = componentNode.name();

	if (componentName == "transformComponent") {
		component = LoadComponentTransform(componentNode);
	}
	else {
		component = new ComponentTransform();
	}

	return component;
}

IComponent* EntityFactory::LoadComponentTransform(xml_node& transformComponent) {
	vec4 position = LoadVec4(transformComponent.child("position"));
	vec3 rotation = LoadVec4(transformComponent.child("rotation"));
	vec3 scale = LoadVec3(transformComponent.child("scale"));

	ComponentTransform* component;
	component = new ComponentTransform();
	component->SetPosition(&position);
	component->SetRotation(&rotation);
	component->SetScale(&scale);

	return component;
}

vec4 EntityFactory::LoadVec4(const xml_node& vecNode) {
	float x = vecNode.child("x").text().as_float();
	float y = vecNode.child("y").text().as_float();
	float z = vecNode.child("z").text().as_float();
	float w = vecNode.child("w").text().as_float();

	return vec4(x, y, z, w);
}

vec3 EntityFactory::LoadVec3(const xml_node& vecNode) {
	float x = vecNode.child("x").text().as_float();
	float y = vecNode.child("y").text().as_float();
	float z = vecNode.child("z").text().as_float();

	return vec3(x, y, z);
}