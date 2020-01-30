#include "Geometry.h"


namespace EngineECS {
	Geometry::Geometry() :
		_vertices(0),
		_uvs(0),
		_normals(0),
		_triangles(0),
		_verticesSize(0),
		_uvSize(0),
		_normalsSize(0),
		_triangleCount(0) {

	}

	Geometry::Geometry(vector<vec3> vertices, vector<vec2> uvs, vector<vec3> normals, vector<TriangleIndices> triangles) :
		_vertices(vertices),
		_uvs(uvs),
		_normals(normals),
		_triangles(triangles)
	{

		// Vertices
		_verticesSize = vertices.size();

		// TexCoords
		_uvSize = uvs.size();

		// Normals
		_normalsSize = normals.size();

		// Triangles
		_triangleCount = triangles.size();
	}

	Geometry::Geometry(const Geometry& rhs) :
		_vertices(rhs._vertices),
		_uvs(rhs._uvs),
		_normals(rhs._normals),
		_triangles(rhs._triangles),
		_verticesSize(rhs._verticesSize),
		_uvSize(rhs._uvSize),
		_normalsSize(rhs._normalsSize),
		_triangleCount(rhs._triangleCount) {

	}

	Geometry::~Geometry() {
	}

	Geometry& Geometry::operator=(const Geometry& rhs) {
		if (this != &rhs) {
			_vertices = rhs._vertices;
			_uvs = rhs._uvs;
			_normals = rhs._normals;
			_triangles = rhs._triangles;

			_verticesSize = rhs._verticesSize;
			_uvSize = rhs._uvSize;
			_normalsSize = rhs._normalsSize;
			_triangleCount = rhs._triangleCount;
		}
		return *this;
	}

	vector<vec3>* Geometry::GetVertices() {
		return &_vertices;
	}

	vector<vec2>* Geometry::GetUVs() {
		return &_uvs;
	}

	vector<vec3>* Geometry::GetNormals() {
		return &_normals;
	}

	vector<TriangleIndices>* Geometry::GetTriangles() {
		return &_triangles;
	}


	int Geometry::GetVertexSize() {
		return _verticesSize;
	}

	int Geometry::GetUVSize() {
		return _uvSize;
	}

	int Geometry::GetNormalSize() {
		return _normalsSize;
	}

	int Geometry::GetTriangleCount() {
		return _triangleCount;
	}
}