#include "AssimpScene.h"
#include <iostream>
#include <map>
#include <iostream>

void AssimpScene::adjust_scene_roperty(float x, float y, float z)
{
}

void AssimpScene::recursive_getBoundingBox(
	const aiScene *scene, const aiNode* nd,
	aiVector3D & sceneMin, aiVector3D & sceneMax, aiMatrix4x4* sceneMatrix)
{
	aiMatrix4x4 sceneMatrixOriginal = *sceneMatrix;
	aiMultiplyMatrix4(sceneMatrix, & nd->mTransformation);
	for (int n=0; n < nd->mNumMeshes; n++) {
		aiMesh* mesh = scene->mMeshes[nd->mMeshes[n]];
		for (int t = 0; t < mesh->mNumVertices; t++) {
			aiVector3D vert = mesh->mVertices[t];
			aiTransformVecByMatrix4(&vert, sceneMatrix);
			sceneMin.x = std::min(sceneMin.x, vert.x);
			sceneMin.y = std::min(sceneMin.y, vert.y);
			sceneMin.z = std::min(sceneMin.z, vert.z);

			sceneMax.x = std::max(sceneMax.x, vert.x);
			sceneMax.y = std::max(sceneMax.y, vert.y);
			sceneMax.z = std::max(sceneMax.z, vert.z);

		}
	}
	//std::cout << "AssimpScene SceneMin " << sceneMin.x << " , " << sceneMin.y << " , " << sceneMin.z << std::endl;
	//std::cout << "AssimpScene SceneMax " << sceneMax.x << " , " << sceneMax.y << " , " << sceneMax.z << std::endl;
	for (int n = 0; n < nd->mNumChildren; n++) {
		recursive_getBoundingBox(scene,nd->mChildren[n], sceneMin, sceneMax,sceneMatrix);
	}
	*sceneMatrix = sceneMatrixOriginal;
}

void AssimpScene::recursive_render(const aiScene * sc, const aiNode * nd, aiMatrix4x4 *matrix_before)
{
	aiMatrix4x4 m = (*matrix_before) * nd->mTransformation;
	//aiTransposeMatrix4(&m);
	//glMultMatrixf((float*)&m);
	//std::cout <<"mNumMeshes " << nd->mNumMeshes <<std::endl;
	for (int n = 0; n < nd->mNumMeshes; ++n) {
		const aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];
		for (int t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			for (int i = 0; i < face->mNumIndices; i++) {
				int index = face->mIndices[i];
				aiVector3D vert, normal;
				vert = m*mesh->mVertices[index];
				if (mesh->mColors[0] != NULL);// glColor4fv((GLfloat*)&mesh->mColors[0][index]);
				if (mesh->mNormals != NULL) normal = mesh->mNormals[index];

			}
		}

	}

	for (int n = 0; n < nd->mNumChildren; ++n) {
		recursive_render(sc, nd->mChildren[n], &m);
	}
}
void AssimpScene::recursive_render_cheap(GLuint id_vertex, const aiScene * sc, const aiNode * nd, aiMatrix4x4 *matrix_before)
{
	aiMatrix4x4 m = (*matrix_before) * nd->mTransformation;
	//aiTransposeMatrix4(&m);
	//glMultMatrixf((float*)&m);
	//std::cout <<"mNumMeshes " << nd->mNumMeshes <<std::endl;
	for (int n = 0; n < nd->mNumMeshes; ++n) {
		const aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];
		for (int t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			for (int i = 0; i < face->mNumIndices; i++) {
				int index = face->mIndices[i];
				aiVector3D vert, normal;
				vert = m*mesh->mVertices[index];
				glVertexAttrib3f(id_vertex, vert.x, vert.y, vert.z);
				if (mesh->mColors[0] != NULL);// glColor4fv((GLfloat*)&mesh->mColors[0][index]);
				if (mesh->mNormals != NULL) normal = mesh->mNormals[index];

			}
		}

	}

	for (int n = 0; n < nd->mNumChildren; ++n) {
		recursive_render(sc, nd->mChildren[n], &m);
	}
}
void AssimpScene::recursive_render_old(const aiScene * sc, const aiNode * nd)
{
	aiMatrix4x4 m = nd->mTransformation;
	aiTransposeMatrix4(&m);
	glPushMatrix();
	glMultMatrixf((float*)&m);
	//std::cout <<"mNumMeshes " << nd->mNumMeshes <<std::endl;
	for (int n = 0; n < nd->mNumMeshes; ++n) {
		const aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];
		//std::cout << "mNumFaces " << mesh->mNumFaces << std::endl;
		applyMaterial(sc->mMaterials[mesh->mMaterialIndex]);

		if (mesh->mNormals == NULL) {
			//std::cout << "DISABLE LIGHTENING " << std::endl;
			glDisable(GL_LIGHTING);
		}
		else {
			//std::cout << "ENABLE LIGHTENING "  << std::endl;
			glEnable(GL_LIGHTING);
		}
		//apply_material(sc->mMaterials[mesh->mMaterialIndex]);

		//std::cout << "mesh->mNumFaces begin" << std::endl;
		

		for (int t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			GLenum face_mode;

			switch (face->mNumIndices) {
			case 1: face_mode = GL_POINTS; break;
			case 2: face_mode = GL_LINES; break;
			case 3: face_mode = GL_TRIANGLES; break;
			default: face_mode = GL_POLYGON; break;
			}
			//if (mesh->mNormals == NULL) glDisable(GL_LIGHTING);
			// else glEnable(GL_LIGHTING);
			glBegin(face_mode);

			for (int i = 0; i < face->mNumIndices; i++) {
				int index = face->mIndices[i];
				if (mesh->mColors[0] != NULL)
					glColor4fv((GLfloat*)&mesh->mColors[0][index]);
				if (mesh->mNormals != NULL)
					glNormal3fv(&mesh->mNormals[index].x);
				glVertex3fv(&mesh->mVertices[index].x);
			}

			glEnd();
		}

	}

	for (int n = 0; n < nd->mNumChildren; ++n) {
		aiMatrix4x4 m;
		recursive_render(sc, nd->mChildren[n],&m );
	}
	glPopMatrix();
}

