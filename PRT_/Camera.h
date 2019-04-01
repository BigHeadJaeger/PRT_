#pragma once
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
using namespace glm;
class MyCamera
{
public:
	vec3 eyePos;
	vec3 lookAtPoint;
	vec3 up;
	mat4 view;
	mat4 pro;
	//相机空间的三个向量
	vec3 lookDir;
	vec3 lookRight;
	vec3 lookUp;
public:
	MyCamera();
	void SetView();
	void SetPro();
public:
	void Walk(float dis);
	void LRMove(float dis);
	void LRRotate(float dis);
};

