#pragma once
#include "Interfaces/IComponent.h"

#include <string>

using std::string;

class ComponentCollider : public IComponent {
private:

protected:
	ComponentCollider();
	ComponentCollider(bool enabled);

	bool _enabled;
	string _colliderType;

public:
	virtual IComponent* Clone();

	virtual int ComponentType() const;
	virtual void Message(IMessage* message);

	virtual const string& GetColliderType();
	virtual bool IsEnabled();
	virtual void SetEnabled(bool enabled);
};