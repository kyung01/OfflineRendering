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

bool KFrameBufferObject::init(int width, int height)
{
	if (init()) {
		this->set_colorbuffer(width, height);
		this->set_depthbuffer(width, height);
		return true;
	}
	return false;
}

void KFrameBufferObject::set_colorbuffer(int width, int height)
{
	std::tuple<GLuint, int, int> texture_color;
	isColorOn = true;

	std::get<1>(texture_color) = width;
	std::get<2>(texture_color) = height;


	glGenTextures(1,  &std::get<0>(texture_color)  );
	glBindTexture(GL_TEXTURE_2D, std::get<0>(texture_color));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_FLOAT, 0);
	//glBindTexture(GL_TEXTURE_2D,0);

	glBindFramebuffer(GL_FRAMEBUFFER, id_fbo);
	glDrawBuffer(GL_COLOR_ATTACHMENT0 + ids_texutre_color.size());
	glReadBuffer(GL_COLOR_ATTACHMENT0 + ids_texutre_color.size());
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + ids_texutre_color.size(), GL_TEXTURE_2D, std::get<0>(texture_color), 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	ids_texutre_color.push_back(texture_color);
	//std::cout << "NEW TEXTURE COLOR " << std::get<0>(texture_color) << std::endl;

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


GLuint KFrameBufferObject::get_color(int id)
{
	auto it = ids_texutre_color.begin();
	std::advance(it, id);
	//std::cout << "GET COLOR " << std::get<0>(*it) << std::endl;
	return std::get<0>( *it);
}

GLuint KFrameBufferObject::get_depth()
{
	return id_texture_depth;
}

int KFrameBufferObject::get_color_width(int id)
{

	if (ids_texutre_color.size() == 0) {
		return depth_width;
	}
	auto it = ids_texutre_color.begin();
	std::advance(it, id);
	return std::get<1>(*it);
}

int KFrameBufferObject::get_color_height(int id)
{
	if (ids_texutre_color.size() == 0) {
		return depth_height;
	}
	auto it = ids_texutre_color.begin();
	std::advance(it, id);
	return std::get<2>(*it);
}
