#include "GLBufferID.h"



GLBufferID::GLBufferID(int id) {
	_id = id;
}

GLBufferID::~GLBufferID() {

}

const char* GLBufferID::GetName() {
	return "GL Buffer";
}

void GLBufferID::SetID(int id) {
	_id = id;
}

int GLBufferID::GetID() {
	return _id;
}