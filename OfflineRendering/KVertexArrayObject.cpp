#include "KVertexArrayObject.h"

void KVertexArrayObject::init(
	float * vert, float * normal, int num_vertex,
	int* indices, int num_faces, glm::vec3 boundingBox)
{
	this->boundingBox = boundingBox;
	this->indice_length = num_faces;
	GLuint
		loc_vertex_position = 0,
		loc_vertex_normal = 1;
	glGenVertexArrays(1, &id_vertex_array);
	glBindVertexArray(id_vertex_array);

	glGenBuffers(1, &id_indices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_indices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * 3 * num_faces, indices, GL_STATIC_DRAW);

	glGenBuffers(1, &id_vertex_position_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex_position_buffer);
	glVertexAttribPointer(loc_vertex_position, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3*num_vertex, vert, GL_STATIC_DRAW);
	glEnableVertexAttribArray(loc_vertex_position);

	glGenBuffers(1, &id_vertex_normal_buffer);
	glVertexAttribPointer(loc_vertex_normal, 3, GL_FLOAT, GL_TRUE, 0, 0);
	glBindBuffer(GL_ARRAY_BUFFER, id_vertex_normal_buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*3* num_vertex, normal, GL_STATIC_DRAW);
	glEnableVertexAttribArray(loc_vertex_normal);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
