#pragma once
#include "Program_View_Inverted.h"
class Program_Deferred :public Program_View_Inverted {
public:

	Shader_Element world_size, material_color;
protected:
	void init_shader_locations() override;
};