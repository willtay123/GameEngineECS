#pragma once
#include "Interfaces/IShader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <strstream>
#include <sstream>
#include <vector>

#include "Externals/Buffers/GLBufferID.h"

class ShaderGLSL : public IShader {
private:
	GLuint _pgmID;
	GLuint _vsID;
	GLuint _fsID;
	GLuint _uniform_MVP;

public:
	ShaderGLSL();
	~ShaderGLSL();

	bool Initialise();
	IBufferID* LoadShader(const char* filepath, ShaderType shaderType);
	void LinkShaders(int pgmID, int vsID, int fsID);

	GLuint GetPgmID();
	GLuint GetVsID();
	GLuint GetFsID();
	GLuint GetMvpID();

	void Unload();
};