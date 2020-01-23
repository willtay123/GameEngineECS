#pragma once
#include "Interfaces/IResource.h"

#include <vector>
#include <glm\vec2.hpp>
#include <glm\vec3.hpp>

using std::vector;
using glm::vec2;
using glm::vec3;

struct TriangleIndices {
	unsigned short vertices[3];
	unsigned short uvs[3];
	unsigned short normals[3];
};

class Geometry : public IResource {
private:
	vector<vec3> _vertices;
	vector<vec2> _uvs;
	vector<vec3> _normals;
	vector<TriangleIndices> _triangles;

	
	int _verticesSize;
	int _uvSize;
	int _normalsSize;
	int _triangleCount;

public:
	Geometry();
	Geometry(vector<vec3> vertices, vector<vec2> uvs, vector<vec3> normals, vector<TriangleIndices> triangles);
	Geometry(const Geometry& rhs);
	~Geometry();
	Geometry& operator=(const Geometry& rhs);

	vector<vec3>* GetVertices();
	vector<vec2>* GetUVs();
	vector<vec3>* GetNormals();
	vector<TriangleIndices>* GetTriangles();

	int GetVertexSize();
	int GetUVSize();
	int GetNormalSize();
	int GetTriangleCount();
};