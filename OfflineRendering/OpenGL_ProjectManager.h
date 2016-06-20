#pragma once
#include "EasyGLFW.h"
#include "WorldRenderer.h"
#include "Program_Default.h"
#include "Program_Texture.h"
#include "Program_Shadow.h"
#include "Program_Normal.h"
#include "Program_WorldSpace.h"
#include "Program_Flux.h"
#include "KFrameBufferObject.h"
class OpenGL_ProjectManager {
	const char* PATH_SHADER_VERTEX_DEFAULT =	"Shader/shader_default_vert.txt";
	const char* PATH_SHADER_FRAG_DEFAULT =		"Shader/shader_default_frag.txt";

	const char* PATH_SHADER_TEXTURE_VERT = "Shader/shader_texture_vert.txt";
	const char* PATH_SHADER_TEXTURE_FRAG = "Shader/shader_texture_frag.txt";
	const char* PATH_SHADER_SHADOW_VERT = "Shader/shader_shadow_vert.txt";
	const char* PATH_SHADER_SHADOW_FRAG = "Shader/shader_shadow_frag.txt";

	const char* PATH_SHADER_NORMAL_VERT = "Shader/shader_normal_vert.txt";
	const char* PATH_SHADER_NORMAL_FRAG = "Shader/shader_normal_frag.txt";
	const char* PATH_SHADER_WORLDSPACE_VERT = "Shader/shader_worldspace_vert.txt";
	const char* PATH_SHADER_WORLDSPACE_FRAG = "Shader/shader_worldspace_frag.txt";


	const char* PATH_SHADER_FLUX_VERT = "Shader/shader_flux_spotlight_vert.txt";
	const char* PATH_SHADER_FLUX_FRAG = "Shader/shader_flux_spotlight_frag.txt";

	EasyGLFW easyGLFW;
	WorldRenderer worldRender;
	Program_Default program_default; // will be used to... do stuff
	Program_WorldSpace program_worldsapce;
	Program_View_Inversed program_normal;
	Program_texture program_texture;
	Program_Shadow	program_shadow;
	Program_Flux program_flux;

	KFrameBufferObject fbo_light, fbo_normal, fbo_worldSpace, fbo_flux;
	glm::vec3 world_space;
	glm::mat4 mat_proj_firstPerson;
	glm::mat4 mat_proj_ortho;
	glm::mat4 mat_proj_ortho_screen;

	glm::mat4 mat_me_modelView;
	glm::mat4 mat_me_view_inversed;
	glm::mat4 mat_light_modelView;
	glm::mat4 mat_light_view_inverted;
	glm::mat4 mat_light_MVP;
	glm::mat4 biasMatrix;
	glm::vec4 color_default;
	

	//void init_fbo();
	//void init_shader();
	//void init_program(GLuint &program_id, GLuint shader_vertex, GLuint shader_frag);
	//bool init_shader(GLuint *shader_id, GLenum shaderType,  char* data, int data_size);
	void render_texture(GLuint id_vert, GLuint id_vert_texture, GLuint id_texture, int index);
	void hpr_basisc_glTexParameteri();
	//int hpr_txt_to_char(char* buffer, int buffer_size, const char* path);
	//bool hpr_is_shader_compiled(GLint shaderID);
	void error(const char* error_message);
	void glm_mat_array(float* arr, glm::mat4 *mat);

	void set_FBO(KFrameBufferObject * buffer);
public:
	enum RenderState {RENDER_UNDEFINED, RENDER_REALTIME,RENDER_OFFLINE,RENDER_END};
	RenderState stateRender;
	void init();
	void renderRealTimeBegin();
	//void renderRealTimeBegin_old();
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