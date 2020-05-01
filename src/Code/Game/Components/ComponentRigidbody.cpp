#include "ComponentRigidbody.h"


ComponentRigidbody::ComponentRigidbody(float gravity) :
	_isKinematic(false),
	_isGravityAffected(false),
	_gravityVal(gravity),
	_mass(1),
	_frictionCoeff(0),
	_netForce(0, 0, 0),
	_acceleration(0, 0, 0),
	_velocity(0, 0, 0) {
	_componentType = ComponentManager::GetInstance().GetIDByType(typeid(ComponentRigidbody));
}

ComponentRigidbody::~ComponentRigidbody() {

}

IComponent* ComponentRigidbody::Clone() {
	return new ComponentRigidbody(_gravityVal);
}

int ComponentRigidbody::ComponentType() const {
	return _componentType;
}

void ComponentRigidbody::Message(IMessage* message) {
	// nothing to do
}
