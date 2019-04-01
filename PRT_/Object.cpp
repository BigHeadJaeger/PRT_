#include "Object.h"

void Object::Init(string fileName, vec3 _albedo, bool isTexture,ObjIndexType type)
{
	modelPath = fileName;
	albedo = _albedo;

	indexType = type;

	ifstream file;
	file.open(fileName);
	if (!file.is_open())
		cout << "打开obj文件失败" << endl;

	string line, flag;				//一行的内容和一行中开头的标志符

	float x, y, z;					//顶点坐标
	float u, v;						//纹理坐标
	float nx, ny, nz;				//法向量坐标

	char temp;

	//面上的三个点的 顶点、法向量、纹理索引
	unsigned indexV0, indexV1, indexV2, indexV3;
	unsigned indexN0, indexN1, indexN2, indexN3;
	unsigned indexT0, indexT1, indexT2, indexT3;

	//vector<float> vertices;
	//读取obj时进行临时存储
	vector<float> normals;
	vector<float> texcoords;

	//初始化AABB包围盒
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

			//此处先将顶点位置放入pointsData，以保证顶点位置按照obj文件排列，之后再根据各索引将贴图法线坐标补全
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
				//因为大部分obj文件不是每个顶点都将3个属性写一遍，多数是通过索引重复利用同一组数值(注：索引是从1开始的)
				if (isTexture)			//区分是否有纹理坐标
				{
					ist >> indexV0 >> temp >> indexT0 >> temp >> indexN0
						>> indexV1 >> temp >> indexT1 >> temp >> indexN1
						>> indexV2 >> temp >> indexT2 >> temp >> indexN2;
					//渲染时用到的顺序
					renderIndex.push_back(indexV0 - 1);
					renderIndex.push_back(indexV1 - 1);
					renderIndex.push_back(indexV2 - 1);
					//根据索引将法线对应到之前只填了顶点位置的pointsData中
					pointsData[indexV0 - 1].normal = vec3(normals[3 * (indexN0 - 1)], normals[3 * (indexN0 - 1) + 1], normals[3 * (indexN0 - 1) + 2]);
					pointsData[indexV1 - 1].normal = vec3(normals[3 * (indexN1 - 1)], normals[3 * (indexN1 - 1) + 1], normals[3 * (indexN1 - 1) + 2]);
					pointsData[indexV2 - 1].normal = vec3(normals[3 * (indexN2 - 1)], normals[3 * (indexN2 - 1) + 1], normals[3 * (indexN2 - 1) + 2]);
					//填写纹理
					pointsData[indexV0 - 1].texcoord = vec2(texcoords[2 * (indexT0 - 1)], texcoords[2 * (indexT0 - 1) + 1]);
					pointsData[indexV1 - 1].texcoord = vec2(texcoords[2 * (indexT1 - 1)], texcoords[2 * (indexT1 - 1) + 1]);
					pointsData[indexV2 - 1].texcoord = vec2(texcoords[2 * (indexT2 - 1)], texcoords[2 * (indexT2 - 1) + 1]);

				}
				else
				{
					ist >> indexV0 >> temp >> temp >> indexN0
						>> indexV1 >> temp >> temp >> indexN1
						>> indexV2 >> temp >> temp >> indexN2;

					//渲染时用到的顺序
					renderIndex.push_back(indexV0 - 1);
					renderIndex.push_back(indexV1 - 1);
					renderIndex.push_back(indexV2 - 1);
					//根据索引将法线对应到之前只填了顶点位置的pointsData中
					pointsData[indexV0 - 1].normal = vec3(normals[3 * (indexN0 - 1)], normals[3 * (indexN0 - 1) + 1], normals[3 * (indexN0 - 1) + 2]);
					pointsData[indexV1 - 1].normal = vec3(normals[3 * (indexN1 - 1)], normals[3 * (indexN1 - 1) + 1], normals[3 * (indexN1 - 1) + 2]);
					pointsData[indexV2 - 1].normal = vec3(normals[3 * (indexN2 - 1)], normals[3 * (indexN2 - 1) + 1], normals[3 * (indexN2 - 1) + 2]);
				}

			}
			else if (type == ObjIndexType::Quad)
			{
				if (isTexture)			//区分是否有纹理坐标
				{
					ist >> indexV0 >> temp >> indexT0 >> temp >> indexN0
						>> indexV1 >> temp >> indexT1 >> temp >> indexN1
						>> indexV2 >> temp >> indexT2 >> temp >> indexN2
						>> indexV3 >> temp >> indexT3 >> temp >> indexN3;

					renderIndex.push_back(indexV0 - 1);
					renderIndex.push_back(indexV1 - 1);
					renderIndex.push_back(indexV2 - 1);
					renderIndex.push_back(indexV3 - 1);

					//根据索引将法线对应到之前只填了顶点位置的pointsData中
					pointsData[indexV0 - 1].normal = vec3(normals[3 * (indexN0 - 1)], normals[3 * (indexN0 - 1) + 1], normals[3 * (indexN0 - 1) + 2]);
					pointsData[indexV1 - 1].normal = vec3(normals[3 * (indexN1 - 1)], normals[3 * (indexN1 - 1) + 1], normals[3 * (indexN1 - 1) + 2]);
					pointsData[indexV2 - 1].normal = vec3(normals[3 * (indexN2 - 1)], normals[3 * (indexN2 - 1) + 1], normals[3 * (indexN2 - 1) + 2]);
					pointsData[indexV3 - 1].normal = vec3(normals[3 * (indexN3 - 1)], normals[3 * (indexN3 - 1) + 1], normals[3 * (indexN3 - 1) + 2]);

					//填写纹理
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

					//根据索引将法线对应到之前只填了顶点位置的pointsData中
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
