#pragma once
#include "GLFW_GLEW.h"

class KVertexArrayObject {
public:
	int indice_length;
	GLuint 
		id_vertex_array, id_indices,
		id_vertex_position_buffer, id_vertex_normal_buffer;
	void init(
		float * vert, float *normal, int num_vertex, 
		int* indices, int num_faces);

};