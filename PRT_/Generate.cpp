#include "Generate.h"

void MyGeometryGenerator::CreateBox(float width, float height, float depth, MeshData & mesh)
{
	mesh.indices.clear();
	mesh.vertices.clear();

	mesh.indices.resize(36);
	mesh.vertices.resize(24);

	float halfW = width*0.5f;
	float halfH = height*0.5f;
	float halfD = depth*0.5f;

	//背面
	mesh.vertices[0].pos = vec3(-halfW, -halfH, -halfD);
	mesh.vertices[0].normal = vec3(0.f, 0.f, -1.f);
	mesh.vertices[0].tangent = vec3(1.f, 0.f, 0.f);
	mesh.vertices[0].tex = vec2(0.f, 1.f);
	mesh.vertices[1].pos = vec3(-halfW, halfH, -halfD);
	mesh.vertices[1].normal = vec3(0.f, 0.f, -1.f);
	mesh.vertices[1].tangent = vec3(1.f, 0.f, 0.f);
	mesh.vertices[1].tex = vec2(0.f, 0.f);
	mesh.vertices[2].pos = vec3(halfW, halfH, -halfD);
	mesh.vertices[2].normal = vec3(0.f, 0.f, -1.f);
	mesh.vertices[2].tangent = vec3(1.f, 0.f, 0.f);
	mesh.vertices[2].tex = vec2(1.f, 0.f);
	mesh.vertices[3].pos = vec3(halfW, -halfH, -halfD);
	mesh.vertices[3].normal = vec3(0.f, 0.f, -1.f);
	mesh.vertices[3].tangent = vec3(1.f, 0.f, 0.f);
	mesh.vertices[3].tex = vec2(1.f, 1.f);
	//左侧面
	mesh.vertices[4].pos = vec3(-halfW, -halfH, halfD);
	mesh.vertices[4].normal = vec3(-1.f, 0.f, 0.f);
	mesh.vertices[4].tangent = vec3(0.f, 0.f, -1.f);
	mesh.vertices[4].tex = vec2(0.f, 1.f);
	mesh.vertices[5].pos = vec3(-halfW, halfH, halfD);
	mesh.vertices[5].normal = vec3(-1.f, 0.f, 0.f);
	mesh.vertices[5].tangent = vec3(0.f, 0.f, -1.f);
	mesh.vertices[5].tex = vec2(0.f, 0.f);
	mesh.vertices[6].pos = vec3(-halfW, halfH, -halfD);
	mesh.vertices[6].normal = vec3(-1.f, 0.f, 0.f);
	mesh.vertices[6].tangent = vec3(0.f, 0.f, -1.f);
	mesh.vertices[6].tex = vec2(1.f, 0.f);
	mesh.vertices[7].pos = vec3(-halfW, -halfH, -halfD);
	mesh.vertices[7].normal = vec3(-1.f, 0.f, 0.f);
	mesh.vertices[7].tangent = vec3(0.f, 0.f, -1.f);
	mesh.vertices[7].tex = vec2(1.f, 1.f);
	//正面
	mesh.vertices[8].pos = vec3(halfW, -halfH, halfD);
	mesh.vertices[8].normal = vec3(0.f, 0.f, 1.f);
	mesh.vertices[8].tangent = vec3(-1.f, 0.f, 0.f);
	mesh.vertices[8].tex = vec2(0.f, 1.f);
	mesh.vertices[9].pos = vec3(halfW, halfH, halfD);
	mesh.vertices[9].normal = vec3(0.f, 0.f, 1.f);
	mesh.vertices[9].tangent = vec3(-1.f, 0.f, 0.f);
	mesh.vertices[9].tex = vec2(0.f, 0.f);
	mesh.vertices[10].pos = vec3(-halfW, halfH, halfD);
	mesh.vertices[10].normal = vec3(0.f, 0.f, 1.f);
	mesh.vertices[10].tangent = vec3(-1.f, 0.f, 0.f);
	mesh.vertices[10].tex = vec2(1.f, 0.f);
	mesh.vertices[11].pos = vec3(-halfW, -halfH, halfD);
	mesh.vertices[11].normal = vec3(0.f, 0.f, 1.f);
	mesh.vertices[11].tangent = vec3(-1.f, 0.f, 0.f);
	mesh.vertices[11].tex = vec2(1.f, 1.f);
	//右侧面
	mesh.vertices[12].pos = vec3(halfW, -halfH, -halfD);
	mesh.vertices[12].normal = vec3(1.f, 0.f, 0.f);
	mesh.vertices[12].tangent = vec3(0.f, 0.f, 1.f);
	mesh.vertices[12].tex = vec2(0.f, 1.f);
	mesh.vertices[13].pos = vec3(halfW, halfH, -halfD);
	mesh.vertices[13].normal = vec3(1.f, 0.f, 0.f);
	mesh.vertices[13].tangent = vec3(0.f, 0.f, 1.f);
	mesh.vertices[13].tex = vec2(0.f, 0.f);
	mesh.vertices[14].pos = vec3(halfW, halfH, halfD);
	mesh.vertices[14].normal = vec3(1.f, 0.f, 0.f);
	mesh.vertices[14].tangent = vec3(0.f, 0.f, 1.f);
	mesh.vertices[14].tex = vec2(1.f, 0.f);
	mesh.vertices[15].pos = vec3(halfW, -halfH, halfD);
	mesh.vertices[15].normal = vec3(1.f, 0.f, 0.f);
	mesh.vertices[15].tangent = vec3(0.f, 0.f, 1.f);
	mesh.vertices[15].tex = vec2(1.f, 1.f);
	//上面
	mesh.vertices[16].pos = vec3(-halfW, halfH, -halfD);
	mesh.vertices[16].normal = vec3(0.f, 1.f, 0.f);
	mesh.vertices[16].tangent = vec3(1.f, 0.f, 0.f);
	mesh.vertices[16].tex = vec2(0.f, 1.f);
	mesh.vertices[17].pos = vec3(-halfW, halfH, halfD);
	mesh.vertices[17].normal = vec3(0.f, 1.f, 0.f);
	mesh.vertices[17].tangent = vec3(1.f, 0.f, 0.f);
	mesh.vertices[17].tex = vec2(0.f, 0.f);
	mesh.vertices[18].pos = vec3(halfW, halfH, halfD);
	mesh.vertices[18].normal = vec3(0.f, 1.f, 0.f);
	mesh.vertices[18].tangent = vec3(1.f, 0.f, 0.f);
	mesh.vertices[18].tex = vec2(1.f, 0.f);
	mesh.vertices[19].pos = vec3(halfW, halfH, -halfD);
	mesh.vertices[19].normal = vec3(0.f, 1.f, 0.f);
	mesh.vertices[19].tangent = vec3(1.f, 0.f, 0.f);
	mesh.vertices[19].tex = vec2(1.f, 1.f);
	//底面
	mesh.vertices[20].pos = vec3(-halfW, -halfH, halfD);
	mesh.vertices[20].normal = vec3(0.f, -1.f, 0.f);
	mesh.vertices[20].tangent = vec3(1.f, 0.f, 0.f);
	mesh.vertices[20].tex = vec2(0.f, 1.f);
	mesh.vertices[21].pos = vec3(-halfW, -halfH, -halfD);
	mesh.vertices[21].normal = vec3(0.f, -1.f, 0.f);
	mesh.vertices[21].tangent = vec3(1.f, 0.f, 0.f);
	mesh.vertices[21].tex = vec2(0.f, 0.f);
	mesh.vertices[22].pos = vec3(halfW, -halfH, -halfD);
	mesh.vertices[22].normal = vec3(0.f, -1.f, 0.f);
	mesh.vertices[22].tangent = vec3(1.f, 0.f, 0.f);
	mesh.vertices[22].tex = vec2(1.f, 0.f);
	mesh.vertices[23].pos = vec3(halfW, -halfH, halfD);
	mesh.vertices[23].normal = vec3(0.f, -1.f, 0.f);
	mesh.vertices[23].tangent = vec3(1.f, 0.f, 0.f);
	mesh.vertices[23].tex = vec2(1.f, 1.f);

	//构建索引
	mesh.indices[0] = 0;
	mesh.indices[1] = 1;
	mesh.indices[2] = 2;
	mesh.indices[3] = 0;
	mesh.indices[4] = 2;
	mesh.indices[5] = 3;

	mesh.indices[6] = 4;
	mesh.indices[7] = 5;
	mesh.indices[8] = 6;
	mesh.indices[9] = 4;
	mesh.indices[10] = 6;
	mesh.indices[11] = 7;

	mesh.indices[12] = 8;
	mesh.indices[13] = 9;
	mesh.indices[14] = 10;
	mesh.indices[15] = 8;
	mesh.indices[16] = 10;
	mesh.indices[17] = 11;

	mesh.indices[18] = 12;
	mesh.indices[19] = 13;
	mesh.indices[20] = 14;
	mesh.indices[21] = 12;
	mesh.indices[22] = 14;
	mesh.indices[23] = 15;

	mesh.indices[24] = 16;
	mesh.indices[25] = 17;
	mesh.indices[26] = 18;
	mesh.indices[27] = 16;
	mesh.indices[28] = 18;
	mesh.indices[29] = 19;

	mesh.indices[30] = 20;
	mesh.indices[31] = 21;
	mesh.indices[32] = 22;
	mesh.indices[33] = 20;
	mesh.indices[34] = 22;
	mesh.indices[35] = 23;
}

