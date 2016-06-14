#pragma once
#include "EasyGLFW.h"
#include "WorldRenderer.h"
class OpenGL_ProjectManager {
	EasyGLFW easyGLFW;
	WorldRenderer worldRender;
	GLuint fbo_depth;
	GLuint texture_color, texture_depth;
	GLuint program_00;
	GLuint shader_vertex, shader_frag;
	void init_fbo();
	void init_shader();
	void init_program(GLuint &program_id, GLuint shader_vertex, GLuint shader_frag);
	bool init_shader(GLuint *shader_id, GLenum shaderType,  char* data, int data_size);
	void render_texture(GLuint texture, int index);
	void hpr_basisc_glTexParameteri();
	int hpr_txt_to_char(char* buffer, int buffer_size, const char* path);
	bool hpr_is_shader_compiled(GLint shaderID);
public:
	enum RenderState {RENDER_UNDEFINED, RENDER_REALTIME,RENDER_OFFLINE,RENDER_END};
	RenderState stateRender;
	void init();
	void renderRealTimeBegin();
	void renderRealTimeEnd();
	void renderOfflineBegin();
	void renderOfflineEnd();
	void end();

};
/*
#include "Main.h"

#include "EasyGLFW.h"


bool main() {

EasyGLFW myGLFW;
myGLFW.init(500,500,"hi");
myGLFW.startLoop();

std::cout << "SystemEnding...\n";
return true;
//system("pause");
}
*/