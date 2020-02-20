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
#include "Components/ComponentTransform.h"

#include "Components/BasicGL.h"
#include "Components/ComponentPhysics.h"
#include "Components/ComponentSphereCollider.h"
#include "Components/ComponentScore.h"

#include "Systems/SystemPhysics.h"

#include "IO/Keyboard.h"
#include "Implementations/RendererGL.h"

using namespace EngineECS;

class TestScene : public IScene {
private:
	Camera* _camera;
	double _timeSinceStart;

	void ProcessInput();

public:
	TestScene();
	TestScene(const TestScene& rhs);
	~TestScene() override;
	TestScene& operator=(const TestScene& rhs) = delete;
	
	void Initialise();

	void Update(double dt);
	void Render();
	void Close();
};