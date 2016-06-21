#include "I_Light_Renderer_Call.h"
#include "KFrameBufferObject.h"
#include "Program_WorldSpace.h"
#include "Program_Default.h"
#include "Program_Normal.h"
#include "Program_Flux.h"


#pragma once
class Light_Renderer{
	//I know projection,
public:
	KFrameBufferObject 
		buffer_worldSpace, 
		buffer_normal, 
		buffer_flux;
	Program_WorldSpace p_worldspace;
	Program_Normal p_normal;
	Program_Flux p_flux; 
	
	Light_Renderer();
	void init();
	void init(
		char* path_worldspace_vert, char* path_worldspace_frag,
		char* path_normal_vert,		char* path_normal_frag,
		char* path_flux_vert,		char* path_flux_frag);

	void prepare(); // call this before you render.
	void render(I_Light_Renderer_Call &call); // will call these function couple times;
};
