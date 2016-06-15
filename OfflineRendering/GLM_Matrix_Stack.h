#pragma once
#include <list>
#include <vector>
#include <memory>
#include <stack>
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
using namespace std;
//replace the OpenGL matrix
class GLM_Matrix_Stack {
	std::stack<glm::mat4> stack;
	/*
	std::shared_ptr<float> matrix; // current matrix
	//opengl functions made up
	void glhPerspectivef2(float *matrix, float fovyInDegrees, float aspectRatio,
		float znear, float zfar);
	void glhFrustumf2(float *matrix, float left, float right, float bottom, float top,
		float znear, float zfar);
	void glhLookAtf2(float *matrix, float *eyePosition3D, float *center3D, float *upVector3D);
	void NormalizeVector(float* vec);
	void ComputeNormalOfPlane(float *resulted, float * a, float *b);
	void MultiplyMatrices4by4OpenGL_FLOAT(float* resulted, float* u, float* v);
	void glhTranslatef2(float *resulted, float x, float y, float z);
	*/
	
public:
	glm::mat4 mat;
	void push(); //pushes the current matrix to the stack
	void pop(); //set the current matrix to the poped matrix from the stack

	//gluperspectice for projection
	//gluLookAt for modelview
	//gluOrtho for projection 
	//translated, scale, rotate traditional translation 
	/*
	MatrixReplacement();
	void identity();
	void perspective(float fovy, float aspect, float near, float far);
	void push_matrix();
	void pop_matrix();
	*/

};