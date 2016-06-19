#include "KFrameBufferObject.h"
#include <iostream>

KFrameBufferObject::KFrameBufferObject()
{
	
}

bool KFrameBufferObject::init()
{
	bool returnValue = false;
	glGenFramebuffers(1, &id_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, id_fbo);
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture, 0);
	//glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture, 0);
	glDrawBuffer(GL_NONE);
	glReadBuffer(GL_NONE);
	//glDepthMask(GL_FALSE);
	GLenum status;
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	char* c ="";
	if (status == GL_FRAMEBUFFER_COMPLETE) c = "GL_FRAMEBUFFER_COMPLETE";
	if (status == GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT) c = "GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT ";
	if (status == GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER) c = "GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER";
	if (status == GL_FRAMEBUFFER_UNSUPPORTED) c = "GL_FRAMEBUFFER_UNSUPPORTED";
	if (status == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE) c = "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
	if (status == GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE) c = "GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE";
	if (status == GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS) c = "GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS";
	if (status == GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT) {
		c = "GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT";
		returnValue = true;
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return returnValue;
}

void KFrameBufferObject::set_colorbuffer(int width, int height)
{
	isColorOn = true;
	this->color_width = width;
	this->color_height = height;

	glGenTextures(1, &id_texture_color);
	glBindTexture(GL_TEXTURE_2D, id_texture_color);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, id_fbo);
	glDrawBuffer(GL_COLOR_ATTACHMENT0);
	glReadBuffer(GL_COLOR_ATTACHMENT0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, id_texture_color, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void KFrameBufferObject::set_depthbuffer(int width, int height)
{
	this->depth_width = width;
	this->depth_height = height;

	glGenTextures(1, &id_texture_depth);
	glBindTexture(GL_TEXTURE_2D, id_texture_depth);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT16, width, height, 0,GL_DEPTH_COMPONENT, GL_FLOAT, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, id_fbo);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, id_texture_depth, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

int KFrameBufferObject::viewport_width()
{
	return (isColorOn)? color_width: depth_width;
}

int KFrameBufferObject::viewport_height()
{
	return (isColorOn) ? color_height : depth_height;
}
