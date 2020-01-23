#include "CollisionManager.h"



ICollisionDetector* CollisionManager::_collisionDetector;
ICollisionResponder* CollisionManager::_collisionResponder;
vector<ICollisionManifold*>* CollisionManager::_collisions;


void CollisionManager::Initialise(ICollisionDetector* detector, ICollisionResponder* responder) {
	_collisionDetector = detector;
	_collisionResponder = responder;
	_collisions = new vector<ICollisionManifold*>();
	ComponentManager::GenerateIDByString("collider");
}

void CollisionManager::DetectCollision(Entity* entity1, Entity* entity2) {
	ICollisionManifold* manifold = _collisionDetector->CollisionCheck(entity1, entity2);
	if (manifold != NULL) {
		_collisions->push_back(manifold);
	}
}

void CollisionManager::DetectCollisions(vector<Entity*>* entityList) {
	vector<ICollisionManifold*>* manifoldList = _collisionDetector->CollisionCheck(entityList);
	if (manifoldList != NULL) {
		if (manifoldList->size() > 0) {
			// Merge the collision lists
			_collisions->insert(
				_collisions->end(),
				manifoldList->begin(),
				manifoldList->end()
			);

			// Empty old list
			manifoldList->clear();
		}

		delete manifoldList;
	}
}

void CollisionManager::HandleCollisions() {
	_collisionResponder->HandleCollisions(_collisions);

	for (ICollisionManifold* manifold : (*_collisions)) {
		delete manifold;
	}
	_collisions->clear();
}

void CollisionManager::ClearCollisions() {
	for (ICollisionManifold* manifold : (*_collisions)) {
		delete manifold;
	}
	_collisions->clear();
}

void CollisionManager::End() {
	delete _collisionDetector;
	delete _collisionResponder;
	ClearCollisions();
	delete _collisions;
}