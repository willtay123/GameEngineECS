#pragma once
#include "Interfaces/IScene.h"

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>

#include "Managers/Managers.h"
#include "Objects/Camera.h"
#include "IO/Keyboard.h"
#include "Externals/Implementations/RendererGL.h"

#include "Objects/Entity.h"
#include "Interfaces/IComponent.h"
#include "Components/ComponentTransform.h"

#include "Externals/Components/BasicGL.h"

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