#include "EntityFactory.h"
#include <Components\ComponentTransform.h>
#include <Components\ComponentModelGL.h>
#include <Components\ComponentTexture.h>
#include <Components\ComponentPhysics.h>
#include <Components\ComponentSphereCollider.h>
#include <Components\ComponentScore.h>


void EntityFactory::LoadFromFile(const string& sceneName, const string& filepath) {
	xml_document doc;
	xml_parse_result result = doc.load_file(filepath.c_str());
	if (!result) {
		return;
	}

	for (xml_node entityNode : doc.root().first_child().children()) {
		std::unique_ptr<Entity> entity(LoadEntity(entityNode));

		EntityManager::GetInstance().AddEntity(sceneName, std::move(entity));
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

	Entity* entity = new Entity(name);

	for (size_t i = 0; i < components.size(); i++) {
		entity->AddComponent(components[i]);
	}
	components.clear();
	
	return entity;
}

IComponent* EntityFactory::LoadComponent(xml_node& componentNode) {
	IComponent* component;
	string componentName = componentNode.name();

	if (componentName == "transformComponent") {
		component = LoadComponentTransform(componentNode);
	}
	else if (componentName == "modelGLComponent") {
		component = LoadComponentModelGL(componentNode);
	}
	else if (componentName == "textureComponent") {
		component = LoadComponentTexture(componentNode);
	}
	else if (componentName == "physicsComponent") {
		component = LoadComponentPhysics(componentNode);
	}
	else if (componentName == "sphereColliderComponent") {
		component = LoadComponentSphereCollider(componentNode);
	}
	else if (componentName == "scoreComponent") {
		component = LoadComponentScore(componentNode);
	}
	else {
		component = new ComponentTransform();
	}

	return component;
}

string EntityFactory::LoadAttributeString(const xml_node& stringNode) {
	string text = stringNode.text().as_string();
	return text;
}

vec4 EntityFactory::LoadAttributeVec4(const xml_node& vecNode) {
	float x = vecNode.child("x").text().as_float();
	float y = vecNode.child("y").text().as_float();
	float z = vecNode.child("z").text().as_float();
	float w = vecNode.child("w").text().as_float();

	return vec4(x, y, z, w);
}

vec3 EntityFactory::LoadAttributeVec3(const xml_node& vecNode) {
	float x = vecNode.child("x").text().as_float();
	float y = vecNode.child("y").text().as_float();
	float z = vecNode.child("z").text().as_float();

	return vec3(x, y, z);
}

IComponent* EntityFactory::LoadComponentTransform(xml_node& transformComponent) {
	vec4 position = LoadAttributeVec4(transformComponent.child("position"));
	vec3 rotation = LoadAttributeVec4(transformComponent.child("rotation"));
	vec3 scale = LoadAttributeVec3(transformComponent.child("scale"));

	ComponentTransform* component;
	component = new ComponentTransform();
	component->SetPosition(&position);
	component->SetRotation(&rotation);
	component->SetScale(&scale);

	return component;
}

IComponent* EntityFactory::LoadComponentModelGL(xml_node& modelNode) {
	string filepath = LoadAttributeString(modelNode.child("filepath"));

	ComponentModelGL* component;
	component = new ComponentModelGL(filepath);
	return component;
}

IComponent* EntityFactory::LoadComponentTexture(xml_node& textureNode) {
	string filepath = LoadAttributeString(textureNode.child("filepath"));
	// load into resource manager
	ResourceID resourceID = ResourceManager::GetInstance().LoadTextureByPath(filepath);

	// create component with ResourceID
	ComponentTexture* component;
	component = new ComponentTexture(resourceID);
	
	return component;
}

IComponent* EntityFactory::LoadComponentPhysics(xml_node& physicsNode) {
	float gravity = physicsNode.child("gravity").text().as_float();

	ComponentPhysics* component;
	component = new ComponentPhysics(gravity);
	return component;
}

IComponent* EntityFactory::LoadComponentSphereCollider(xml_node& colliderNode) {
	vec3 offset = LoadAttributeVec3(colliderNode.child("offset"));
	float radius = colliderNode.child("radius").text().as_float();

	ComponentSphereCollider* component;
	component = new ComponentSphereCollider(offset.x, offset.y, offset.z, radius);
	return component;
}

IComponent* EntityFactory::LoadComponentScore(xml_node& scoreNode) {
	ComponentScore* component;
	component = new ComponentScore();
	return component;
}