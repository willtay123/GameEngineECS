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
	vector<Vertex>* vertices = geometry->GetVertices();
	vector<TriangleIndices>* triangles = geometry->GetTriangles();
	
	vector<float> tempData;

	for (int i = 0; i < (int)(vertices->size()); i++) {

		// Add indexed values to the data array
		tempData.push_back((*vertices)[i].pos.x);
		tempData.push_back((*vertices)[i].pos.y);
		tempData.push_back((*vertices)[i].pos.z);

		tempData.push_back((*vertices)[i].uv.x);
		tempData.push_back((*vertices)[i].uv.y);
		
		tempData.push_back((*vertices)[i].normal.x);
		tempData.push_back((*vertices)[i].normal.y);
		tempData.push_back((*vertices)[i].normal.z);
	}

	vector<unsigned short> temp_indices;

	for (int i = 0; i < triangles->size(); i++) {
		TriangleIndices triangle = (*triangles)[i];

		temp_indices.push_back(triangle.vertices[0]);
		temp_indices.push_back(triangle.vertices[1]);
		temp_indices.push_back(triangle.vertices[2]);
	}

	// Turn temp data into array format
	_dataSize = tempData.size();
	_data = new float[_dataSize];
	for (int i = 0; i < _dataSize; i += 1) {
		_data[i] = tempData[i];
	}

	_triangleCount = triangles->size();

	_indicesSize = temp_indices.size();
	_indices = new unsigned short[_indicesSize];
	for (int i = 0; i < _indicesSize; i++) {
		_indices[i] = temp_indices[i];
	}


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