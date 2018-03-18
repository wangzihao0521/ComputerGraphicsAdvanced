#include "FrameBuffer.h"
GLint FrameBuffer::count = 0;

void FrameBuffer::init_ColorTexture(GLsizei width, GLsizei height, bool comparison)
{
	glActiveTexture(GL_TEXTURE30 - count);
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

	tex->setTexUnitId(30 - count);
	ColorTexture = tex;
	count += 1;
}

void FrameBuffer::init_DepthTexture(GLsizei width, GLsizei height, bool comparison)
{
	glActiveTexture(GL_TEXTURE29 - count);
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

	tex->setTexUnitId(30 - count);
	DepthTexture = tex;
	count += 1;
}

void FrameBuffer::init_DepthTexture(GLsizei width, GLsizei height, bool comparison, GLint TexUnitID)
{
	
	glActiveTexture(GL_TEXTURE0 + TexUnitID-1);
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

	tex->setTexUnitId(TexUnitID-1);
	DepthTexture = tex;
}

void FrameBuffer::init_SelectionColorTexture()
{
	glActiveTexture(GL_TEXTURE30 - count);
	Texture * tex = TextureManager::getInstance()->CreateEmptyTexture();
	glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, 1, 1, 0, GL_RED_INTEGER, GL_INT, 0);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	tex->setTexUnitId(30 - count);
	ColorTexture = tex;
	count += 1;
}

void FrameBuffer::init_DepthTexture_3D(GLsizei width, GLsizei height, bool comparison)
{
	glActiveTexture(GL_TEXTURE30 - count);
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
	tex->setTexUnitId(30 - count);
	DepthTexture_3D = tex;
	count += 1;
}

void FrameBuffer::init_DepthTexture_3D(GLsizei width, GLsizei height, bool comparison, GLint TexUnitID)
{
	glActiveTexture(GL_TEXTURE0 + TexUnitID+1);
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
	tex->setTexUnitId(TexUnitID + 1);
	DepthTexture_3D = tex;
}

void FrameBuffer::Delete_ColorTex()
{
	TextureManager::getInstance()->DeleteTexture(ColorTexture);
	ColorTexture = nullptr;
}

void FrameBuffer::Delete_DepthTex_3D()
{
	TextureManager::getInstance()->DeleteTexture3D(DepthTexture_3D);
	DepthTexture_3D = nullptr;
}

void FrameBuffer::Delete_DepthTex()
{
	TextureManager::getInstance()->DeleteTexture(DepthTexture);
	DepthTexture = nullptr;
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
	count += 1;
}

void FrameBuffer::PointLight_Shadow_Change(GLsizei width, GLsizei height, GLint TexUnitId)
{
	Delete_DepthTex();
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	init_DepthTexture_3D(width, height, true, TexUnitId);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, DepthTexture_3D->getTextureID(), 0);
}

void FrameBuffer::DirectLight_Shadow_Change(GLsizei width, GLsizei height, GLint TexUnitId)
{
	Delete_DepthTex_3D();
//	glDeleteFramebuffers(1, &id);
//	id = 0;
//	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	init_DepthTexture(width, height, true, TexUnitId);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthTexture->getTextureID(), 0);
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



