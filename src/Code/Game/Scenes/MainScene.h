#pragma once

#include "Interfaces/IScene.h"

#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdlib.h>

#include <Managers/Managers.h>
#include <Objects/Camera.h>

#include "Objects/Entity.h"
#include "Interfaces/IComponent.h"

#include "Systems/SystemRigidBody.h"

#include "Components/ComponentTransform.h"
#include "Components/BasicGL.h"
#include "Components/ComponentRigidbody.h"
#include "Components/ComponentSphereCollider.h"
#include "Components/ComponentScore.h"

#include "IO/Keyboard.h"
#include "Implementations/RendererGL.h"

using namespace EngineECS;

class MainScene : public IScene {
private:
	Camera* _camera;
	double _timeSinceStart;

	void ProcessInput();
	void CreatePyramid(const vec3& origin, int size);
	void CreateSphere(const vec3& position, float size, bool isKinematic);

public:
	MainScene();
	MainScene(const MainScene& rhs) = delete;
	~MainScene() override;
	MainScene& operator=(const MainScene& rhs) = delete;
	
	void Initialise();

	void Update(double dt);
	void Render();
	void Close();
};