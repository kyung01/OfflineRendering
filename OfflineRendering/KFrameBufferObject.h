#pragma once
#include "GL\glew.h"
//use it to render things 
class KFrameBufferObject {
	int color_width, color_height, depth_width, depth_height;
public:
	GLuint id_fbo, id_texture_color, id_texture_depth;

	KFrameBufferObject();//create frame buffer without depth or color
	bool init();
	void set_colorbuffer(int width, int height);
	void set_depthbuffer(int width, int height);
	//accessors
	int get_color_width();
	int get_color_height();
	int get_depth_width();
	int get_depth_height;

};