#pragma once

#include <string>
#include "Interfaces/IComponent.h"
#include "Implementations/OpenGLModel.h"

#include "Managers/ResourceManager.h"

using std::string;

class ComponentModelGL : public IComponent {
private:
	OpenGLModel* _model;

public:
	ComponentModelGL();
	ComponentModelGL(const string& filepath);
	ComponentModelGL(OpenGLModel* model);
	ComponentModelGL(const ComponentModelGL& rhs);
	~ComponentModelGL();
	ComponentModelGL& operator=(const ComponentModelGL& rhs);

	ComponentModelGL* Clone();
	int ComponentType() const;
	void Message(IMessage* message);

	void SetModel(OpenGLModel* model);
	const OpenGLModel* GetModel() const;
};

