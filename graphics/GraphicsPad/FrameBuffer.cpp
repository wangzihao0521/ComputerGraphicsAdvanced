#include "FrameBuffer.h"
GLint FrameBuffer::count = 0;

void FrameBuffer::init_ColorTexture(GLsizei width, GLsizei height)
{
	glActiveTexture(GL_TEXTURE31 - count);
	Texture * tex = TextureManager::getInstance()->CreateEmptyTexture();
	glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	ColorTexture = tex;
}

void FrameBuffer::init_DepthTexture(GLsizei width, GLsizei height)
{
	glActiveTexture(GL_TEXTURE30 - count);
	Texture * tex = TextureManager::getInstance()->CreateEmptyTexture();
	glBindTexture(GL_TEXTURE_2D, tex->getTextureID());
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	DepthTexture = tex;
}

void FrameBuffer::init(GLsizei width, GLsizei height)
{
	glGenFramebuffers(1, &id);
	glBindBuffer(GL_FRAMEBUFFER, id);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glDrawBuffer(GL_DEPTH_ATTACHMENT);
	init_ColorTexture(width, height);
	init_DepthTexture(width, height);
	count += 1;

}