#include "OpenGLModel.h"


OpenGLModel::OpenGLModel() :
	_DBO_Handle(0),
	_IBO_Handle(0)
{

}

OpenGLModel::OpenGLModel(std::shared_ptr<Geometry> geometry) :
	_DBO_Handle(0),
	_IBO_Handle(0)
{
	GenerateBuffers(geometry);
}

OpenGLModel::OpenGLModel(const OpenGLModel& rhs) :
	_DBO_Handle(rhs._DBO_Handle),
	_IBO_Handle(rhs._IBO_Handle),
	_dataSize(rhs._dataSize),
	_indicesSize(rhs._indicesSize),
	_triangleCount(rhs._triangleCount) {
	// Copy Data
	_data = new float[_dataSize];
	for (int i = 0; i < _dataSize; i += 1) {
		_data[i] = rhs._data[i];
	}

	// Copy Indices
	_indices = new unsigned short[_indicesSize];
	for (int i = 0; i < _indicesSize; i += 1) {
		_indices[i] = rhs._indices[i];
	}
}

OpenGLModel::~OpenGLModel() {
	
}

OpenGLModel& OpenGLModel::operator=(const OpenGLModel& rhs) {
	if (this != &rhs) {
		_DBO_Handle = rhs._DBO_Handle;
		_IBO_Handle = rhs._IBO_Handle;
		_dataSize = rhs._dataSize;
		_indicesSize = rhs._indicesSize;
		_triangleCount = rhs._triangleCount;

		// Copy Data
		_data = new float[_dataSize];
		for (int i = 0; i < _dataSize; i += 1) {
			_data[i] = rhs._data[i];
		}

		// Copy Indices
		_indices = new unsigned short[_indicesSize];
		for (int i = 0; i < _indicesSize; i += 1) {
			_indices[i] = rhs._indices[i];
		}
	}
	return *this;
}

void OpenGLModel::GenerateBuffers(std::shared_ptr<Geometry> geometry) {
	// Take data from geometry
	vector<vec3>* vertices = geometry->GetVertices();
	vector<vec2>* uvs = geometry->GetUVs();
	vector<vec3>* normals = geometry->GetNormals();
	vector<TriangleIndices>* triangles = geometry->GetTriangles();
	
	map<PointData, unsigned short> uniquePoints;
	unsigned short indexCount = 0;
	vector<float> tempData;
	vector<unsigned short> tempIndices;

	// --Turn data into GL format
	for (int i = 0; i < (int)(triangles->size()); i += 1) {
		TriangleIndices triangle = (*triangles)[i];
		
		// For each indices set in the triangle
		for (int j = 0; j < 3; j += 1) {
			PointData point = {
				triangle.vertices[j],
				triangle.uvs[j],
				triangle.normals[j]
			};

			unsigned short index;

			// Look in map for matching point
			auto it = uniquePoints.find(point);
			
			// If current point is similar to one seen before
			if (it != uniquePoints.end()) {
				// Match

				// Use index value from matching map
				index = it->second;
			} else {
				// No match

				// Add current point to map
				uniquePoints[point] = indexCount;
				index = indexCount;

				// Add indexed values to the data array
				tempData.push_back((*vertices)[point.vertIndex].x);
				tempData.push_back((*vertices)[point.vertIndex].y);
				tempData.push_back((*vertices)[point.vertIndex].z);
				
				tempData.push_back((*uvs)[point.uvIndex].x);
				tempData.push_back((*uvs)[point.uvIndex].y);
				
				tempData.push_back((*normals)[point.normalIndex].x);
				tempData.push_back((*normals)[point.normalIndex].y);
				tempData.push_back((*normals)[point.normalIndex].z);

				// Increment indexCount
				indexCount += 1;
			}

			// Add the new-format index to index list
			tempIndices.push_back(index);
		}
	}

	// Turn temp data into array format
	_dataSize = tempData.size();
	_data = new float[_dataSize];
	for (int i = 0; i < _dataSize; i += 1) {
		_data[i] = tempData[i];
	}

	_indicesSize = tempIndices.size();
	_indices = new unsigned short[_indicesSize];
	for (int i = 0; i < _indicesSize; i += 1) {
		_indices[i] = tempIndices[i];
	}

	_triangleCount = _indicesSize;

	// --Generate buffers

	// Data buffer
	glGenBuffers(1, &_DBO_Handle);
	glBindBuffer(GL_ARRAY_BUFFER, _DBO_Handle);
	glBufferData(GL_ARRAY_BUFFER, _dataSize * sizeof(float), &_data[0], GL_STATIC_DRAW);
	
	// Index buffer
	glGenBuffers(1, &_IBO_Handle);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _IBO_Handle);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indicesSize * sizeof(unsigned short), &_indices[0], GL_STATIC_DRAW);
}

const GLuint OpenGLModel::GetDBOHandle() const {
	return _DBO_Handle;
}

const GLuint OpenGLModel::GetIBOHandle() const {
	return _IBO_Handle;
}

const int OpenGLModel::GetTriangleCount() const {
	return _triangleCount;
}