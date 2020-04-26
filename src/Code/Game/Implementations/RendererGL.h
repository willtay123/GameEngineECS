#pragma once

#include "Interfaces/IRenderer.h"
#include "GLAD/glad.h"
#include "GLFW/glfw3.h"

#include "Interfaces/IComponent.h"
#include "Components/ComponentTransform.h"
#include "Components/ComponentModelGL.h"
#include "Components/ComponentTexture.h"
#include "CleverPointers.h"

using namespace EngineECS;

class RendererGL : public IRenderer {
private:
	GLFWwindow* _window;
	int _screenWidth;
	int _screenHeight;
	const char* _windowTitle;

public:
	RendererGL();
	RendererGL(const RendererGL& rhs) = delete;
	~RendererGL();
	RendererGL& operator=(const RendererGL& rhs) = delete;

	bool Initialise();
	
	void Draw(const Camera& camera, const shared_ptr<const Entity> entity);
	void Draw(const Camera& camera, const shared_ptr<const EntityList> entityList);

	GLFWwindow* GetWindow();

	void StartUpdate();
	void EndUpdate();

	void StartRender();
	void EndRender();

	void Unload();
};