#include "MainScene.h"
#include <IO\EntityFactory.h>
#include <Tools/Logger.h>



MainScene::MainScene() {
	_name = "Main Scene";
	string text = string("Scene Created: " + _name);
	Logger::LogInfo(text);
}

MainScene::~MainScene() {

}

void MainScene::Initialise() {
	// Camera
	_camera = new Camera();
	_camera->SetPosition(vec3(0, 0, 10));
	_camera->LookAt(vec3(0, 0, 0), vec3(0,1,0));

	// IO
	RendererGL* rend = (RendererGL*)RenderManager::GetInstance().GetRenderer();
	GLFWwindow* window = rend->GetWindow();
	glfwSetKeyCallback(window, Keyboard::KeyCallback);

	// Entities
	//string filepath = "Assets/Data/entities.xml";
	//EntityFactory::LoadFromFile("game", filepath);
	CreatePyramid(vec3(0,0,0), 5);

	// Create Systems
	shared_ptr<ISystem> system = make_shared<SystemRigidBody>();
	SystemManager::GetInstance().AddUpdateSystem(system);

	// Create timer
	_timeSinceStart = 0;
}

void MainScene::Update(double dt) {
	ProcessInput();

	// Systems
	SystemManager::GetInstance().ActionUpdateSystems(dt);

	// Update Camera
	_camera->Update(dt);

	// Time
	_timeSinceStart += dt;

}

void MainScene::Render() {
	shared_ptr<const EntityList> entities = EntityManager::GetInstance().GetEntities(_name);
	RenderManager::GetInstance().Draw(*_camera, entities);
}

void MainScene::ProcessInput() {
	float x = 0, y = 0, z = 0;
	float moveValue = 2;
	
	// Move foward
	if (Keyboard::KeyPressed(GLFW_KEY_W))
		z -= moveValue;
	// Move left
	if (Keyboard::KeyPressed(GLFW_KEY_A))
		x -= moveValue;
	// Move back
	if (Keyboard::KeyPressed(GLFW_KEY_S))
		z += moveValue;
	// Move right
	if (Keyboard::KeyPressed(GLFW_KEY_D))
		x += moveValue;
	
	_camera->MoveBy(vec3(x, y, z));
}

void MainScene::CreatePyramid(const vec3& origin, int size) {
	EntityManager::GetInstance().ClearCurrentEntities();

	int length = size;

	for (float y = 0; y < size; y++) {
		// Create a square of lengthxlength

		// will round wrong
		for (float x = -(length / 2.0f); x < (length / 2.0f); x++) {
			for (float z = -(length / 2.0f); z < (length / 2.0f); z++) {
				float mod = 3;
				vec3 position(origin.x + (x * mod), origin.y + (y * mod), origin.z + (z * mod));

				CreateSphere(position);
			}
		}

		length--;
	}
}

void MainScene::CreateSphere(const vec3& position) {
	shared_ptr<Entity> entity = std::make_shared<Entity>("sphere");

	// Transform
	ComponentTransform* transform = new ComponentTransform(
		position,
		vec3(0.1, 0.1, 0.1),
		vec3(0, 0, 0)
	);
	entity->AddComponent(transform);

	// Model
	ComponentModelGL* modelGL = new ComponentModelGL("Assets/Models/sphere.obj");
	entity->AddComponent(modelGL);

	// Texture
	ResourceID textureID = ResourceManager::GetInstance().LoadTextureByPath("Assets/Textures/testImage.png");
	ComponentTexture* textureComp = new ComponentTexture(textureID);
	entity->AddComponent(textureComp);

	// Rigidbody
	float gravity = 9.0f;
	ComponentRigidbody* rigidbody = new ComponentRigidbody(gravity);
	rigidbody->SetIsKinematic(true);
	rigidbody->SetIsGravityAffected(true);
	rigidbody->SetMass(1);
	rigidbody->SetFrictionCoefficient(0.2);
	entity->AddComponent(rigidbody);

	// Sphere Collider
	float radius = 1;
	ComponentSphereCollider* collider = new ComponentSphereCollider(0, 0, 0, radius);
	entity->AddComponent(collider);

	EntityManager::GetInstance().AddEntity(_name, entity);
}

void MainScene::Close() {
}