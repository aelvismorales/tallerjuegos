#pragma once
#include <GL/glew.h>
#include <string>

using namespace std;

class GLProgram
{
private:
	GLuint programID;
	GLuint fragmentShaderID;
	GLuint vertexShaderID;
	void compileShader(const string& shaderPath, GLuint id);
public:
	GLProgram();
	~GLProgram();
	void compileShader(const string& vertexShaderFilePath, const string& fragmentShaderFilePath);
	void linkShader();
};

