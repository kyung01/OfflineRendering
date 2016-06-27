#pragma once
#include "KVertexArrayObject.h"
#include "AssimpScene.h"
#include <map>

namespace KGame {namespace Render {
	class VAO_Dictionary {
		KVertexArrayObject init_vao(const char* file, float * arr_vert, int arr_vert_length, float * arr_normal, int arr_normal_length, int * arr_indices, int arr_indices_length);
	public:
		enum MODEL_ID {BUNNY,TEAPOT,SPHERE};
		std::map<MODEL_ID, KVertexArrayObject> dic;
		void init();

	};
}}