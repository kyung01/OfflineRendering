#include "VAO_Dictionary.h"
#include <memory>
#include <list>
#include <string>

void KGame::Render::VAO_Dictionary::init()
{
	std::string root = "Model/";
	const int SIZE = 600000;
	std::unique_ptr<float> arr_vert(new float[SIZE]);
	std::unique_ptr<float> arr_normal(new float[SIZE]);
	std::unique_ptr<int> arr_indices(new int[SIZE]);
	std::list<std::pair<MODEL_ID, std::string>> files;
	files.push_back(std::pair<MODEL_ID, std::string>(MODEL_ID::BUNNY,	"bunny.ply"));
	files.push_back(std::pair<MODEL_ID, std::string>(MODEL_ID::SPHERE,	"sphere.ply"));
	files.push_back(std::pair<MODEL_ID, std::string>(MODEL_ID::TEAPOT,	"teapot.ply"));



	for (auto i = files.begin(); i != files.end(); i++) {
		std::string path = root + (i->second);
		dic.insert(std::pair<MODEL_ID, KVertexArrayObject>
			(i->first, init_vao((const char*)&( root + i->second), arr_vert.get(), SIZE, arr_normal.get(), SIZE, arr_indices.get(), SIZE)));
	}
	
}

KVertexArrayObject KGame::Render::VAO_Dictionary::init_vao(const char* file, float * arr_vert, int arr_vert_length, float * arr_normal, int arr_normal_length, int * arr_indices, int arr_indices_length)
{
	KVertexArrayObject vao;
	int store_arr_vert_length, store_indices_length;
	AssimpScene scene(file);
	//scene.init_glList();
	scene.get_data(
		arr_vert, arr_vert_length,
		arr_normal, arr_normal_length,
		arr_indices, arr_indices_length,
		store_arr_vert_length, store_indices_length);
	vao.init(arr_vert, arr_normal, store_arr_vert_length / 3, arr_indices, store_indices_length / 3, glm::vec3(scene.sceneMax.x, scene.sceneMax.y, scene.sceneMax.z));
	return vao;
}
