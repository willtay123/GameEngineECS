#include "CollisionManager.h"

using namespace EngineECS;


CollisionManager* CollisionManager::Instance = nullptr;

CollisionManager::CollisionManager() :
	_collisionDetector(nullptr),
	_collisionResponder(nullptr),
	_collisions() {
	
}

CollisionManager::~CollisionManager() {
	delete _collisionDetector;
	delete _collisionResponder;
	
	ClearCollisions();
}

CollisionManager& CollisionManager::GetInstance() {
	if (!Instance) {
		Instance = new CollisionManager();
	}
	return *Instance;
}

void CollisionManager::SetCollisionDetector(ICollisionDetector* detector) {
	_collisionDetector = detector;
}

void CollisionManager::SetCollisionResponder(ICollisionResponder* responder) {
	_collisionResponder = responder;
}

void CollisionManager::DetectCollisions(const std::weak_ptr<EntityList> entityList) {
	// Ensure a detector is set
	if (_collisionDetector) {
		// Get manifolds for all collisions
		_collisionDetector->DetectCollisions(entityList, _collisions);
	}
}

void CollisionManager::HandleCollisions() {
	if (_collisionResponder) {
		_collisionResponder->HandleCollisions(_collisions);

		ClearCollisions();
	}
}

void CollisionManager::ClearCollisions() {
	for (ICollisionManifold* manifold : _collisions) {
		delete manifold;
	}
	_collisions.clear();
}
