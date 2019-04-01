#include "DiffuseObject.h"

void DiffuseObject::ProjectToSH(int mode, int band, int sampleNumber, int bounce)
{
	Sampler sampler((int)sqrt(sampleNumber));
	sampler.ComputeSH(band);

	if (mode == 1)			//��������Ӱ
	{
		DiffuseUnShadow(band, sampleNumber, sampler);
	}
	else if (mode == 2)		//��������Ӱ
	{
		DiffuseShadow(band, sampleNumber, sampler);
	}
	else if (mode == 3)		//������
	{

	}
}

void DiffuseObject::WriteToFile(string fileName)
{
	ofstream out(fileName);

	int band2 = band*band;
	int size = pointsData.size();

	out << pointsData.size() << endl;
	out << band << endl;

	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < band2; j++)
		{
			out << transferFunc[i][j].x << ' ' << transferFunc[i][j].y << ' ' << transferFunc[i][j].z << ' ';
		}
		cout << endl;
	}

	out.close();
}

void DiffuseObject::ReadFromDisk(string fileName)
{
	ifstream in(fileName);

	int size;			//�������Ŀ
	in >> size >> band;
	int band2 = band*band;

	for (int i = 0; i < size; i++)
	{
		vector<vec3> temp(band2, vec3(0, 0, 0));
		for (int j = 0; j < band2; j++)
		{
			in >> temp[j].x >> temp[j].y >> temp[j].z;
		}
		RtransferFunc.push_back(temp);
	}

	in.close();
}

void DiffuseObject::InitColorBuffer(Light & light)
{
	int band2 = band*band;
	int vertexNumber = pointsData.size();
	colorBuffer.clear();

	/*float temp = 0.1f;
	float temp2 = 0.2f;
	int flag = 0;*/

	for (int i = 0; i < vertexNumber; i++)
	{
		vec3 vertexColor(0, 0, 0);
		for (int j = 0; j < band2; j++)
		{
			vertexColor += RtransferFunc[i][j] * light.Rcoeffs[j];
		}

		colorBuffer.push_back(vertexColor);
	}
}

void DiffuseObject::DiffuseUnShadow(int _band, int samplerNumber, Sampler & sampler)
{
	band = _band;
	int band2 = band*band;
	int size = pointsData.size();				//

	//ָ��ϵ�����ϵĴ�С
	transferFunc.resize(size,vector<vec3>(band2, vec3(0.0, 0.0, 0.0)));

	int count = 0;

	/*array_view<Point, 1> p(pointsData.size(), pointsData);

	parallel_for_each(
		p.extent,
		[=](index<1> idx) restrict(amp)
	{
		vec3 normal = p[idx].normal;

		for (int j = 0; j < samplerNumber; j++)
		{
			float unTran;			//����Ӱ�еĴ��亯��
			

			unTran = dot(normal, sampler.samples[j].coord);

			//���С��0ֱ����һ��ѭ��������ִ�н��������ۼ�
			if (unTran <= 0)
				continue;

			//���忨�ػ����ۼӲ���
			for (int k = 0; k < band2; k++)
			{
				float shValue = sampler.samples[j].SHvalue[k];
				transferFunc[i][k] += shValue*albedo*unTran;
			}

		}
	}
	);*/


	//����ÿһ���������band2��ϵ��
#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
		//��ȡ��ǰ����ķ�������������Կ���ÿ�������band2��ϵ���Ĳ����Ҫ�뷨�����йأ���Ϊ���ж���ʹ�õ�����������ͬ�ģ�
		//int index = normalsIndex[i] * 3;

		//��ȡ��ǰ��ķ�����
		vec3 normal = pointsData[i].normal;

		/*float *result = new float[samplerNumber];
		float *x = new float[samplerNumber];
		float *y = new float[samplerNumber];
		float *z = new float[samplerNumber];

		for (int i = 0; i < samplerNumber; i++)
		{
			x[i] = sampler.samples[i].coord.x;
			y[i] = sampler.samples[i].coord.y;
			z[i] = sampler.samples[i].coord.z;
		}

		array_view<float, 1> coordx(samplerNumber, x);
		array_view<float, 1> coordy(samplerNumber, y);
		array_view<float, 1> coordz(samplerNumber, z);
		array_view<float, 1> res(samplerNumber, result);

		res.discard_data();

		parallel_for_each(
			res.extent,
			[=](index<1> idx) restrict(amp)
		{
			float unTran;			//����Ӱ�еĴ��亯��
			//unTran = glm::dot(normal, sam[idx].coord);

			unTran = normal.x*coordx[idx] + normal.y*coordy[idx] + normal.z*coordz[idx];

			//���С��0ֱ����һ��ѭ��������ִ�н��������ۼ�
			/*if (unTran <= 0)
				continue;

			res[idx] = unTran;

		}
		);

		res.synchronize();

		//���忨�ػ����ۼӲ���
		for (int j = 0; j < samplerNumber; j++)
		{
			if (result[j] <= 0)
				continue;
			for (int k = 0; k < band2; k++)
			{
				float shValue = sampler.samples[j].SHvalue[k];
				transferFunc[i][k] += shValue*albedo*result[j];
			}
		}

		delete result;
		delete x;
		delete y;
		delete z;*/

		for (int j = 0; j < samplerNumber; j++)
		{
			float unTran;			//����Ӱ�еĴ��亯��
			unTran = dot(normal, sampler.samples[j].coord);

			//���С��0ֱ����һ��ѭ��������ִ�н��������ۼ�
			if (unTran <= 0)
				continue;

			if (unTran >= 1.0f)
			{
				count++;
				cout << "����Ӱ���亯������" << " " << unTran << " " << count << endl;
				continue;
			}

			//���忨�ػ����ۼӲ���
			for (int k = 0; k < band2; k++)
			{
				float shValue = sampler.samples[j].SHvalue[k];
				transferFunc[i][k] += shValue*albedo*unTran;
			}

		}
	}



	float weight = 4.0f*(float)PI / samplerNumber;			//���忨�ػ��ֵ�Ȩ��

	//ÿ��ϵ����Ȩ�����
