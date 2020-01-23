#include "CollisionManifold.h"



CollisionManifold::CollisionManifold(Entity* entity1, Entity* entity2) {
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

Entity* CollisionManifold::GetEntity1() const {
	return _entity1;
}

Entity* CollisionManifold::GetEntity2() const {
	return _entity2;
}