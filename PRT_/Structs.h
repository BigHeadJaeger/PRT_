#pragma once
#include<glm.hpp>
#include"Tool.h"

using namespace glm;

struct Triangle
{
	vec3 v0, v1, v2;
	int index;
	Triangle()
	{
		index = -1;
	}

	Triangle(vec3 _v0, vec3 _v1, vec3 _v2, int _index)
		:v0(_v0), v1(_v1), v2(_v2), index(_index) {}

};

//���ߵ��ཻ���ʹ�� ���ߵĲ�����ʽ �� �����εĲ�����ʾ ����
struct Ray
{
	vec3 o;					//�������
	vec3 dir;				//���߷���
	vec3 inv;

	float tmin;
	float tmax;
	float t;				//�ཻ����
	int index;				//�ཻ�������������ֵ

	Ray()
	{}

	Ray(vec3 _o, vec3 _d, float _tmin = 0.0f, float _tmax = M_INFINITE)
		:o(_o), dir(_d), tmin(_tmin), tmax(_tmax)
	{
		normalize();
	}
	void normalize()
	{
		inv.x = 1.0f / dir.x;
		inv.y = 1.0f / dir.y;
		inv.z = 1.0f / dir.z;

		t = (float)M_INFINITE;
		float length = sqrt(dir.x * dir.x + dir.y * dir.y + dir.z * dir.z);

		if (fabs(length) <= ZERO)
			return;

		dir.x /= length;
		dir.y /= length;
		dir.z /= length;
	}

};

//�����Ƿ����������ཻ��ʹ�ü���u��v��t�Ĺ�ʽ��������u��v,t��ֵȷ���Ƿ����������ཻ��
inline bool RayTriangle(Ray &ray, Triangle &tri)
{
	vec3 edge1 = tri.v1 - tri.v0;
	vec3 edge2 = tri.v2 - tri.v0;

	vec3 crossVec = glm::cross(ray.dir, edge2);

	float dotvalue = glm::dot(edge1, crossVec);

	if (fabs(dotvalue) < ZERO)
	{
		return false;
	}

	float inv = 1.0f / dotvalue;

	vec3 diffVec = ray.o - tri.v0;


	float u = glm::dot(diffVec, crossVec) * inv;
	if (u < 0.0f || u > 1.0f)
		return false;

	vec3 q = glm::cross(diffVec, edge1);

	float v = glm::dot(ray.dir, q) * inv;

	if (v < 0.0f || u + v > 1.0)
		return false;

	float t = glm::dot(edge2, q) * inv;
	if (t <= 0.0f)
		return false;

	if (t < ray.t)
	{
		ray.t = t;
		ray.index = tri.index;
	}

	return true;
}