#pragma once
#include"Object.h"
#include"Sampler.h"
#include"Light.h"
#include<amp.h>
using namespace concurrency;

class DiffuseObject :public Object
{
public:
	//离线部分
	void ProjectToSH(int mode, int band, int sampleNumber, int bounce);			//投影到球面调和函数
	void WriteToFile(string fileName);												//将系数写入文件

	//实时部分
	void ReadFromDisk(string fileName);
	void InitColorBuffer(Light &light);



	//离线部分
	vector<vector<vec3>> transferFunc;						//预处理中计算好的传输函数
	int band;

	//实时部分
	vector<vector<vec3>> RtransferFunc;						//实时中从文件中读取的传输函数
	vector<vec3> colorBuffer;								//存储光函数系数与传输函数系数结合后的所有顶点的颜色
private:
	//不同的效果
	void DiffuseUnShadow(int _band, int samplerNumber,Sampler&sampler);				//无阴影
	void DiffuseShadow(int _band, int samplerNumber, Sampler&sampler);				//有阴影
};