void AssimpScene::applyMaterial(const aiMaterial * mtl)
{
	
	//AI_MATKEY_COLOR_DIFFUSE       char int int
	//GL_FRONT_AND_BACK GL_DIFFUSE  int int

	//std::map<const char*, int*> ai_matkeys = { { "",arr } };
	//ai_matkeys.insert(std::pair<char*, int*>("", arr));
	


	/*
	GLenum fill_mode;
	hpr_set_float4(color, 0.8f, 0.8f, 0.8f, 1.0f);
	*/
	//GL_Mat mat(0,0,0);
	aiColor4D colorAI;
	float color[4];
	typedef std::pair<char*, int*> AI_MATKEY; // AI_MATKEY_COLOR_TYPE comes as char int int
	typedef std::pair<int, int> GL_MATERIAL; // FACE_GL, MATERIAL_TYPE;
	typedef std::pair<int, int*> MAT_DEFAULT_COLOR;
	std::map<AI_MATKEY, GL_MATERIAL>	argument_list;
	std::map<int, float*>					mat_default_color;
	float color_diffuse[] = { 1.0f,1.0f,1.0f,1 };
	float color_specular[] = { 0,0.0f,0,1 };
	float color_ambient[] = { 0.2f,0.2f,0.2f,1 }; //color of an object under shadow
	float color_emission[] = { 0,0,0,1 };

	argument_list.insert({ hpr_to_pair_char_arr_int(AI_MATKEY_COLOR_DIFFUSE), std::pair<int, int>(GL_FRONT_AND_BACK, GL_DIFFUSE) });
	argument_list.insert({ hpr_to_pair_char_arr_int(AI_MATKEY_COLOR_SPECULAR), std::pair<int, int>(GL_FRONT_AND_BACK, GL_SPECULAR) });
	argument_list.insert({ hpr_to_pair_char_arr_int(AI_MATKEY_COLOR_AMBIENT), std::pair<int, int>(GL_FRONT_AND_BACK, GL_AMBIENT) });
	argument_list.insert({ hpr_to_pair_char_arr_int(AI_MATKEY_COLOR_EMISSIVE), std::pair<int, int>(GL_FRONT_AND_BACK, GL_EMISSION) });

	mat_default_color.insert({ GL_DIFFUSE ,color_diffuse });
	mat_default_color.insert({ GL_SPECULAR ,color_specular });
	mat_default_color.insert({ GL_AMBIENT ,color_ambient });
	mat_default_color.insert({ GL_EMISSION ,color_emission });

	for (std::map<AI_MATKEY, GL_MATERIAL>::iterator it = argument_list.begin(); it != argument_list.end();it++) {
		AI_MATKEY mat_key = it->first;
		GL_MATERIAL gl_mat = it->second;
		float* colorDefault = mat_default_color[gl_mat.second];
		hpr_set_float4(color, .1, .1, .1, 1);
		//std::cout << "applyMaterial " << mat_key.first << " ";
		if (AI_SUCCESS == aiGetMaterialColor(mtl, mat_key.first, mat_key.second[0], mat_key.second[1], &colorAI)) {
			hpr_color4_to_float4(&colorAI, color);
			glMaterialfv(gl_mat.first, gl_mat.second, color);
			//std::cout << " true " << std::endl;
		}
		else {
			glMaterialfv(gl_mat.first, gl_mat.second, colorDefault);
			//std::cout << " false " << std::endl;
		}
		//std::cout << color[0] << " " << color[1] << " " << color[2] << std::endl;
		
		ai_get_mat_color(mtl, AI_MATKEY_COLOR_DIFFUSE, color);
	}

	/*
	ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
	if (ret1 == AI_SUCCESS) {
		max = 1;
		ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);
		if (ret2 == AI_SUCCESS)
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
		else
			glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
	}
	else {
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
		set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
	}

	max = 1;
	if (AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	max = 1;
	if ((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
		glDisable(GL_CULL_FACE);
	else
		glEnable(GL_CULL_FACE);
	*/
}

