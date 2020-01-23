#pragma once

#include "Interfaces/IScene.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include <stdlib.h>

#include <Managers/Managers.h>
#include <Objects/Camera.h>

#include "Objects/Entity.h"
#include "Interfaces/IComponent.h"
#include "Components/ComponentTransform.h"

#include "Externals/Components/BasicGL.h"
#include "Externals/Components/ComponentPhysics.h"
#include "Externals/Components/ComponentSphereCollider.h"
#include "Externals/Components/ComponentScore.h"

#include "Externals/Systems/SystemPhysics.h"
#include "Externals/Scenes/EndScene.h"

#include "IO/Keyboard.h"
#include "Externals/Implementations/RendererGL.h"

class TestScene : public IScene {
private:
	Camera* _camera;
	double _timeSinceStart;

	void ProcessInput();

public:
	TestScene();
	TestScene(const TestScene& rhs) = delete;
	~TestScene();
	TestScene& operator=(const TestScene& rhs) = delete;
	
	void Initialise();

	void GenerateItems(int numberOfItems);

	void Update(double dt);
	void Render();
	void Close();
};