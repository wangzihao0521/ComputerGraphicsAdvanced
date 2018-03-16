#pragma once
#include <string>
#include <gl\glew.h>

class Pass {
protected:
	char* VshaderFileName;
	char* FshaderFileName;
	GLuint programID;
	GLuint VshaderID;
	GLuint FshaderID;
public:
	Pass(char* V_Shader_File_Name = nullptr, char* F_Shader_File_Name = nullptr) :
		VshaderFileName(V_Shader_File_Name), FshaderFileName(F_Shader_File_Name) {}
	~Pass() 
	{
		if (VshaderFileName)
		{
			VshaderFileName = nullptr;
		}
		if (FshaderFileName)
		{
			FshaderFileName = nullptr;
		}
	}

	GLuint getProgramID() const { return programID; }
	GLuint getVshaderID() const { return VshaderID; }
	GLuint getFshaderID() const { return FshaderID; }
	char* getVshaderFileName() const { return VshaderFileName; }
	char* getFshaderFileName() const { return FshaderFileName; }
	void setVshaderID(GLuint vs_id) { VshaderID = vs_id; }
	void setFshaderID(GLuint fs_id) { FshaderID = fs_id; }
	void setProgramID(GLuint pro_id) { programID = pro_id; }

	void ExecutePass();
};
