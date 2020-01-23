#pragma once

#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include "Interfaces/IModel.h"
#include "Objects/Geometry.h"
#include <map>

using std::map;
using std::make_pair;

struct PointData {
	unsigned short vertIndex;
	unsigned short uvIndex;
	unsigned short normalIndex;
	bool operator<(const PointData that) const {
		return memcmp((void*)this, (void*)&that, sizeof(PointData))>0;
	}
};

class OpenGLModel : public IModel {
private:
	GLuint _DBO_Handle;
	GLuint _IBO_Handle;
	
	int _dataSize;
	int _indicesSize;
	int _triangleCount;

	float* _data;
	unsigned short* _indices;


public:
	OpenGLModel();
	OpenGLModel(Geometry* geomtry);
	OpenGLModel(const OpenGLModel& rhs);
	~OpenGLModel();
	OpenGLModel& operator=(const OpenGLModel& rhs);

	void GenerateBuffers(Geometry* geometry);

	const GLuint GetDBOHandle() const;
	const GLuint GetIBOHandle() const;

	const int GetTriangleCount() const;
};