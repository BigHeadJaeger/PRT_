//����Ļ��࣬������������;��淴�������ɴ�������

#pragma once
#include<iostream>
#include<vector>
#include <fstream>
#include <sstream>

#include<glm.hpp>


#include"Structs.h"

using namespace std;
using namespace glm;

//�����AABB��Χ��
struct AABB
{
	vec3 minPos;
	vec3 maxPos;
};

enum ObjIndexType
{
	Triangles,
	Quad
};

//������һ�������Ϣ���ϵ�һ��
struct Point
{
	vec3 vertex;
	vec2 texcoord;
	vec3 normal;
};

//obj�ļ�������ÿ����������������ꡢ���㷨�����ꡢ�������꣨��ѡ������������������ͬ
class Object
{

protected:
	string modelPath;						//ģ��·��
	int band;								//SH����
	vec3 albedo;							//���巴���ʣ�������ֵ��ʽ��Ҳ���Բ�����ͼ��ʽ��

	ObjIndexType indexType;					//obj�ļ���������ʽ

	AABB aabb;								//��Χ��
public:


	vector<Point> pointsData;

	vector<unsigned> renderIndex;			//������϶��������

	vector<Triangle> triangleFace;
	//vector<unsigned> normalsIndex;			//��ŷ�������

public:
	Object(){}

	//��ȡobj�ļ�ģ�ͣ�ָ������Ļ���������
	void Init(string fileName,vec3 _albedo,bool isTexture,ObjIndexType type);
	//��ģ������滮����λһ��
	void ObjNormalize();

	//ͶӰ��������ͺ�����
	virtual void ProjectToSH(int mode,int band,int sampleNumber,int bounce){}		//����Ϊģʽ�����֣���SH��������������������������Է���ʱ���ã�
	//��ϵ��д�뵽�ļ�
	virtual void WriteToFile(string fileName){}

	//��ȡϵ���ļ�

public:
	//bool intersectTest(Ray& ray,int)

};