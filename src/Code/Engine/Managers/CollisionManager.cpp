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

void CollisionManager::DetectCollision(const Entity& entity1, const Entity& entity2) {
	if (_collisionDetector) {
		ICollisionManifold* manifold = _collisionDetector->CollisionCheck(entity1, entity2);
		if (manifold != NULL) {
			_collisions.push_back(manifold);
		}
	}
}

void CollisionManager::DetectCollisions(const std::shared_ptr<EntityList> entityList) {
	if (_collisionDetector) {
		vector<ICollisionManifold*>* manifoldList = _collisionDetector->CollisionCheck(entityList);
		if (manifoldList != NULL) {
			if (manifoldList->size() > 0) {
				// Merge the collision lists
				_collisions.insert(
					_collisions.end(),
					manifoldList->begin(),
					manifoldList->end()
				);

				// Empty old list
				manifoldList->clear();
			}

			delete manifoldList;
		}
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