int AssimpScene::ai_get_mat_color(const aiMaterial * mat, const char * key, int type, int index, float * color)
{
	aiColor4D colorAI;
	hpr_set_float4(color, 1.0f, 0.0f, 0.0f, 1.0f); // default color red
	if (AI_SUCCESS == aiGetMaterialColor(mat,key,type,index,&colorAI)) {
	}
	return 0;
}

void AssimpScene::hpr_set_float4(float *f, float a, float b, float c, float d)
{
	f[0] = a;
	f[1] = b;
	f[2] = c;
	f[3] = d;
}

void AssimpScene::hpr_color4_to_float4(aiColor4D * color4, float * float4)
{
	float4[0] = color4->r;
	float4[1] = color4->g;
	float4[2] = color4->b;
	float4[3] = color4->a;
}

int AssimpScene::uncompress_recursive_old(float * arr, float arr_size, float vertex_size, int arr_index_start, const aiScene * sc, const aiNode * nd, aiMatrix4x4 * matrix_before)
{
	aiMatrix4x4 m = (*matrix_before) * nd->mTransformation;
	int arr_index = arr_index_start;
	int count_vertex = 0; //combined sum is returned at the end

	for (int n = 0; n < nd->mNumMeshes; ++n) {
		const aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];
		for (int t = 0; t < mesh->mNumFaces; ++t) {
			const struct aiFace* face = &mesh->mFaces[t];
			bool isNormal = mesh->mNormals != NULL;

			for (int i = 0; i < face->mNumIndices; i++) {
				count_vertex++;
				int index = face->mIndices[i];
				aiVector3D 
					vert(m*mesh->mVertices[index]),
					normal((isNormal)? aiVector3D (mesh->mNormals[index]): aiVector3D());
				adjust_scene_roperty(vert.x, vert.y, vert.z);
				arr[arr_index]		= vert.x;
				arr[arr_index + 1]	= vert.y;
				arr[arr_index + 2]	= vert.z;
				arr[arr_index + 3]	= normal.x;
				arr[arr_index + 4]	= normal.y;
				arr[arr_index + 5]	= normal.z;
				arr_index			+= vertex_size;
			}
		}

	}

	for (int n = 0; n < nd->mNumChildren; ++n) {
		count_vertex += uncompress_recursive_old(arr, arr_size, vertex_size, arr_index, sc, nd, &m);
	}
	return count_vertex;
}

