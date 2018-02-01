#include "ShaderCompiler.h"

ShaderCompiler* ShaderCompiler::shadercompiler = nullptr;

bool checkStatus(
	GLuint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{
	GLint status;
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE)
	{
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		std::cout << buffer << std::endl;
		delete[] buffer;
		return false;
	}
	return true;
}

Pass * ShaderCompiler::Compile(char * VshaderFileName, char * FshaderFileName)
{
	if (!VshaderFileName || !FshaderFileName)
		return nullptr;
	else {
		GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
		GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

		const GLchar* adapter[1];
		std::string temp = ReadShaderCode(VshaderFileName);
		adapter[0] = temp.c_str();
		glShaderSource(VertexShaderID, 1, adapter, 0);
		temp = ReadShaderCode(FshaderFileName);
		adapter[0] = temp.c_str();
		glShaderSource(FragmentShaderID, 1, adapter, 0);

		glCompileShader(VertexShaderID);
		glCompileShader(FragmentShaderID);

		if (!checkShaderStatus(VertexShaderID) || !checkShaderStatus(FragmentShaderID)) {
			printf("shader compile failed");
			return nullptr;
		}

		GLuint programID = glCreateProgram();
		glAttachShader(programID, VertexShaderID);
		glAttachShader(programID, FragmentShaderID);
		glLinkProgram(programID);

		if (!checkProgramStatus(programID)) {
			printf("program compile failed");
			return nullptr;
		}
		else {
			Pass* p = new Pass(VshaderFileName, FshaderFileName);
			p->setVshaderID(VertexShaderID);
			p->setFshaderID(FragmentShaderID);
			p->setProgramID(programID);
			return p;
		}

		return nullptr;
	}
}

bool ShaderCompiler::ReCompile_Pass(Pass * p)
{
	if (!p)
		return false;
	else {
		const GLchar* adapter[1];
		std::string temp = ReadShaderCode(p->getVshaderFileName());
		adapter[0] = temp.c_str();
		glShaderSource(p->getVshaderID(), 1, adapter, 0);
		temp = ReadShaderCode(p->getFshaderFileName());
		adapter[0] = temp.c_str();
		glShaderSource(p->getFshaderID(), 1, adapter, 0);

		glCompileShader(p->getVshaderID());
		glCompileShader(p->getFshaderID());

		if (!checkShaderStatus(p->getVshaderID()) || !checkShaderStatus(p->getFshaderID())) {
			printf("shader compile failed");
			return false;
		}

		glAttachShader(p->getProgramID(), p->getVshaderID());
		glAttachShader(p->getProgramID(), p->getFshaderID());
		glLinkProgram(p->getProgramID());

		if (!checkProgramStatus(p->getProgramID())) {
			printf("program compile failed");
			return false;
		}

		return true;
	}
}

bool ShaderCompiler::checkShaderStatus(GLuint shaderID)
{
	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool ShaderCompiler::checkProgramStatus(GLuint programID)
{
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);
}

std::string ShaderCompiler::ReadShaderCode(const char* fileName)
{
	std::ifstream meInput(fileName);
	if (!meInput.good())
	{
		std::cout << "File failed to load..." << fileName;
		exit(1);
	}
	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>());
}
