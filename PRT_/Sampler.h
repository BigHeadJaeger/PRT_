#pragma once

#include"SphericalHarmonic.h"
#include<glm.hpp>
#include<vector>
#include<ctime>
#include<math.h>
#include<iostream>

using namespace std;
using namespace glm;

//样本结构体
struct Sample
{
	vec3 coord;			//样本点在球坐标下的x,y,z表示
	vec2 angle;			//球坐标下的θ和φ的表示
	float *SHvalue;		//每个样本点都对应band2个SH

	Sample(vec3 c,vec2 a):coord(c),angle(a){}
};

//进行采样的类
class Sampler
{
public:
	Sampler(unsigned n);		//根据根号采样数初始化样本点
	void ComputeSH(int band);	//根据球面调和基函的阶数初始化样本的SH

	float Random(int n)
	{
		return (rand() % (n + 1)) / (float)n;
	}

	vector<Sample> samples;		//样本集合
};