/*void MyGeometryGenerator::CreateSphere(int X_SEGMENTS, int Y_SEGMENTS, MeshData &mesh,float r)
{
	const float PI = 3.14159265359;
	for (unsigned int y = 0; y <= Y_SEGMENTS; ++y)
	{
		for (unsigned int x = 0; x <= X_SEGMENTS; ++x)
		{
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI)*r;
			float yPos = std::cos(ySegment * PI)*r;
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI)*r;

			Vertex temp;
			temp.pos = vec3(xPos, yPos, zPos);
			temp.normal = vec3(xPos, yPos, zPos);
			temp.tex = vec2(xSegment, ySegment);
			mesh.vertices.push_back(temp);
		}
	}


	bool oddRow = false;
	for (int y = 0; y < Y_SEGMENTS; ++y)
	{
		if (!oddRow) // even rows: y == 0, y == 2; and so on
		{
			for (int x = 0; x <= X_SEGMENTS; ++x)
			{
				mesh.indices.push_back(y       * (X_SEGMENTS + 1) + x);
				mesh.indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
			}
		}
		else
		{
			for (int x = X_SEGMENTS; x >= 0; --x)
			{
				mesh.indices.push_back((y + 1) * (X_SEGMENTS + 1) + x);
				mesh.indices.push_back(y       * (X_SEGMENTS + 1) + x);
			}
		}
		oddRow = !oddRow;
	}
}*/


