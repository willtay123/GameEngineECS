#pragma once
#include "RendererGL.h"
#include <Tools/Logger.h>



RendererGL::RendererGL() {
	_window = NULL;
	_screenWidth = 1080;
	_screenHeight = 720;
	_windowTitle = "Component-Based game engine";
}

RendererGL::~RendererGL() {

}

bool RendererGL::Initialise() {
	Logger::LogInfo("Initialising renderer");

	if (!glfwInit()) {
		Logger::LogError("Error initialising GLFW");
		return false;
	}

	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_DEPTH_BITS, 16);

	_window = glfwCreateWindow(_screenWidth, _screenHeight, _windowTitle, NULL, NULL);
	if (!_window) {
		glfwTerminate();
		Logger::LogError("Failed to create window");
		return false;
	}

	//--GLFW setup
	glfwMakeContextCurrent(_window);
	int width, height;
	glfwGetFramebufferSize(_window, &width, &height);

	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int screenWidth = 1080, screenHeight = 720;
	int xPos = (mode->width - screenWidth) / 2;
	int yPos = (mode->height - screenHeight) / 2;
	glfwSetWindowPos(_window, xPos, yPos);

	//GLAD setup
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);


	//--callbacks

	//window
	//glfwSetWindowCloseCallback(window, Engine::End); //works but doesnt seem to actually close

	//mouse
	//glfwSetCursorPosCallback(window, Mouse::MousePosCallback);
	//glfwSetMouseButtonCallback(window, Mouse::MouseButtonCallback);
	//keyboard
	//glfwSetKeyCallback(window, Keyboard::KeyCallback);

	//--OpenGL setup

	//viewport
	glViewport(0, 0, width, height);

	// Winding
	glFrontFace(GL_CCW);

	// Depth
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDepthFunc(GL_LESS);
	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	glCullFace(GL_BACK);

	//alpha blending
	//glEnable(GL_ALPHA);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//initial settings
	glClearColor(1, 0.5, 0, 1); // Normalised RGBA

	// Successful
	return true;
}

void RendererGL::Draw(const Camera& camera, const shared_ptr<const Entity> entity) { // Likely to fail here due to resource change

	const ComponentTransform* transfComponent = static_cast<const ComponentTransform*>(entity->GetComponentByType(typeid(ComponentTransform)));
	const ComponentModelGL* modelComponent = static_cast<const ComponentModelGL*>(entity->GetComponentByType(typeid(ComponentModelGL)));
	const ComponentTexture* textureComponent = static_cast<const ComponentTexture*>(entity->GetComponentByType(typeid(ComponentTexture)));

	if (transfComponent &&
		modelComponent &&
		textureComponent) {

		// Camera matrix
		const glm::mat4 view = camera.GetView();
		const glm::mat4 projection = camera.GetProjection();

		// Model Matrix
		const mat4 modelMatrix = transfComponent->GetMatrix();

		// Our ModelViewProjection : multiplication of our 3 matrices
		mat4 mvp = projection * view * modelMatrix;

		// Fetch model data
		const OpenGLModel* model = modelComponent->GetModel();
		GLuint dataHandle = model->GetDBOHandle();
		GLuint indicesHandle = model->GetIBOHandle();

		// Fetch texture data
		GLuint textureID = textureComponent->GetTextureID(); // ID of resource and not GL id?

		// Update uniform shader variables
		GLuint _uniform_MVP = 0; //TODO: get this value from the shader
		glUniformMatrix4fv(_uniform_MVP, 1, GL_FALSE, &mvp[0][0]);

		// Texture
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureID);
		glEnable(GL_TEXTURE_2D);

		glBindBuffer(GL_ARRAY_BUFFER, dataHandle);

		// Vertices
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,							// attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,							// size
			GL_FLOAT,					// type
			GL_FALSE,					// normalized?
			8 * sizeof(float),			// stride
			(void*)0					// array buffer offset
		);

		//NOTE: buffer offset may be wrong
		// UVs
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,                          // attribute. No particular reason for 1, but must match the layout in the shader.
			2,                          // size
			GL_FLOAT,                   // type
			GL_FALSE,                   // normalized?
			8 * sizeof(float),			// stride
			(float*)(3 * sizeof(float))	// array buffer offset
		);

		// Normals
		//glEnableVertexAttribArray(2);
		//glVertexAttribPointer(
		//	2,                          // attribute. No particular reason for 1, but must match the layout in the shader.
		//	2,                          // size
		//	GL_FLOAT,                   // type
		//	GL_FALSE,                   // normalized?
		//	8 * sizeof(float),			// stride
		//	(float*)(5 * sizeof(float))	// array buffer offset
		//);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, model->GetIBOHandle());

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,					// mode
			model->GetTriangleCount(),		// count
			GL_UNSIGNED_SHORT,				// type
			(void*)0						// element array buffer offset
		);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		//glDisableVertexArrayAttrib(2);
	}
}

void RendererGL::Draw(const Camera& camera, const std::shared_ptr<const EntityList> entityList) {
	// Draw all entities one after another, slow and inefficient due to memory swaps
	// For a more efficient draw, try to re-organise for similar textures
	for (int i = 0; i < entityList->size(); i++) {
		shared_ptr<Entity> entity = (*entityList)[i];
		Draw(camera, entity);
	}
}

GLFWwindow* RendererGL::GetWindow() {
	return _window;
}

void RendererGL::StartUpdate() {
	glfwPollEvents();
}

void RendererGL::EndUpdate() {

}

void RendererGL::StartRender() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RendererGL::EndRender() {
	glfwSwapBuffers(_window);
}

void RendererGL::Unload() {

}