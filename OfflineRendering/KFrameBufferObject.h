#pragma once
#include "GL\glew.h"
//use it to render things 
class KFrameBufferObject {
	GLuint id_fbo, id_texture_color, id_texture_depth;
	int color_width, color_height, depth_width, depth_height;
public:
	KFrameBufferObject();//create frame buffer without depth or color
	bool init();
	void set_framebuffer(int width, int height);
	void set_depthbuffer(int width, int height);
	GLuint id;
	//accessors
	int get_color_width();
	int get_color_height();
	int get_depth_width();
	int get_depth_height;

};