#pragma once
#include <assimp\cimport.h>
#include <assimp\scene.h>
#include <assimp\postprocess.h>
#include <assimp\matrix4x4.h>
#include <assimp\vector3.h>
#include <algorithm>
class AssimpScene {
	const aiScene *scene;
	void recursive_getBoundingBox(
		const aiScene *scene, const aiNode* nd,
		aiVector3D & sceneMin, aiVector3D& sceneMax, aiMatrix4x4* sceneMatrix);
	void recursive_render(const aiScene *sc, const aiNode* nd);
	void applyMaterial(const  aiMaterial *mtl);
	int ai_get_mat_color(const aiMaterial* mat, const char* key, int type, int index, float *color);
	void hpr_set_float4(float *f, float a, float b, float c, float d);
	void hpr_color4_to_float4(aiColor4D *color4, float *float4);
	std::pair<char*, int*> hpr_to_pair_char_arr_int(char * c, int a, int b);
public:
	aiVector3D sceneMin, sceneMax, sceneCenter;
	AssimpScene(const char* path);
	void Render();
};