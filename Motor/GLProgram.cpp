#include "GLProgram.h"
#include <fstream>
#include <vector>
void GLProgram::compileShader(const string& shaderPath, GLuint id)
{
	string fileContent = "";
	string line = "";
	
	ifstream shaderFile(shaderPath);
	if (shaderFile.fail()) {
		//TO DO ERROR
	}
	while (getline(shaderFile, line)) 
	{
		fileContent += line + "\n";
	}
	shaderFile.close();
	const char* contents = fileContent.c_str();
	glShaderSource(id, 1, &contents, nullptr);
	glCompileShader(id);
	GLint isCompiled = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled==GL_FALSE) 
	{
		GLint maxLenght = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLenght);
		std::vector<GLchar> errorLog(maxLenght);
		glGetShaderInfoLog(id, maxLenght, &maxLenght, &errorLog[0]);
		glDeleteShader(id);
		return ;
	}
}

GLProgram::GLProgram(): programID(0),vertexShaderID(0),fragmentShaderID(0)
{
}

GLProgram::~GLProgram()
{
}

void GLProgram::compileShader(const string& vertexShaderFilePath, const string& fragmentShaderFilePath)
{
	programID = glCreateProgram();
	vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (vertexShaderID == 0) 
	{
		// TODO SHOW ERROR
	}
	fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (fragmentShaderID == 0)
	{
		//TODO SHOW ERROR
	}
	compileShader(vertexShaderFilePath, vertexShaderID);
	compileShader(fragmentShaderFilePath, fragmentShaderID);
}

void GLProgram::linkShader()
{
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
	
	GLint islinked = 0;
	glGetProgramiv(programID,GL_LINK_STATUS,(int*)&islinked);
	if (islinked == GL_FALSE) 
	{
		GLint maxLenght = 0;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLenght);
		std::vector<GLchar> infoLog(maxLenght);
		glGetProgramInfoLog(programID, maxLenght, &maxLenght, &infoLog[0]);
		glDeleteProgram(programID);
		glDeleteShader(vertexShaderID);
		glDeleteShader(fragmentShaderID);
		return;
	}
	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
}
