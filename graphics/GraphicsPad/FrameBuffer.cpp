#include "FrameBuffer.h"
GLint FrameBuffer::count = 0;

void FrameBuffer::init_ColorTexture(GLsizei width, GLsizei height)
{
	glActiveTexture(GL_TEXTURE30 - count*2);
	Texture * tex = TextureManager::getInstance()->CreateEmptyTexture();
	glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	ColorTexture = tex;
}

void FrameBuffer::init_DepthTexture(GLsizei width, GLsizei height)
{
	glActiveTexture(GL_TEXTURE29 - count*2);
	Texture * tex = TextureManager::getInstance()->CreateEmptyTexture();
	glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	DepthTexture = tex;
}

void FrameBuffer::init_SelectionColorTexture()
{
	glActiveTexture(GL_TEXTURE30 - count*2);
	Texture * tex = TextureManager::getInstance()->CreateEmptyTexture();
	glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_R32I, 1, 1, 0, GL_RED_INTEGER, GL_INT, 0);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	ColorTexture = tex;
}

void FrameBuffer::init(GLsizei width, GLsizei height)
{
	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	init_ColorTexture(width, height);
	init_DepthTexture(width, height);
	count += 1;
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ColorTexture->getTextureID(), 0);
	glFramebufferTexture2D(GL_DRAW_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, DepthTexture->getTextureID(), 0);
}

void FrameBuffer::SelectionInit()
{
	glGenFramebuffers(1, &id);
	glBindFramebuffer(GL_FRAMEBUFFER, id);
	init_SelectionColorTexture();
	init_DepthTexture(1, 1);
	count += 1;
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,ColorTexture->getTextureID(), 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D,DepthTexture->getTextureID(), 0);
}
