#pragma once
#include "Interfaces/IShader.h"

#include <GLAD/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <strstream>
#include <sstream>
#include <vector>
#include <Tools/Logger.h>

#include "Buffers/GLBufferID.h"

using namespace EngineECS;

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
	IBufferID* LoadShader(const string& filepath, const ShaderType shaderType);
	void LinkShaders(int pgmID, int vsID, int fsID);

	GLuint GetPgmID();
	GLuint GetVsID();
	GLuint GetFsID();
	GLuint GetMvpID();

	void Unload();
};