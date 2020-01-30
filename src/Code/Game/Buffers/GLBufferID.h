#pragma once
#include "Interfaces/IBufferID.h"

using namespace EngineECS;

class GLBufferID : public IBufferID {
private:
	int _id;

public:
	GLBufferID(int id);
	~GLBufferID();

	const char* GetName();

	void SetID(int id);
	int GetID();
};