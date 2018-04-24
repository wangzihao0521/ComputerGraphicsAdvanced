#pragma once
#include <string>
#include <gl\glew.h>

class Pass {
protected:
	std::string VshaderFileName;
	std::string FshaderFileName;
	GLuint programID;
	GLuint VshaderID;
	GLuint FshaderID;
public:
	Pass(std::string V_Shader_File_Name = "", std::string F_Shader_File_Name = "") :
		VshaderFileName(V_Shader_File_Name), FshaderFileName(F_Shader_File_Name) {}
	~Pass() 
	{
	}

	GLuint getProgramID() const { return programID; }
	GLuint getVshaderID() const { return VshaderID; }
	GLuint getFshaderID() const { return FshaderID; }
	const char* getVshaderFileName() const { return VshaderFileName.c_str(); }
	const char* getFshaderFileName() const { return FshaderFileName.c_str(); }
	void setVshaderID(GLuint vs_id) { VshaderID = vs_id; }
	void setFshaderID(GLuint fs_id) { FshaderID = fs_id; }
	void setProgramID(GLuint pro_id) { programID = pro_id; }
	void setVshaderFileName(std::string filename) 
	{ 
		VshaderFileName = filename; 
	}
	void setFshaderFileName(std::string filename)
	{ 
		FshaderFileName = filename; 
	}

	void ExecutePass();
};