std::pair<char*, int*> AssimpScene::hpr_to_pair_char_arr_int(char * c, int a, int b)
{
	int arr[] = { a,b };
	return std::pair<char*, int*>(c, arr);
}

AssimpScene::AssimpScene(const char* path)
{
	scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
	aiMatrix4x4 sceneMatrix;
	aiIdentityMatrix4(&sceneMatrix);
	if (!scene) throw std::invalid_argument("Path is invalid");
	recursive_getBoundingBox(scene, scene->mRootNode, this->sceneMin, this->sceneMax,&sceneMatrix);
	sceneCenter.x = (sceneMin.x + sceneMax.x) / 2.0f;
	sceneCenter.y = (sceneMin.y + sceneMax.y) / 2.0f;
	sceneCenter.z = (sceneMin.z + sceneMax.z) / 2.0f;
	
}

int AssimpScene::init_glList()
{
	this->gl_scene_id = glGenLists(1);
	glNewList(gl_scene_id, GL_COMPILE);
	Render();
	glEndList();
	return gl_scene_id;
}

void AssimpScene::Render()
{
	bool is_lighting = glIsEnabled(GL_LIGHTING);
	aiMatrix4x4 m;
	recursive_render(this->scene, this->scene->mRootNode, &m);
	if (is_lighting)
		glEnable(GL_LIGHTING);
	else
		glDisable(GL_LIGHTING);
}
void AssimpScene::RenderCheap(GLuint id)
{
	aiMatrix4x4 m;
	recursive_render_cheap(id, this->scene, this->scene->mRootNode, &m);
	
}

void AssimpScene::get_data(
	float * arr_vertex, int arr_vertex_length, 
	float * arr_normal, int arr_normal_length, 
	int * arr_indices, int arr_indices_length, 
	int & store_num_vertex, int & store_num_faces)
{
	store_num_vertex = 0;
	store_num_faces = 0;
	uncompress_recursive(this->scene->mRootNode,
		arr_vertex, arr_vertex_length, store_num_vertex,
		arr_normal, arr_normal_length,
		arr_indices, arr_indices_length, store_num_faces);
	/*
	{
		for (int i = 0; i < store_num_vertex / 3; i++) {
			std::cout << "POS : " << arr_vertex[i * 3 + 0] << " " << arr_vertex[i * 3 + 1] <<" " << arr_vertex[i * 3 + 2] << std::endl;
			std::cout << "NOR : " << arr_normal[i * 3 + 0] << " " << arr_normal[i * 3 + 1] << " " <<arr_normal[i * 3 + 2] << std::endl;
		}
		for (int i = 0; i < store_num_faces/3; i++) {
			std::cout << "indices : " << arr_indices[i * 3 + 0] << " " << arr_indices[i * 3 + 1] << " "<< arr_indices[i * 3 + 2] << std::endl;
		}
	}
	*/
}

int AssimpScene::toArr(float * arr, int arr_size)
{
	const int ARR_TEMP_SIZE = 3*40000;
	int index_vertex=0, index_indices=0;
	float arr_vertex[ARR_TEMP_SIZE];
	int arr_indices[ARR_TEMP_SIZE];
	uncompress(
		arr_vertex, ARR_TEMP_SIZE, index_vertex, 
		arr_indices, ARR_TEMP_SIZE, index_indices);;
	for (int i = 0; i< 1000000 ;i++) {

		int index = i * 3;
		if (6 + i * 6 >= arr_size) {
			std::cout << "Require size of " << arr_size -(index_vertex + index_indices) << std::endl;
			system("pause");
			exit(0);
		}
		//arr[1] =1;
		
		arr[i * 6 + 0] = arr_vertex[index + 0];
		arr[i*6 + 1] =	arr_vertex[index + 1];
		arr[i*6 + 2] =	arr_vertex[index + 2];

		arr[i*6 + 3] = arr_indices[index + 0];
		arr[i*6 + 4] = arr_indices[index + 1];
		arr[i*6 + 5] = arr_indices[index + 2];
		
		if (i * 3 + 3 >= index_vertex || i * 3 + 3 >= index_indices) {
			std::cout << "done" << std::endl;
			return i; // this is how many vertices I have saved 
		}
	}
	return 0;
}

