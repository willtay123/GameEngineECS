#include "ComponentModelGL.h"



ComponentModelGL::ComponentModelGL() :
	_model(nullptr) {
	_componentType = ComponentManager::GetInstance().GenerateIDByType(this);
}

ComponentModelGL::ComponentModelGL(const string& filepath) {
	_componentType = ComponentManager::GetInstance().GenerateIDByType(this);
	std::shared_ptr<Geometry> geom = ResourceManager::GetInstance().LoadModelByPath(filepath).lock();
	_model = new OpenGLModel(geom);
}

ComponentModelGL::ComponentModelGL(OpenGLModel* model) :
	_model(model)
{
	_componentType = ComponentManager::GetInstance().GenerateIDByType(this);
}

ComponentModelGL::ComponentModelGL(const ComponentModelGL& rhs) :
	_model(rhs._model) {

}

ComponentModelGL::~ComponentModelGL() {
	delete _model;
}

ComponentModelGL& ComponentModelGL::operator=(const ComponentModelGL& rhs) {
	if (this != &rhs) {
		_componentType = rhs._componentType;
		_model = rhs._model;
	}
	return *this;
}

ComponentModelGL* ComponentModelGL::Clone() {
	ComponentModelGL* clone = new ComponentModelGL(*this);
	return clone;
}

int ComponentModelGL::ComponentType() const {
	return _componentType;
}

void ComponentModelGL::Message(IMessage* message) {

}

void ComponentModelGL::SetModel(OpenGLModel* model) {
	// May want data validation here
	_model = model;
}

const OpenGLModel* ComponentModelGL::GetModel() const {
	return _model;
}