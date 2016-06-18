#pragma once
#include <assimp\cimport.h>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <assimp\matrix4x4.h>
#include <assimp\vector3.h>
#include <algorithm>
#include "GLFW_GLEW.h"
class AssimpScene {
	const aiScene *scene;
	void update_min_max(aiVector3D &min, aiVector3D &max, aiVector3D vert_new);
	void update_center(
		float * vert, int length, 
		aiVector3D &min, aiVector3D &max, aiVector3D &center);
	void rescale_verts(float* vert, int length);

	//delete
	void adjust_scene_roperty(float x, float y, float z);
	void recursive_getBoundingBox(
		const aiScene *scene, const aiNode* nd,
		aiVector3D & sceneMin, aiVector3D& sceneMax, aiMatrix4x4* sceneMatrix);
	void recursive_render(const aiScene *sc, const aiNode* nd, aiMatrix4x4 *matrix_before);
	void recursive_render_cheap(GLuint id_vertex,  const aiScene *sc, const aiNode* nd, aiMatrix4x4 *matrix_before);
	void recursive_render_old(const aiScene *sc, const aiNode* nd);
	void applyMaterial(const  aiMaterial *mtl);
	int ai_get_mat_color(const aiMaterial* mat, const char* key, int type, int index, float *color);
	void hpr_set_float4(float *f, float a, float b, float c, float d);
	void hpr_color4_to_float4(aiColor4D *color4, float *float4);
	int uncompress_recursive_old(float* arr, float arr_size, float vertex_size, int arr_index_start, const aiScene *sc, const aiNode* nd, aiMatrix4x4 *matrix_before);
	std::pair<char*, int*> hpr_to_pair_char_arr_int(char * c, int a, int b);
public:
	int gl_scene_id;
	aiVector3D sceneMin, sceneMax, sceneCenter;
	AssimpScene(const char* path);

	void get_data(
		float *arr_vertex,int arr_vertex_length,
		float* arr_normal,int arr_normal_length, 
		int * arr_indices,int arr_indices_length, int& store_num_vertex, int &store_num_faces);

	void uncompress(
		float* arr_vertex, int arr_vertex_size, int& arr_vertex_size_used,
		int* arr_indices, int arr_indices_size, int& arr_indices_size_used);
	void uncompress_recursive(
		aiNode* nd,
		float * arr_vertex, int arr_vertex_length, int & arr_vertex_index,
		float * arr_normal, int arr_normal_length,
		int * arr_indeces, int arr_indeces_size, int & arr_indices_index);
	int uncompress_vertex(aiMesh* mesh, float* arr, int arr_size, int arr_index);
	int uncompress_normal(aiMesh* mesh, float* arr, int arr_size, int arr_index);
	int uncompress_indices(aiMesh* mesh, int* arr, int arr_size, int arr_index);


	//delete all
	int toArr(float *arr, int arr_size);
	int init_glList();
	void Render();
	void RenderCheap(GLuint id_vertex);
	
	/*
	*/
	//,float* arr_normals, int arr_normals_size, int& arr_normals_size_used
	//int uncompress(float* arr, float arr_size, float vertex_size);
};