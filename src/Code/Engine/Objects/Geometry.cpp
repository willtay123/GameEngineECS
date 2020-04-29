#include "Geometry.h"

using namespace EngineECS;

Geometry::Geometry() :
	_vertices(0),
	_faces(0) {

}

Geometry::Geometry(vector<Vertex>& vertices, vector<TriangleIndices>& faces) :
	_vertices(vertices),
	_faces(faces) {
}

Geometry::Geometry(const Geometry& rhs) :
	_vertices(rhs._vertices),
	_faces(rhs._faces) {

}

Geometry::~Geometry() {
}

Geometry& Geometry::operator=(const Geometry& rhs) {
	if (this != &rhs) {
		_vertices = rhs._vertices;
		_faces = rhs._faces;
	}
	return *this;
}

vector<Vertex>* Geometry::GetVertices() {
	return &_vertices;
}

vector<TriangleIndices>* Geometry::GetTriangles() {
	return &_faces;
}


int Geometry::GetVertexSize() {
	return _vertices.size();
}

int Geometry::GetUVSize() {
	return _vertices.size();
}

int Geometry::GetNormalSize() {
	return _vertices.size();
}

int Geometry::GetTriangleCount() {
	return _faces.size();
}