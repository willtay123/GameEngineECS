#include "CollisionManifold.h"



CollisionManifold::CollisionManifold(shared_ptr<Entity> entity1, shared_ptr<Entity> entity2) {
	_entity1 = entity1;
	_entity2 = entity2;
}

CollisionManifold::CollisionManifold(const CollisionManifold& rhs) {
	_entity1 = rhs._entity1;
	_entity2 = rhs._entity2;
}

CollisionManifold::~CollisionManifold() {

}

CollisionManifold& CollisionManifold::operator=(const CollisionManifold& rhs) {
	if (this != &rhs) {
		_entity1 = rhs._entity1;
		_entity2 = rhs._entity2;
	}
	return *this;
}

shared_ptr<Entity> CollisionManifold::GetEntity1() const {
	return _entity1;
}

shared_ptr<Entity> CollisionManifold::GetEntity2() const {
	return _entity2;
}