#pragma once

#include "Interfaces/IComponent.h"
#include "Interfaces/IMessage.h"

#include <vector>
#include <string>

using namespace std;

namespace EngineECS {
	class Entity {
	private:
		string _id;
		vector<IComponent*>* _components;
		bool _enabled;

	public:
		Entity();
		Entity(const char* id);
		Entity(string* id);
		Entity(const Entity& rhs);
		~Entity();
		Entity& operator= (const Entity& rhs);

		const string* GetID() const;
		void SetID(string value);


		void AddComponent(IComponent* component);
		void RemoveComponent(int id);

		bool HasComponent(int id);

		const vector<IComponent*>* GetComponents() const;
		vector<IComponent*>* GetComponentsEditable();

		const IComponent* GetComponent(int id) const;
		const IComponent* GetComponent(string id) const;
		IComponent* GetComponentEditable(int id);

		void Message(IMessage* message);

		bool GetComponentIndex(int id, int* outIndex);
	};
}