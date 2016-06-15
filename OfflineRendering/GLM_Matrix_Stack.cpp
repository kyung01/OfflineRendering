#include "GLM_Matrix_Stack.h"

void GLM_Matrix_Stack::push()
{
	this->stack.push(this->mat);
}

void GLM_Matrix_Stack::pop()
{
	this->mat = stack.top();
	this->stack.pop();
}

