#include "Camera.h"

MyCamera::MyCamera()
{
	lookDir = vec3(0.0f, 0.0f, -1.0f);
	lookRight = vec3(1.0f, 0.0f, 0.0f);
	lookUp = vec3(0.0f, 1.0f, 0.0f);
	eyePos = vec3(0.0, 0.0, 0.0);
}

void MyCamera::SetView()
{
	lookDir = normalize(lookAtPoint - eyePos);
	//lookAtPoint��eyepos����lookDir����
	view = lookAt(eyePos, lookAtPoint, up);
	//view *= rotate(mat4(1.0f), 45.0f, vec3(0.0, 1.0, 0.0));
}

void MyCamera::SetPro()
{
	pro = perspective(45.0f, ((float)1200) / (1000), 0.1f, 1000.0f);
}

void MyCamera::Walk(float dis)
{
	//��ȡ�۾�����ķ���
	lookDir = normalize(lookAtPoint - eyePos);

	eyePos += lookDir*vec3(dis);		//lookDir������ǰǰ���߶�ʱ��������Ĺ��ף���dis��˼ӵ�eyepos��
	lookAtPoint += lookDir*vec3(dis);
}

void MyCamera::LRMove(float dis)
{
	lookRight = normalize(cross(lookDir, lookUp));

	eyePos += lookRight*vec3(dis);
	lookAtPoint += lookRight*vec3(dis);
}

void MyCamera::LRRotate(float dis)
{
	lookDir = normalize(lookAtPoint - eyePos);
	float dist = length(lookAtPoint - eyePos);
	mat4 ro = rotate(mat4(1.0f), dis, vec3(0.0, 1.0f , 0.0));

	lookDir = (ro*vec4(lookDir, 1.0f));

	lookDir = normalize(lookDir);

	lookAtPoint = lookDir*dist;

}
