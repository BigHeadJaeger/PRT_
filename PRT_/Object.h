//物体的基类，有漫反射物体和镜面反射物体由此类派生

#pragma once
#include<iostream>
#include<vector>
#include <fstream>
#include <sstream>

#include<glm.hpp>


#include"Structs.h"

using namespace std;
using namespace glm;

//物体的AABB包围盒
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

//用来将一个点的信息整合到一起
struct Point
{
	vec3 vertex;
	vec2 texcoord;
	vec3 normal;
};

//obj文件必须是每个顶点包含顶点坐标、顶点法线坐标、纹理坐标（可选）。三者数量必须相同
class Object
{

protected:
	string modelPath;						//模型路径
	int band;								//SH阶数
	vec3 albedo;							//物体反射率（采用数值形式，也可以采用贴图形式）

	ObjIndexType indexType;					//obj文件面索引方式

	AABB aabb;								//包围盒
public:


	vector<Point> pointsData;

	vector<unsigned> renderIndex;			//存放面上顶点的索引

	vector<Triangle> triangleFace;
	//vector<unsigned> normalsIndex;			//存放法线索引

public:
	Object(){}

	//读取obj文件模型，指定物体的基本反射率
	void Init(string fileName,vec3 _albedo,bool isTexture,ObjIndexType type);
	//将模型坐标规划到单位一下
	void ObjNormalize();

	//投影到球面调和函数上
	virtual void ProjectToSH(int mode,int band,int sampleNumber,int bounce){}		//参数为模式（三种）、SH阶数、采样数、反射次数（仅自反射时有用）
	//将系数写入到文件
	virtual void WriteToFile(string fileName){}

	//读取系数文件

public:
	//bool intersectTest(Ray& ray,int)

};