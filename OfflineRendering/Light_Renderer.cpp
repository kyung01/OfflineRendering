#include "Light_Renderer.h"

Light_Renderer::Light_Renderer()
{
	
}

//delete this later
void Light_Renderer::init()
{
	int size = 256;
	buffer_worldSpace.init(size, size);
	buffer_flux.init(size, size);
	buffer_normal.init(size, size);
	
}

void Light_Renderer::init(char * path_worldspace_vert, char * path_worldspace_frag, char * path_normal_vert, char * path_normal_frag, char * path_flux_vert, char * path_flux_frag)
{
	init();
	//p_worldspace.init( );
}

void Light_Renderer::prepare()
{
	buffer_worldSpace.init();
	
}
