#pragma once
#include"Scene.h"
#include<GLFW\glfw3.h>

const GLuint WIDTH = 1200, HEIGHT = 1000;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

MyScene scene;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

bool isRealTime = true;		//ָ����ǰ״̬�����߻���ʵʱ

ObjIndexType _type = ObjIndexType::Triangles;
string objFile = "OBJ//buddha.obj";
string objData = "ProcessData//buddhaData.txt";
int mode = 1;
bool _isTexture = true;
int _band = 4;
int _sampleNum = 4096;

string lightFile = "Image//Image1.png";
string lightData = "ProcessData//lightData.txt";

int main(void)
{
	if (isRealTime)
	{
		//��������
		GLFWwindow* window;

		//��ʼ��glfw
		if (!glfwInit())
			return -1;

		/* Create a windowed mode window and its OpenGL context */
		window = glfwCreateWindow(WIDTH, HEIGHT, "PRT", NULL, NULL);
		if (!window)
		{
			//��������ʣ�µĴ��ں��α꣬�ָ����б��޸ĵ�٤���ߣ����ͷ����������������Դ
			glfwTerminate();
			return -1;
		}

		/* �ú���ָ���ڵ�ǰ�����߳��ϵĴ�����Ⱦ����ΪOpenGL��OpenGL ES���� */
		glfwMakeContextCurrent(window);

		//ָ���¼�
		glfwSetKeyCallback(window, key_callback);			//�����¼�
															//glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

		scene.Init(objFile,objData,_type,_isTexture,lightData);


		/* Loop until the user closes the window */
		while (!glfwWindowShouldClose(window))
		{
			//����һ֡�ļ��
			float currentFrame = glfwGetTime();
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;



			//�������ºͻ���
			scene.Update();
			scene.Draw(_type);

			//����˫����
			glfwSwapBuffers(window);

			/* Poll for and process events */
			glfwPollEvents();
			//glfwWaitEvents();
		}

		glfwTerminate();
		return 0;
	}
	else
	{
		scene.PreProcess(objFile, objData,mode, _band, _sampleNum, _type, _isTexture, lightFile, lightData);
	}
	
}

void key_callback(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	float cameraSpeed = 5.0f*deltaTime;		//����һ������ƶ��ٶȣ�һ֡��ʱ����Ϊ��λ
	if (key == GLFW_KEY_W&&action == GLFW_REPEAT)
		scene.camera.Walk(cameraSpeed);
	if (key == GLFW_KEY_S&&action == GLFW_REPEAT)
		scene.camera.Walk(-cameraSpeed);
	if (key == GLFW_KEY_A&&action == GLFW_REPEAT)
		scene.camera.LRMove(-cameraSpeed);
	if (key == GLFW_KEY_D&&action == GLFW_REPEAT)
		scene.camera.LRMove(cameraSpeed);
	if (key == GLFW_KEY_Q&&action == GLFW_REPEAT)
		scene.camera.LRRotate(cameraSpeed);
	if (key == GLFW_KEY_E&&action == GLFW_REPEAT)
		scene.camera.LRRotate(-cameraSpeed);
}
