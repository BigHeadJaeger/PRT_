#pragma once

#include"SphericalHarmonic.h"
#include<glm.hpp>
#include<vector>
#include<ctime>
#include<math.h>
#include<iostream>

using namespace std;
using namespace glm;

//�����ṹ��
struct Sample
{
	vec3 coord;			//���������������µ�x,y,z��ʾ
	vec2 angle;			//�������µĦȺͦյı�ʾ
	float *SHvalue;		//ÿ�������㶼��Ӧband2��SH

	Sample(vec3 c,vec2 a):coord(c),angle(a){}
};

//���в�������
class Sampler
{
public:
	Sampler(unsigned n);		//���ݸ��Ų�������ʼ��������
	void ComputeSH(int band);	//����������ͻ����Ľ�����ʼ��������SH

	float Random(int n)
	{
		return (rand() % (n + 1)) / (float)n;
	}

	vector<Sample> samples;		//��������
};
