#include "FrameBuffer.h"
GLint FrameBuffer::count = 0;
std::vector<GLint> FrameBuffer::FreeTexUnit{};

void FrameBuffer::init_ColorTexture(GLsizei width, GLsizei height, bool comparison)
{
	GLint Valid_TexUnit = fetchValidTexUnit();
	glActiveTexture(GL_TEXTURE0+Valid_TexUnit);
	
	Texture * tex = TextureManager::getInstance()->CreateEmptyTexture();
	glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (comparison)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	}

	tex->setTexUnitId(Valid_TexUnit);
	ColorTexture = tex;
}

void FrameBuffer::init_DepthTexture(GLsizei width, GLsizei height, bool comparison)
{
	GLint Valid_TexUnit = fetchValidTexUnit();
	glActiveTexture(GL_TEXTURE0 + Valid_TexUnit);
	Texture * tex = TextureManager::getInstance()->CreateEmptyTexture();
	glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (comparison)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	}

	tex->setTexUnitId(Valid_TexUnit);
	DepthTexture = tex;
}

void FrameBuffer::init_DepthTexture(GLsizei width, GLsizei height, bool comparison, GLint TexUnitID)
{
	GLint Valid_TexUnit = fetchValidTexUnit();
	glActiveTexture(GL_TEXTURE0 + Valid_TexUnit);
	Texture * tex = TextureManager::getInstance()->CreateEmptyTexture();
	glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	if (comparison)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	}

	tex->setTexUnitId(Valid_TexUnit);
	DepthTexture = tex;
}

void FrameBuffer::init_SelectionColorTexture()
{
	GLint Valid_TexUnit = fetchValidTexUnit();
	glActiveTexture(GL_TEXTURE0 + Valid_TexUnit);
	Texture * tex = TextureManager::getInstance()->CreateEmptyTexture();
	glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, 1, 1, 0, GL_RED_INTEGER, GL_INT, 0);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	tex->setTexUnitId(Valid_TexUnit);
	ColorTexture = tex;
}

void FrameBuffer::init_DepthTexture_3D(GLsizei width, GLsizei height, bool comparison)
{
	GLint Valid_TexUnit = fetchValidTexUnit();
	glActiveTexture(GL_TEXTURE0 + Valid_TexUnit);
	Texture3D * tex = TextureManager::getInstance()->CreateEmptyTexture_3D();
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex->getTextureID());
	for (int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}	
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	if (comparison)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	}
	tex->setTexUnitId(Valid_TexUnit);
	DepthTexture_3D = tex;
}

void FrameBuffer::init_DepthTexture_3D(GLsizei width, GLsizei height, bool comparison, GLint TexUnitID)
{
	GLint Valid_TexUnit = fetchValidTexUnit();
	glActiveTexture(GL_TEXTURE0 + Valid_TexUnit);
	Texture3D * tex = TextureManager::getInstance()->CreateEmptyTexture_3D();
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex->getTextureID());
	for (int i = 0; i < 6; ++i)
	{
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	}
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameterf(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	if (comparison)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
	}
	tex->setTexUnitId(Valid_TexUnit);
	DepthTexture_3D = tex;
}

void FrameBuffer::Delete_ColorTex()
{
	FreeTexUnit.push_back(ColorTexture->getTexUnitID());
	TextureManager::getInstance()->DeleteTexture(ColorTexture);
	ColorTexture = nullptr;
}

void FrameBuffer::Delete_DepthTex_3D()
{
	FreeTexUnit.push_back(DepthTexture_3D->getTexUnitID());
	TextureManager::getInstance()->DeleteTexture3D(DepthTexture_3D);
	DepthTexture_3D = nullptr;
}

void FrameBuffer::Delete_DepthTex()
{
	FreeTexUnit.push_back(DepthTexture->getTexUnitID());
	TextureManager::getInstance()->DeleteTexture(DepthTexture);
	DepthTexture = nullptr;
}

GLint FrameBuffer::fetchValidTexUnit()
{
	if (FreeTexUnit.empty())
	{
		count++;
		return 31 - count;
	}
	else
	{
		GLint b = FreeTexUnit.back();
		FreeTexUnit.pop_back();
		return b;
	}
}

GLint FrameBuffer::getEmptyTexUnit()
{
	if (FreeTexUnit.empty())
	{
		return 30 - count;
	}
	else
	{ 
		return FreeTexUnit.back();
	}
}

void FrameBuffer::init(GLsizei width, GLsizei height)
{
	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	init_ColorTexture(width, height,false);
	init_DepthTexture(width, height,false);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorTexture->getTextureID(), 0);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthTexture->getTextureID(), 0);
}

void FrameBuffer::SelectionInit()
{
	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	init_SelectionColorTexture();
	init_DepthTexture(1, 1,false);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,ColorTexture->getTextureID(), 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,DepthTexture->getTextureID(), 0);
}

void FrameBuffer::PointLight_Shadow_Init(GLsizei width, GLsizei height)
{
	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	init_DepthTexture_3D(width, height,true);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthTexture_3D->getTextureID(), 0);
}

void FrameBuffer::DirectLight_Shadow_Init(GLsizei width, GLsizei height)
{
	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	init_DepthTexture(width, height, true);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthTexture->getTextureID(), 0);
}

void FrameBuffer::PointLight_Shadow_Change(GLsizei width, GLsizei height, GLint TexUnitId)
{
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	init_DepthTexture_3D(width, height, true, TexUnitId);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthTexture_3D->getTextureID(), 0);
	Delete_DepthTex();
}

void FrameBuffer::DirectLight_Shadow_Change(GLsizei width, GLsizei height, GLint TexUnitId)
{	
//	glDeleteFramebuffers(1, &id);
//	id = 0;
//	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	init_DepthTexture(width, height, true, TexUnitId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthTexture->getTextureID(), 0);
	Delete_DepthTex_3D();
}

void FrameBuffer::UpdateTexSize(GLsizei width, GLsizei height)
{
	if (ColorTexture)
	{
		glBindTexture(GL_TEXTURE_2D, ColorTexture->getTextureID());
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
	}
	if (DepthTexture)
	{
		glBindTexture(GL_TEXTURE_2D, DepthTexture->getTextureID());
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	}
	if (DepthTexture_3D)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, DepthTexture_3D->getTextureID());
		for (int i = 0; i < 6; ++i)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		}
	}

}



