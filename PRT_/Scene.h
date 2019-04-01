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
	//各种场景信息（相机、材质、灯光、各种物体的各种矩阵）

	//mesh object
	mat4x4 buddhaWorld;					//世界矩阵
	mat4x4 buddhaWorldViewProj;			//最终坐标转换矩阵
	//mat4x4 buddhaWorldInvTranspose;
	DiffuseObject dsBuddha;


	Light HDRLight;

public:
	//相机
	MyCamera camera;


	//---------------------------------------------------------------------------------

private:
	//VAO、VBO(buffer),以及需要传给shader的数据的location

	GLuint dsBuddhaVAO;
	GLuint dsBuddhaVertexBuffer;
	GLuint dsBuddhaIndexBuffer;

	//---------------------------------------------------------------------------------



	//shader程序
	ShaderProgram p1;

public:
	void Init(string objPath, string objDataPath, ObjIndexType type, bool isTexture, string lightPath);			//初始化各种信息
	void Update();			//需要动画时，计算各种矩阵（暂时不传入shader中）
	void Draw(ObjIndexType type);			//绘制场景

	void PreProcess(string objPath, string objDataPath, int mode,int band, int sampNumber, ObjIndexType type, bool isTexture, string lightPath, string lightDataPath);		//预计算部分
private:
	void SetBuffers();		//设置VAO和VBO
	void DataInit(string objPath, string objDataPath, ObjIndexType type, bool isTexture, string lightPath);		//实时部分用来初始化模型并根据预处理的数据计算每个顶点的颜色
	//void SetTexture();		//生成纹理并绑定数据
};