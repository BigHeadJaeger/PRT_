#include "Object.h"

void Object::Init(string fileName, vec3 _albedo, bool isTexture,ObjIndexType type)
{
	modelPath = fileName;
	albedo = _albedo;

	indexType = type;

	ifstream file;
	file.open(fileName);
	if (!file.is_open())
		cout << "��obj�ļ�ʧ��" << endl;

	string line, flag;				//һ�е����ݺ�һ���п�ͷ�ı�־��

	float x, y, z;					//��������
	float u, v;						//��������
	float nx, ny, nz;				//����������

	char temp;

	//���ϵ�������� ���㡢����������������
	unsigned indexV0, indexV1, indexV2, indexV3;
	unsigned indexN0, indexN1, indexN2, indexN3;
	unsigned indexT0, indexT1, indexT2, indexT3;

	//vector<float> vertices;
	//��ȡobjʱ������ʱ�洢
	vector<float> normals;
	vector<float> texcoords;

	//��ʼ��AABB��Χ��
	aabb.maxPos = vec3(float(-M_INFINITE), float(-M_INFINITE), float(-M_INFINITE));
	aabb.minPos = vec3(float(M_INFINITE), float(M_INFINITE), float(M_INFINITE));

	while (getline(file,line))
	{
		istringstream ist(line);
		ist >> flag;
		if (flag == "v")
		{
			ist >> x >> y >> z;

			if (x > aabb.maxPos.x)aabb.maxPos.x = x;
			if (y > aabb.maxPos.y)aabb.maxPos.y = y;
			if (z > aabb.maxPos.z)aabb.maxPos.z = z;

			if (x < aabb.minPos.x)aabb.minPos.x = x;
			if (y < aabb.minPos.y)aabb.minPos.y = y;
			if (z < aabb.minPos.z)aabb.minPos.z = z;

			//�˴��Ƚ�����λ�÷���pointsData���Ա�֤����λ�ð���obj�ļ����У�֮���ٸ��ݸ���������ͼ�������겹ȫ
			Point temp;
			temp.vertex = vec3(x, y, z);
			pointsData.push_back(temp);

			/*vertices.push_back(x);
			vertices.push_back(y);
			vertices.push_back(z);*/
		}
		else if (flag=="vt")
		{
			ist >> u >> v;
			texcoords.push_back(u);
			texcoords.push_back(v);
		}
		else if (flag == "vn")
		{
			ist >> nx >> ny >> nz;
			normals.push_back(nx);
			normals.push_back(ny);
			normals.push_back(nz);
		}
		else if (flag == "f")
		{
			if (type==ObjIndexType::Triangles)
			{
				//��Ϊ�󲿷�obj�ļ�����ÿ�����㶼��3������дһ�飬������ͨ�������ظ�����ͬһ����ֵ(ע�������Ǵ�1��ʼ��)
				if (isTexture)			//�����Ƿ�����������
				{
					ist >> indexV0 >> temp >> indexT0 >> temp >> indexN0
						>> indexV1 >> temp >> indexT1 >> temp >> indexN1
						>> indexV2 >> temp >> indexT2 >> temp >> indexN2;
					//��Ⱦʱ�õ���˳��
					renderIndex.push_back(indexV0 - 1);
					renderIndex.push_back(indexV1 - 1);
					renderIndex.push_back(indexV2 - 1);
					//�������������߶�Ӧ��֮ǰֻ���˶���λ�õ�pointsData��
					pointsData[indexV0 - 1].normal = vec3(normals[3 * (indexN0 - 1)], normals[3 * (indexN0 - 1) + 1], normals[3 * (indexN0 - 1) + 2]);
					pointsData[indexV1 - 1].normal = vec3(normals[3 * (indexN1 - 1)], normals[3 * (indexN1 - 1) + 1], normals[3 * (indexN1 - 1) + 2]);
					pointsData[indexV2 - 1].normal = vec3(normals[3 * (indexN2 - 1)], normals[3 * (indexN2 - 1) + 1], normals[3 * (indexN2 - 1) + 2]);
					//��д����
					pointsData[indexV0 - 1].texcoord = vec2(texcoords[2 * (indexT0 - 1)], texcoords[2 * (indexT0 - 1) + 1]);
					pointsData[indexV1 - 1].texcoord = vec2(texcoords[2 * (indexT1 - 1)], texcoords[2 * (indexT1 - 1) + 1]);
					pointsData[indexV2 - 1].texcoord = vec2(texcoords[2 * (indexT2 - 1)], texcoords[2 * (indexT2 - 1) + 1]);

				}
				else
				{
					ist >> indexV0 >> temp >> temp >> indexN0
						>> indexV1 >> temp >> temp >> indexN1
						>> indexV2 >> temp >> temp >> indexN2;

					//��Ⱦʱ�õ���˳��
					renderIndex.push_back(indexV0 - 1);
					renderIndex.push_back(indexV1 - 1);
					renderIndex.push_back(indexV2 - 1);
					//�������������߶�Ӧ��֮ǰֻ���˶���λ�õ�pointsData��
					pointsData[indexV0 - 1].normal = vec3(normals[3 * (indexN0 - 1)], normals[3 * (indexN0 - 1) + 1], normals[3 * (indexN0 - 1) + 2]);
					pointsData[indexV1 - 1].normal = vec3(normals[3 * (indexN1 - 1)], normals[3 * (indexN1 - 1) + 1], normals[3 * (indexN1 - 1) + 2]);
					pointsData[indexV2 - 1].normal = vec3(normals[3 * (indexN2 - 1)], normals[3 * (indexN2 - 1) + 1], normals[3 * (indexN2 - 1) + 2]);
				}

			}
			else if (type == ObjIndexType::Quad)
			{
				if (isTexture)			//�����Ƿ�����������
				{
					ist >> indexV0 >> temp >> indexT0 >> temp >> indexN0
						>> indexV1 >> temp >> indexT1 >> temp >> indexN1
						>> indexV2 >> temp >> indexT2 >> temp >> indexN2
						>> indexV3 >> temp >> indexT3 >> temp >> indexN3;

					renderIndex.push_back(indexV0 - 1);
					renderIndex.push_back(indexV1 - 1);
					renderIndex.push_back(indexV2 - 1);
					renderIndex.push_back(indexV3 - 1);

					//�������������߶�Ӧ��֮ǰֻ���˶���λ�õ�pointsData��
					pointsData[indexV0 - 1].normal = vec3(normals[3 * (indexN0 - 1)], normals[3 * (indexN0 - 1) + 1], normals[3 * (indexN0 - 1) + 2]);
					pointsData[indexV1 - 1].normal = vec3(normals[3 * (indexN1 - 1)], normals[3 * (indexN1 - 1) + 1], normals[3 * (indexN1 - 1) + 2]);
					pointsData[indexV2 - 1].normal = vec3(normals[3 * (indexN2 - 1)], normals[3 * (indexN2 - 1) + 1], normals[3 * (indexN2 - 1) + 2]);
					pointsData[indexV3 - 1].normal = vec3(normals[3 * (indexN3 - 1)], normals[3 * (indexN3 - 1) + 1], normals[3 * (indexN3 - 1) + 2]);

					//��д����
					pointsData[indexV0 - 1].texcoord = vec2(texcoords[2 * (indexT0 - 1)], texcoords[2 * (indexT0 - 1) + 1]);
					pointsData[indexV1 - 1].texcoord = vec2(texcoords[2 * (indexT1 - 1)], texcoords[2 * (indexT1 - 1) + 1]);
					pointsData[indexV2 - 1].texcoord = vec2(texcoords[2 * (indexT2 - 1)], texcoords[2 * (indexT2 - 1) + 1]);
					pointsData[indexV3 - 1].texcoord = vec2(texcoords[2 * (indexT3 - 1)], texcoords[2 * (indexT3 - 1) + 1]);
				}
				else
				{
					ist >> indexV0 >> temp >> temp >> indexN0
						>> indexV1 >> temp >> temp >> indexN1
						>> indexV2 >> temp >> temp >> indexN2
						>> indexV3 >> temp >> temp >> indexN3;

					renderIndex.push_back(indexV0 - 1);
					renderIndex.push_back(indexV1 - 1);
					renderIndex.push_back(indexV2 - 1);
					renderIndex.push_back(indexV3 - 1);

					//�������������߶�Ӧ��֮ǰֻ���˶���λ�õ�pointsData��
					pointsData[indexV0 - 1].normal = vec3(normals[3 * (indexN0 - 1)], normals[3 * (indexN0 - 1) + 1], normals[3 * (indexN0 - 1) + 2]);
					pointsData[indexV1 - 1].normal = vec3(normals[3 * (indexN1 - 1)], normals[3 * (indexN1 - 1) + 1], normals[3 * (indexN1 - 1) + 2]);
					pointsData[indexV2 - 1].normal = vec3(normals[3 * (indexN2 - 1)], normals[3 * (indexN2 - 1) + 1], normals[3 * (indexN2 - 1) + 2]);
					pointsData[indexV3 - 1].normal = vec3(normals[3 * (indexN3 - 1)], normals[3 * (indexN3 - 1) + 1], normals[3 * (indexN3 - 1) + 2]);

				}
			}
			
		}

	}

	file.close();

	ObjNormalize();
}

void Object::ObjNormalize()
{
	float X, Y, Z;
	X = max(fabs(aabb.maxPos.x), fabs(aabb.minPos.x));
	Y = max(fabs(aabb.maxPos.y), fabs(aabb.minPos.y));
	Z = max(fabs(aabb.maxPos.x), fabs(aabb.minPos.z));

	float result = 1.0f / max(X, max(Y, Z));

	for (int i = 0; i < pointsData.size(); i++)
	{
		pointsData[i].vertex *= result;
		//vertices[i] *= result;
	}
}