void MyGeometryGenerator::CreateSphere2(float radius, int slice, int stack, MeshData &mesh)
{
	float PI = 3.14159265359;

	mesh.vertices.clear();
	mesh.indices.clear();

	int vertsPerRow = slice + 1;
	int nRows = stack - 1;

	int nVerts = vertsPerRow * nRows + 2;
	int nIndices = (nRows - 1)*slice * 6 + slice * 6;

	mesh.vertices.resize(nVerts);
	mesh.indices.resize(nIndices);

	for (int i = 1; i <= nRows; ++i)
	{
		float phy = PI * i / stack;
		float tmpRadius = radius * sin(phy);
		for (int j = 0; j < vertsPerRow; ++j)
		{
			float theta = 2* PI * j / slice;
			int index = (i - 1)*vertsPerRow + j;

			float x = tmpRadius*cos(theta);
			float y = radius*cos(phy);
			float z = tmpRadius*sin(theta);

			//位置坐标
			mesh.vertices[index].pos = vec3(x, y, z);
			//法线
			vec3 N = vec3(x, y, z);
			mesh.vertices[index].normal = N;
			//XMStoreFloat3(&mesh.vertices[index].normal, XMVector3Normalize(N));
			//切线
			/*XMVECTOR T = XMVectorSet(-sin(theta), 0.f, cos(theta), 0.f);
			XMStoreFloat3(&mesh.vertices[index].tangent, XMVector3Normalize(T));*/
			//纹理坐标
			mesh.vertices[index].tex = vec2(j*1.f / slice, i*1.f / stack);
		}
	}

	int size = vertsPerRow * nRows;
	//添加顶部和底部两个顶点信息
	mesh.vertices[size].pos = vec3(0.f, radius, 0.f);
	mesh.vertices[size].normal = vec3(0.f, 1.f, 0.f);
	mesh.vertices[size].tangent = vec3(1.f, 0.f, 0.f);
	mesh.vertices[size].tex = vec2(0.f, 0.f);

	mesh.vertices[size + 1].pos = vec3(0.f, -radius, 0.f);
	mesh.vertices[size + 1].normal = vec3(0.f, -1.f, 0.f);
	mesh.vertices[size + 1].tangent = vec3(1.f, 0.f, 0.f);
	mesh.vertices[size + 1].tex = vec2(0.f, 1.f);

	int tmp(0);
	int start1 = 0;
	int start2 = mesh.vertices.size() - vertsPerRow - 2;
	int top = size;
	int bottom = size + 1;
	for (int i = 0; i < slice; ++i)
	{
		mesh.indices[tmp] = top;
		mesh.indices[tmp + 1] = start1 + i + 1;
		mesh.indices[tmp + 2] = start1 + i;

		tmp += 3;
	}

	for (int i = 0; i < slice; ++i)
	{
		mesh.indices[tmp] = bottom;
		mesh.indices[tmp + 1] = start2 + i;
		mesh.indices[tmp + 2] = start2 + i + 1;

		tmp += 3;
	}

	for (int i = 0; i < nRows - 1; ++i)
	{
		for (int j = 0; j < slice; ++j)
		{
			mesh.indices[tmp] = i * vertsPerRow + j;
			mesh.indices[tmp + 1] = (i + 1) * vertsPerRow + j + 1;
			mesh.indices[tmp + 2] = (i + 1) * vertsPerRow + j;
			mesh.indices[tmp + 3] = i * vertsPerRow + j;
			mesh.indices[tmp + 4] = i * vertsPerRow + j + 1;
			mesh.indices[tmp + 5] = (i + 1) * vertsPerRow + j + 1;

			tmp += 6;
		}
	}
}
