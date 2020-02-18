#include "TestScene.h"
#include <IO\EntityFactory.h>
#include <Tools/Logger.h>



TestScene::TestScene() {
	_name = "Test Scene";
	string text = string("Scene Created: " + _name);
	Logger::LogInfo(text);
}

TestScene::~TestScene() {

}

void TestScene::Initialise() {
	// Camera
	_camera = new Camera();
	_camera->SetPosition(vec3(0, 10, 0));
	_camera->LookAt(vec3(0, 0, 0), vec3(0,1,0));
	_camera->SetUp(vec3(0, 0, 1));

	// IO
	RendererGL* rend = (RendererGL*)RenderManager::_renderer;
	GLFWwindow* window = rend->GetWindow();
	glfwSetKeyCallback(window, Keyboard::KeyCallback);
;
	// Create Entities

	// Entities: Item
	GenerateItems(10);

	string filepath = "Assets/Data/entities.xml";
	EntityFactory::LoadFromFile("game", filepath);

	// Entity: player
	//Entity* playerEntity = new Entity(&string("player"));
	//IComponent* comp = new ComponentTransform(0, 0, 0,
	//	0, 0.0f, 0,
	//	1, 0.5f, 1);
	//playerEntity->AddComponent(comp);
	//comp = new ComponentModelGL("Assets/Models/cube.obj");
	//playerEntity->AddComponent(comp);
	//comp = new ComponentTexture("Assets/Textures/testImage.png");
	//playerEntity->AddComponent(comp);
	//comp = new ComponentPhysics(3);
	//playerEntity->AddComponent(comp);
	//comp = new ComponentSphereCollider(0, 0, 0, 0.5);
	//playerEntity->AddComponent(comp);
	//comp = new ComponentScore();
	//playerEntity->AddComponent(comp);
	//EntityManager::AddEntity("game", playerEntity);

	// Create Systems
	ISystem* system;
	system = new SystemPhysics();
	SystemManager::AddUpdateSystem(system);

	// Create timer
	_timeSinceStart = 0;
}

void TestScene::GenerateItems(int numberOfItems) {
	// Generate random seem
	srand((unsigned int)time(NULL));
	for (int i = 1; i < numberOfItems; i++) {
		// Generate Name
		string name = "item_";
		name += std::to_string(i);

		// Generate Position
		int spawnMin = -7;
		int spawnMax = 7;
		float x = spawnMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (spawnMax - spawnMin)));
		float z = spawnMin + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (spawnMax - spawnMin)));

		// Create Item
		Entity* entity = new Entity(&name);
		IComponent* comp = new ComponentTransform(x, 0, z,
			0, 3.14f, 0,
			0.5f, 0.5f, 0.5f);
		entity->AddComponent(comp);
		comp = new ComponentModelGL("Assets/Models/cube.obj");
		entity->AddComponent(comp);
		comp = new ComponentTexture("Assets/Textures/Pokeball.png");
		entity->AddComponent(comp);
		comp = new ComponentSphereCollider(0, 0, 0, 0.5);
		entity->AddComponent(comp);
		EntityManager::AddEntity("game", entity);
	}
}

void TestScene::Update(double dt) {
	// Update Camera
	_camera->Update(dt);

	// Time
	_timeSinceStart += dt;

	// Collisions
	vector<Entity*>* entities = EntityManager::GetEntitiesEditable("game");
	CollisionManager::DetectCollisions(entities);
	CollisionManager::HandleCollisions();

	int transformID = ComponentManager::GetIDForString("Transform");

	ProcessInput();

	// Rotate the items
	string itemStart("item_");
	vector<Entity*> itemList = EntityManager::GetStartingWith("game", itemStart);
	if (itemList.size() == 0) {
		GenerateItems(10);
	}
	else {
		for (int i = 0; i < itemList.size(); i++) {
			Entity* entity = itemList[i];
			ComponentTransform* trans = static_cast<ComponentTransform*>(entity->GetComponentEditable(transformID));
			const vec3* rot = trans->GetRotation();
			vec3 newRot = vec3(rot->x, rot->y + (1 * dt), rot->z);
			trans->SetRotation(&newRot);
		}
	}

	// Update systems
	SystemManager::ActionUpdateSystems(dt, "game");

	// Clean Collisions
	CollisionManager::ClearCollisions();

	//if (_timeSinceStart > 10) {
	//	_timeSinceStart = -1;
	//	SceneManager* sm = SceneManager::GetInstance();
	//	if (sm->HasScene("End Screen")) {
	//		sm->SetScene("End Screen");
	//	}
	//	else {
	//		IScene* scene = new EndScene();
	//		sm->SetScene("End Screen", scene);
	//	}
	//}
}

void TestScene::Render() {
	const vector<Entity*>* entities = EntityManager::GetEntities("game");
	RenderManager::Draw(_camera, entities);
}

void TestScene::ProcessInput() {
	Entity* player = EntityManager::GetEntityEditable("game", "player");
	int physID = ComponentManager::GetIDForString("Physics");
	ComponentPhysics* physComp = (ComponentPhysics*)player->GetComponentEditable(physID);

	if (physComp) {
		float x = 0, y = 0, z = 0;
		float moveValue = 10;

		// Move foward
		if (Keyboard::KeyPressed(GLFW_KEY_W))
			z += moveValue;
		// Move left
		if (Keyboard::KeyPressed(GLFW_KEY_A))
			x += moveValue;
		// Move back
		if (Keyboard::KeyPressed(GLFW_KEY_S))
			z -= moveValue;
		// Move right
		if (Keyboard::KeyPressed(GLFW_KEY_D))
			x -= moveValue;

		physComp->SetAcceleration(x, y, z);
	}
}

void TestScene::Close() {
	//clean buffers?
}