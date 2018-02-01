#pragma once
#include <Pass.h>
#include <fstream>
#include <iostream>

class ShaderCompiler {

public :
	ShaderCompiler() {}

	static ShaderCompiler* getInstance() 
	{ 
		if (shadercompiler)
			return shadercompiler;
		else {
			shadercompiler = new ShaderCompiler();
			return shadercompiler;
		}
	}

	Pass * Compile(char * VshaderFileName, char * FshaderFileName);
	bool ReCompile_Pass(Pass* p);

protected:
	static ShaderCompiler* shadercompiler;

private:
	bool checkShaderStatus(GLuint shaderID);
	bool checkProgramStatus(GLuint programID);
	std::string ReadShaderCode(const char* fileName);
};
