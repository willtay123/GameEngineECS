#pragma once
#include "Interfaces/IResource.h"

#include <vector>
#include <GLM/glm/vec2.hpp>
#include <GLM/glm/vec3.hpp>
#include "DataStructs/Vertex.h"

using std::vector;
using glm::vec2;
using glm::vec3;

namespace EngineECS {
	struct TriangleIndices {
		unsigned short vertices[3];
	};

	class Geometry : public IResource {
	private:
		vector<Vertex> _vertices;
		vector<TriangleIndices> _faces;

	public:
		Geometry();
		Geometry(vector<Vertex>& vertices, vector<TriangleIndices>& faces);
		Geometry(const Geometry& rhs);
		~Geometry();
		Geometry& operator=(const Geometry& rhs);

		vector<Vertex>* GetVertices();
		vector<TriangleIndices>* GetTriangles();

		int GetVertexSize();
		int GetUVSize();
		int GetNormalSize();
		int GetTriangleCount();
	};
}