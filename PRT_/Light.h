//�����Թ⺯������Ԥ����Ĵ洢�Լ�ʵʱ����Ķ�ȡ
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
//���ղ�����ͼ����ʽ��������cubemap�ͣ����ţ���Ҳ������probe�͵ģ�һ�ţ�
class Light
{
public:
	//���߲���
	Light(){}
	//Light(string _path, LightType _type, int _band);		//��ʼ��
	void Init(string _path, LightType _type, int _band);	//��ʼ��
	void Process(int sampleNumber, bool useImage);			//ϵ���Ļ�ȡ�����տ������Թ�����ͼ��Ҳ�������Լ򵥹���
	vec3 ProbeColor(vec3 dir);								//���������������ͼ�ϻ����Ӧ����ɫֵ
	void WriteToFile(string fileName);

	//ʵʱ����
	void ReadFromDisk(string fileName);

private:
	//����Ԥ���㲿��
	string path;							//������ͼ��·��
	LightType lightType;					//���յ�����

	int band;								//SH����
	vector<vec3> coeffs;					//��������õ���ϵ������Ϊ������ͼ�����崦�����ģ����ж���Ĺ⺯��ͨ��һ��ϵ��

	/*HDRLoaderResult hdrResult;				//�洢HDR��ͼ����ֵ
	int width;								//HDRͼ�Ŀ�
	int height;								//HDRͼ�ĸ�*/

	unsigned char* pImage;
	int width;
	int height;

	//BMPImage image;

public:
	//ʵʱ����

	vector<vec3> Rcoeffs;					//�����ȡ������ϵ��

};