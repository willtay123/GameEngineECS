#include "EndScene.h"



EndScene::EndScene() {
	_name = "End Screen";
}

EndScene::~EndScene() {
	delete _camera;
}

void EndScene::Initialise() {
	_camera = new Camera();
	_camera->MoveTo(&vec3(0, 10, 0));
	_camera->LookPosition(&vec3(0, 0, 0));
	_camera->SetUp(&vec3(0, 0, 1));

	// IO
	RendererGL* rend = (RendererGL*)RenderManager::GetInstance().GetRenderer();
	GLFWwindow* window = rend->GetWindow();
	glfwSetKeyCallback(window, Keyboard::KeyCallback);

	string entName("entity1");
	std::unique_ptr<Entity> entity(new Entity(entName));
	IComponent* comp = new ComponentTransform(0, 0, 0, 0, 3.14159f, 0, 10, 10, 10);
	entity->AddComponent(comp);
	comp = new ComponentModelGL("Assets/Models/cube.obj");
	entity->AddComponent(comp);
	comp = new ComponentTexture("Externals/Assets/Textures/End.png");
	entity->AddComponent(comp);
	EntityManager::GetInstance().AddEntity(_name, std::move(entity));
}

void EndScene::Update(double dt) {
	_camera->Update(dt);

	ProcessInput();
}

void EndScene::Render() {
	std::weak_ptr<EntityList> entities = EntityManager::GetInstance().GetEntities(_name);
	RenderManager::GetInstance().Draw(_camera, entities.lock());
}

void EndScene::Close() {

}

void EndScene::ProcessInput() {
	if (Keyboard::KeyPressed(GLFW_KEY_SPACE)) {
		// Change back to game
		SceneManager sm = SceneManager::GetInstance();
		sm.SetScene("game");
	}
}