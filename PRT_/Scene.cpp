#pragma once
#include "Scene.h"

void MyScene::Init(string objPath, string objDataPath, ObjIndexType type, bool isTexture, string lightDataPath)
{
	//��ʼ��glew
	glewInit();
	//����shader����
	char text1[] = "prt.v";
	char text2[] = "prt.f";
	p1.SetShader(text1, text2);
	//p1.SetShader("test.v", "test.f");
	//Ԥ�������ݳ�ʼ��
	DataInit(objPath, objDataPath, type, isTexture, lightDataPath);

	//����VAO��VBO
	SetBuffers();


	//ָ�������ʼλ��
	camera.eyePos = vec3(0, 0, 2);
	camera.lookAtPoint = vec3(0, 0, 0);
	camera.up = vec3(0, 1, 0);



	//ָ������PBR����






	//ָ���������������������Ҫ��ָ������������ת�����������ߣ�



	buddhaWorld = translate(mat4(1.0f), vec3(0.0f, 0.0f, 0.0f));

}

void MyScene::Update()
{
	//�����ӽǾ���
	camera.SetView();
	
	//����ͶӰ����
	camera.SetPro();

	//����������������ӽǾ���ͶӰ��������ÿһ�������worldviewproj(��������˶����ȼ������������������ת����)
	buddhaWorldViewProj = camera.pro*camera.view*buddhaWorld;

	//�������-----
	//��������Ϣ����shader�У������Ҫ���㷴��⣬����Ҫ��eyePos����shader��
}

void MyScene::Draw(ObjIndexType type)
{


	//����ÿһ������ʱ���Ƚ����еĸ������������ؾ��󣬲��ʵ���Ϣ����shader��,�˴�����һЩ��ʶ��
	GLuint SworldViewProj;			//��������worldViewProj�ı�־
	//GLuint Sworld, SworldInvTranspose;

	//����,��������������գ�����Ч���Ŀ�����blend�� cull֮��ģ�
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_CULL_FACE);					//��ά����Ҫ���������޳�
	//glFrontFace(GL_CW);
	//glCullFace(GL_FRONT);

	glUseProgram(p1.p);						//������ɫ������

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
	//ģ��Ԥ����
	dsBuddha.Init(objPath, vec3(0.15f, 0.15f, 0.15f), isTexture, type);
	dsBuddha.ProjectToSH(mode, band, sampNumber,1);
	dsBuddha.WriteToFile(objDataPath);

	//����Ԥ����
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
