#pragma once
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
#include<SOIL.h>

#include"Generate.h"
#include"Program.h"
#include"Camera.h"

#include"DiffuseObject.h"
using namespace glm;
class MyScene
{
private:
	//���ֳ�����Ϣ����������ʡ��ƹ⡢��������ĸ��־���

	//mesh object
	mat4x4 buddhaWorld;					//�������
	mat4x4 buddhaWorldViewProj;			//��������ת������
	//mat4x4 buddhaWorldInvTranspose;
	DiffuseObject dsBuddha;


	Light HDRLight;

public:
	//���
	MyCamera camera;


	//---------------------------------------------------------------------------------

private:
	//VAO��VBO(buffer),�Լ���Ҫ����shader�����ݵ�location

	GLuint dsBuddhaVAO;
	GLuint dsBuddhaVertexBuffer;
	GLuint dsBuddhaIndexBuffer;

	//---------------------------------------------------------------------------------



	//shader����
	ShaderProgram p1;

public:
	void Init(string objPath, string objDataPath, ObjIndexType type, bool isTexture, string lightPath);			//��ʼ��������Ϣ
	void Update();			//��Ҫ����ʱ��������־�����ʱ������shader�У�
	void Draw(ObjIndexType type);			//���Ƴ���

	void PreProcess(string objPath, string objDataPath, int mode,int band, int sampNumber, ObjIndexType type, bool isTexture, string lightPath, string lightDataPath);		//Ԥ���㲿��
private:
	void SetBuffers();		//����VAO��VBO
	void DataInit(string objPath, string objDataPath, ObjIndexType type, bool isTexture, string lightPath);		//ʵʱ����������ʼ��ģ�Ͳ�����Ԥ��������ݼ���ÿ���������ɫ
	//void SetTexture();		//��������������
};