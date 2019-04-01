#pragma once
#include<vector>
#include<glm.hpp>

using namespace glm;

class MyGeometryGenerator
{
private:
	MyGeometryGenerator() {}
public:
	//����ģʽ
	static MyGeometryGenerator* GetInstance()
	{
		static MyGeometryGenerator instance;
		return &instance;
	}

	struct Vertex
	{
		vec3 pos;
		vec3 normal;
		vec3 tangent;
		vec2 tex;

		Vertex() {}
		Vertex(const vec3 _pos, vec3 _normal, vec3 _tangent, vec3 _tex) :
			pos(_pos), normal(_normal), tangent(_tangent), tex(_tex) {}
	};

	struct MeshData
	{
		std::vector<Vertex> vertices;
		std::vector<short> indices;
	};

	void CreateBox(float width, float height, float depth, MeshData &mesh);

	void CreateSphere(int X_SEGMENTS, int Y_SEGMENTS, MeshData &mesh, float r);

	//widthΪx����heightΪz����mΪ���ϵĸ�������nΪ���ϵĸ����� 
	void CreateGrid(float width, float height, int m, int n, MeshData&mesh);

	void CreateSphere2(float radius, int slice, int stack, MeshData &mesh);
};
