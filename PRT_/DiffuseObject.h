#pragma once
#include"Object.h"
#include"Sampler.h"
#include"Light.h"
#include<amp.h>
using namespace concurrency;

class DiffuseObject :public Object
{
public:
	//���߲���
	void ProjectToSH(int mode, int band, int sampleNumber, int bounce);			//ͶӰ��������ͺ���
	void WriteToFile(string fileName);												//��ϵ��д���ļ�

	//ʵʱ����
	void ReadFromDisk(string fileName);
	void InitColorBuffer(Light &light);



	//���߲���
	vector<vector<vec3>> transferFunc;						//Ԥ�����м���õĴ��亯��
	int band;

	//ʵʱ����
	vector<vector<vec3>> RtransferFunc;						//ʵʱ�д��ļ��ж�ȡ�Ĵ��亯��
	vector<vec3> colorBuffer;								//�洢�⺯��ϵ���봫�亯��ϵ����Ϻ�����ж������ɫ
private:
	//��ͬ��Ч��
	void DiffuseUnShadow(int _band, int samplerNumber,Sampler&sampler);				//����Ӱ
	void DiffuseShadow(int _band, int samplerNumber, Sampler&sampler);				//����Ӱ
};