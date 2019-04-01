#pragma once
#include "Scene.h"

void MyScene::Init(string objPath, string objDataPath, ObjIndexType type, bool isTexture, string lightDataPath)
{
	//初始化glew
	glewInit();
	//创建shader程序
	char text1[] = "prt.v";
	char text2[] = "prt.f";
	p1.SetShader(text1, text2);
	//p1.SetShader("test.v", "test.f");
	//预处理数据初始化
	DataInit(objPath, objDataPath, type, isTexture, lightDataPath);

	//设置VAO、VBO
	SetBuffers();


	//指定相机初始位置
	camera.eyePos = vec3(0, 0, 2);
	camera.lookAtPoint = vec3(0, 0, 0);
	camera.up = vec3(0, 1, 0);



	//指定物体PBR材质






	//指定个物体的世界矩阵（如果需要则指定世界矩阵的逆转矩阵，用做法线）



	buddhaWorld = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));

}

void MyScene::Update()
{
	//计算视角矩阵
	camera.SetView();
	
	//计算投影矩阵
	camera.SetPro();

	//根据物体世界矩阵、视角矩阵、投影矩阵计算出每一个物体的worldviewproj(如果物体运动则先计算物体的世界矩阵和逆转矩阵)
	buddhaWorldViewProj = camera.pro*camera.view*buddhaWorld;

	//光照相关-----
	//将光照信息传入shader中，如果需要计算反射光，则需要将eyePos传入shader中
}

void MyScene::Draw(ObjIndexType type)
{


	//绘制每一个物体时，先将类中的该物体的所有相关矩阵，材质等信息传入shader中,此处声明一些标识符
	GLuint SworldViewProj;			//用做链接worldViewProj的标志
	//GLuint Sworld, SworldInvTranspose;

	//绘制,包含缓冲区的清空，各种效果的开启（blend、 cull之类的）
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);					//三维物体要开启背面剔除
	//glFrontFace(GL_CW);
	//glCullFace(GL_FRONT);

	glUseProgram(p1.p);						//启用着色器程序

										//buddha
	glBindVertexArray(dsBuddhaVAO);

	SworldViewProj = glGetUniformLocation(p1.p, "worldViewProj");
	glUniformMatrix4fv(SworldViewProj, 1, GL_FALSE, value_ptr(buddhaWorldViewProj));
	
	if (type==ObjIndexType::Quad)
	{
		glDrawElements(GL_QUADS, dsBuddha.renderIndex.size(), GL_UNSIGNED_INT, 0);

	}
	else if (type == ObjIndexType::Triangles)
	{
		glDrawElements(GL_TRIANGLES, dsBuddha.renderIndex.size(), GL_UNSIGNED_INT, 0);
	}
	glBindVertexArray(0);



}

void MyScene::PreProcess(string objPath,string objDataPath,int mode,int band,int sampNumber,ObjIndexType type,bool isTexture,string lightPath,string lightDataPath)
{
	//模型预处理
	dsBuddha.Init(objPath, vec3(0.15f, 0.15f, 0.15f), isTexture, type);
	dsBuddha.ProjectToSH(mode, band, sampNumber,1);
	dsBuddha.WriteToFile(objDataPath);

	//光照预处理
	HDRLight.Init(lightPath, LightType::Probe, band);
	HDRLight.Process(sampNumber, true);
	HDRLight.WriteToFile(lightDataPath);
}

void MyScene::SetBuffers()
{			
											//buddha
	glGenVertexArrays(1, &dsBuddhaVAO);
	glBindVertexArray(dsBuddhaVAO);

	vector<float> buddhaVertexData;
	int size = dsBuddha.pointsData.size();

	for (int i = 0; i < size; i++)
	{
		buddhaVertexData.push_back(dsBuddha.pointsData[i].vertex.x);
		buddhaVertexData.push_back(dsBuddha.pointsData[i].vertex.y);
		buddhaVertexData.push_back(dsBuddha.pointsData[i].vertex.z);
		buddhaVertexData.push_back(dsBuddha.colorBuffer[i].x);
		buddhaVertexData.push_back(dsBuddha.colorBuffer[i].y);
		buddhaVertexData.push_back(dsBuddha.colorBuffer[i].z);
	}

	glGenBuffers(1, &dsBuddhaVertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER,dsBuddhaVertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, buddhaVertexData.size() * sizeof(float), &buddhaVertexData[0], GL_STATIC_DRAW);

	glGenBuffers(1, &dsBuddhaIndexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dsBuddhaIndexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, dsBuddha.renderIndex.size() * sizeof(unsigned), &dsBuddha.renderIndex[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	glBindVertexArray(0);

}

void MyScene::DataInit(string objPath,string objDataPath,ObjIndexType type,bool isTexture,string lightDataPath)
{
	HDRLight.ReadFromDisk(lightDataPath);

	dsBuddha.Init(objPath, vec3(0.15f, 0.15f, 0.15f), isTexture, type);
	dsBuddha.ReadFromDisk(objDataPath);
	dsBuddha.InitColorBuffer(HDRLight);


}
