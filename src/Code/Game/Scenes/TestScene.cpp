#include "TestScene.h"
#include <IO\EntityFactory.h>
#include <Tools/Logger.h>



TestScene::TestScene() {
	_name = "Test Scene";
	string text = string("Scene Created: " + _name);
	Logger::LogInfo(text);
}

TestScene::TestScene(const TestScene& rhs) {

}

TestScene::~TestScene() {

}

void TestScene::Initialise() {
	// Camera
	_camera = new Camera();
	_camera->MoveTo(&vec3(0, 10, 0));
	_camera->LookPosition(&vec3(0, 0, 0));
	_camera->SetUp(&vec3(0, 0, 1));

	// IO
	RendererGL* rend = (RendererGL*)RenderManager::GetInstance().GetRenderer();
	GLFWwindow* window = rend->GetWindow();
	glfwSetKeyCallback(window, Keyboard::KeyCallback);

	string filepath = "Assets/Data/entities.xml";
	EntityFactory::LoadFromFile("game", filepath);

	// Create Systems
	//ISystem* system;
	//system = new SystemPhysics();
	//SystemManager::GetInstance().AddUpdateSystem(system);

	// Create timer
	_timeSinceStart = 0;
}

void TestScene::Update(double dt) {
	// Update Camera
	_camera->Update(dt);

	// Time
	_timeSinceStart += dt;

	ProcessInput();
}

void TestScene::Render() {
	std::weak_ptr<EntityList> entities = EntityManager::GetInstance().GetEntities("game");
	RenderManager::GetInstance().Draw(_camera, entities.lock());
}

void TestScene::ProcessInput() {
	std::shared_ptr<Entity> player = EntityManager::GetInstance().GetEntityEditable("game", "player").lock();
	int physID = ComponentManager::GetInstance().GetIDForType(typeid(ComponentPhysics));
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