#pragma once
#include "Interfaces/IScene.h"

#include <iostream>
#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "Managers/Managers.h"
#include "Objects/Camera.h"
#include "IO/Keyboard.h"
#include "Implementations/RendererGL.h"

#include "Objects/Entity.h"
#include "Interfaces/IComponent.h"
#include "Components/ComponentTransform.h"

#include "Components/BasicGL.h"

using namespace EngineECS;

class EndScene : public IScene {
private:
	Camera* _camera;

	void ProcessInput();

public:
	EndScene();
	EndScene(const EndScene& rhs) = delete;
	~EndScene();
	EndScene& operator=(const EndScene& rhs) = delete;

	void Initialise();

	void Update(double dt);
	void Render();
	void Close();
};