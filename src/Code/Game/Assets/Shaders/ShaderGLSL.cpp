#include "ShaderGLSL.h"




ShaderGLSL::ShaderGLSL() {

}

ShaderGLSL::~ShaderGLSL() {
	Unload();
}

bool ShaderGLSL::Initialise() {
	int pgmID = glCreateProgram();

	GLBufferID* vertShaderID = static_cast<GLBufferID*>(LoadShader("Assets/Shaders/basic.v", VertexShader));
	GLBufferID* fragShaderID = static_cast<GLBufferID*>(LoadShader("Assets/Shaders/basic.f", FragmentShader));
	LinkShaders(pgmID, vertShaderID->GetID(), fragShaderID->GetID());
	delete vertShaderID;
	delete fragShaderID;

	glUseProgram(pgmID);
	_pgmID = pgmID;
	return true;
}

IBufferID* ShaderGLSL::LoadShader(const char* filepath, ShaderType shaderType) {

	int glShaderType = 0;
	if (shaderType == VertexShader)
		glShaderType = GL_VERTEX_SHADER;
	if (shaderType == FragmentShader)
		glShaderType = GL_FRAGMENT_SHADER;
	
	GLuint shaderID = glCreateShader(glShaderType);

	// Read the shader code from the file
	std::string shaderCode;
	std::ifstream shaderStream(filepath, std::ios::in);
	if (shaderStream.is_open()) {
		std::stringstream sstr;
		sstr << shaderStream.rdbuf();
		shaderCode = sstr.str();
		shaderStream.close();
	}
	else {
		std::cout << "Impossible to open " << filepath << ". Are you in the right directory?" << std::endl;
		getchar();
		shaderID = 0;
	}

	GLint result = GL_FALSE;
	int infoLogLength;

	// Compile Vertex Shader
	std::cout << "Compiling shader : " << filepath << std::endl;
	char const * shaderSourcePointer = shaderCode.c_str();
	glShaderSource(shaderID, 1, &shaderSourcePointer, NULL);
	glCompileShader(shaderID);

	// Check Vertex Shader
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> shaderErrorMessage(infoLogLength + 1);
		glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
		std::cout << "ERROR: " << &shaderErrorMessage[0] << std::endl;
		shaderID = 0;
	}

	GLBufferID* bufferID = new GLBufferID(shaderID);
	return bufferID;
}

void ShaderGLSL::LinkShaders(int pgmID, int vsID, int fsID) {
	GLint result;
	int infoLogLength;

	// Link the program
	std::cout << "linking shaders..." << std::endl;

	glAttachShader(pgmID, vsID);
	glAttachShader(pgmID, fsID);
	glLinkProgram(pgmID);

	// Check the program
	glGetProgramiv(pgmID, GL_LINK_STATUS, &result);
	glGetProgramiv(pgmID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0) {
		std::vector<char> ProgramErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(pgmID, infoLogLength, NULL, &ProgramErrorMessage[0]);
		std::cout << "ERROR: " << &ProgramErrorMessage[0] << std::endl;
	}

	_pgmID = pgmID;
	_vsID = vsID;
	_fsID = fsID;

	_uniform_MVP = glGetUniformLocation(_pgmID, "MVP");

	std::cout << "shaders  linked" << std::endl << std::endl;
}

GLuint ShaderGLSL::GetPgmID() {
	return _pgmID;
}

GLuint ShaderGLSL::GetVsID() {
	return _vsID;
}

GLuint ShaderGLSL::GetFsID() {
	return _fsID;
}

GLuint ShaderGLSL::GetMvpID() {
	return _uniform_MVP;
}

void ShaderGLSL::Unload() {
	glDetachShader(_pgmID, _vsID);
	glDetachShader(_pgmID, _fsID);
	glDeleteShader(_vsID);
	glDeleteShader(_fsID);
	glDeleteProgram(_pgmID);
}