#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < band2; j++)
		{
			transferFunc[i][j] *= weight;
		}
	}
}

void DiffuseObject::DiffuseShadow(int _band, int samplerNumber, Sampler & sampler)
{
	band = _band;
	int band2 = band*band;
	int size = pointsData.size();				//

												//ָ��ϵ�����ϵĴ�С
	transferFunc.resize(size, vector<vec3>(band2, vec3(0.0, 0.0, 0.0)));

	int count = 0;

	//������������������
	if (indexType == ObjIndexType::Triangles)
	{
		int temp = 0;
		for (int i = 0; i < renderIndex.size(); i+=3)
		{
			vec3 p1 = pointsData[renderIndex[i]].vertex;
			vec3 p2 = pointsData[renderIndex[i+1]].vertex;
			vec3 p3 = pointsData[renderIndex[i+2]].vertex;
			
			Triangle tr(p1, p2, p3, temp);
			triangleFace.push_back(tr);
			temp++;
		}
	}
	else if(indexType == ObjIndexType::Quad)
	{
		int temp = 0;
		for (int i = 0; i < renderIndex.size(); i+=4)
		{
			vec3 p1 = pointsData[renderIndex[i]].vertex;
			vec3 p2 = pointsData[renderIndex[i + 1]].vertex;
			vec3 p3 = pointsData[renderIndex[i + 2]].vertex;
			vec3 p4 = pointsData[renderIndex[i + 3]].vertex;

			Triangle tr1(p1, p2, p3, temp);
			temp++;
			Triangle tr2(p2, p3, p4, temp);
			temp++;
			triangleFace.push_back(tr1);
			triangleFace.push_back(tr2);
		}
	}

	//����ÿһ���������band2��ϵ��
#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
		//��ȡ��ǰ����ķ�������������Կ���ÿ�������band2��ϵ���Ĳ����Ҫ�뷨�����йأ���Ϊ���ж���ʹ�õ�����������ͬ�ģ�
		//int index = normalsIndex[i] * 3;

		//��ȡ��ǰ��ķ�����
		vec3 normal = pointsData[i].normal;

		for (int j = 0; j < samplerNumber; j++)
		{
			float unTran;			//����Ӱ�еĴ��亯��
			unTran = dot(normal, sampler.samples[j].coord);

			//���С��0ֱ����һ��ѭ��������ִ�н��������ۼ�
			if (unTran <= 0)
				continue;

			vec3 tr = pointsData[i].vertex;
			vec3 dir = sampler.samples[j].coord;

			Ray testRay(tr, dir);

			bool isOcclusion = false;

			for (int i = 0; i < triangleFace.size(); i++)
			{
				isOcclusion = RayTriangle(testRay, triangleFace[i]);
				if (isOcclusion)
					break;
			}

			if (isOcclusion)
				continue;



			//���忨�ػ����ۼӲ���
			for (int k = 0; k < band2; k++)
			{
				float shValue = sampler.samples[j].SHvalue[k];
				transferFunc[i][k] += shValue*albedo*unTran;
			}

		}
	}



	float weight = 4.0f*(float)PI / samplerNumber;			//���忨�ػ��ֵ�Ȩ��

															//ÿ��ϵ����Ȩ�����
#pragma omp parallel for
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < band2; j++)
		{
			transferFunc[i][j] *= weight;
		}
	}
}
