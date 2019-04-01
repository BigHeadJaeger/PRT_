//用来对光函数进行预计算的存储以及实时计算的读取
#pragma once

#include<iostream>
#include<string>
#include<fstream>

#include"HDRLoader.h"
#include"Sampler.h"

#include<SOIL.h>




using namespace std;
using namespace glm;

enum LightType
{
	Probe,
	CubeMap
};
//光照采用贴图的形式，可以有cubemap型（六张）的也可以是probe型的（一张）
class Light
{
public:
	//离线部分
	Light(){}
	//Light(string _path, LightType _type, int _band);		//初始化
	void Init(string _path, LightType _type, int _band);	//初始化
	void Process(int sampleNumber, bool useImage);			//系数的获取，光照可以来自光照贴图，也可以来自简单光照
	vec3 ProbeColor(vec3 dir);								//根据样本方向从贴图上获得相应的颜色值
	void WriteToFile(string fileName);

	//实时部分
	void ReadFromDisk(string fileName);

private:
	//离线预计算部分
	string path;							//光照贴图的路径
	LightType lightType;					//光照的类型

	int band;								//SH阶数
	vector<vec3> coeffs;					//经过计算得到的系数，因为光照贴图设物体处于中心，所有顶点的光函数通用一组系数

	/*HDRLoaderResult hdrResult;				//存储HDR贴图像素值
	int width;								//HDR图的宽
	int height;								//HDR图的高*/

	unsigned char* pImage;
	int width;
	int height;

	//BMPImage image;

public:
	//实时部分

	vector<vec3> Rcoeffs;					//保存读取出来的系数

};