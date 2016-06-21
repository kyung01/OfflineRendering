#pragma once
#include "GL\glew.h"
#include <list>
#include <tuple>
//use it to render things 
class KFrameBufferObject {
	bool isColorOn;
	int color_width, color_height, depth_width, depth_height;
	GLuint id_texture_depth;
public:
	std::list<std::tuple<GLuint, int, int> > ids_texutre_color;
	GLuint id_fbo;
	KFrameBufferObject();//create frame buffer without depth or color
	bool init();
	bool init(int width, int height);
	void set_colorbuffer(int width, int height);
	void set_depthbuffer(int width, int height);
	//accessors

	GLuint get_color(int id = 0);
	GLuint get_depth();
	int get_color_width(int id = 0);
	int get_color_height(int id = 0);

	//int get_depth_width();
	//int get_depth_height;

};