void AssimpScene::uncompress(
	float * arr_vertex, int arr_vertex_size, int & arr_vertex_size_used, 
	int * arr_indices, int arr_indices_size, int & arr_indices_size_used)
{
	//uncompress_recursive(scene->mRootNode,
	//	arr_vertex, arr_vertex_size, arr_vertex_size_used,
	//	arr_indices, arr_indices_size, arr_indices_size_used);
}
void AssimpScene::uncompress_recursive(
	aiNode* nd,
	float * arr_vertex, int arr_vertex_length, int & arr_vertex_index,
	float * arr_normal, int arr_normal_length,
	int * arr_indices, int arr_indices_size, int & arr_indices_index)
{	
	int arr_normal_index = 0;
	//aiScene* scene;
	for (int i = 0; i < scene->mNumMeshes; i++) {
		aiMesh *mesh = scene->mMeshes[i];
		arr_vertex_index = uncompress_vertex(mesh, arr_vertex, arr_vertex_length, arr_vertex_index);
		uncompress_normal(mesh, arr_normal, arr_normal_length, arr_normal_index);
		arr_indices_index = uncompress_indices(mesh, arr_indices, arr_indices_size, arr_indices_index);
	}
	return;
	
	for (int n = 0; n < nd->mNumChildren; ++n) {
		uncompress_recursive(nd->mChildren[n],
			arr_vertex, arr_vertex_length, arr_vertex_index,
			arr_normal, arr_normal_length,
			arr_indices, arr_indices_size, arr_indices_index);
	}
}
int AssimpScene::uncompress_vertex(aiMesh *mesh, float* arr, int arr_size, int arr_index) {
	for (int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D vert = mesh->mVertices[i];
		//std::cout << "ARR SIZE " << arr_size << " , " << "I USED " << arr_index+3 << std::endl;
		if (arr_index + 3 > arr_size) {
			std::cout << mesh->mNumVertices << " ARR SIZE " << arr_size << " , " << "I USED " << arr_index + 3 << std::endl;
			throw std::invalid_argument("AssimpScene::uncompress_vertex:: array size too small");
		}
		arr[arr_index] = vert.x;
		arr[arr_index + 1] = vert.y;
		arr[arr_index + 2] = vert.z;
		arr_index += 3;
	}
	return arr_index;
}
int AssimpScene::uncompress_normal(aiMesh * mesh, float * arr, int arr_size, int arr_index)
{
	if (!mesh->HasNormals()) return 0;
	for (int i = 0; i < mesh->mNumVertices; i++) {
		aiVector3D normal = mesh->mNormals[i];
		if (arr_index + 3 > arr_size) {
			std::cout << mesh->mNumVertices << " ARR SIZE " << arr_size << " , " << "I USED " << arr_index + 3 << std::endl;
			throw std::invalid_argument("AssimpScene::uncompress_vertex:: array size too small");
		}
		arr[i*3] = normal.x;
		arr[i*3 + 1] = normal.y;
		arr[i*3 + 2] = normal.z;
		arr_index += 3;
	}
	return arr_index;
}
int AssimpScene::uncompress_indices(aiMesh *mesh, int* arr, int arr_size, int arr_index) {
	for (int i = 0; i < mesh->mNumFaces && arr_index < arr_size; i++) {
		aiFace face = mesh->mFaces[i];
		for (int j = 0; j < face.mNumIndices; j++) {
			arr[arr_index++] = face.mIndices[j];
		}
	}
	return arr_index;
}


/*
int AssimpScene::uncompress(float * arr, float arr_size, float vertex_size)
{
	aiMatrix4x4 mat;
	return uncompress_recursive(arr, arr_size, vertex_size, 0,this->scene, this->scene->mRootNode, &mat);
}
*/
