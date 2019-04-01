#include "Light.h"

/*Light::Light(string _path, LightType _type, int _band)
{
	path = _path;
	lightType = _type;
	band = _band;

	HDRLoader loader;
	loader.load(path.c_str(), hdrResult);

	width = hdrResult.width;
	height = hdrResult.height;

}*/

void Light::Init(string _path, LightType _type, int _band)
{
	path = _path;
	lightType = _type;
	band = _band;

	/*HDRLoader loader;
	loader.load(path.c_str(), hdrResult);

	width = hdrResult.width;
	height = hdrResult.height;*/

	pImage = SOIL_load_image(_path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);

	//ReadFile("right.bmp");

	//image.open(path.c_str());

}

void Light::Process(int sampleNumber, bool useImage)
{
	cout << "Light Pre Process" << endl;
	int band2 = band*band;								
	int sqrNum = (int)sqrt(sampleNumber);				//分层抽样范围

	float weight = 4.0f * PI / sampleNumber;			//权值

	Sampler sampler(sqrNum);
	sampler.ComputeSH(band);

	coeffs.clear();
	coeffs.resize(band2, vec3(0, 0, 0));

	//对所有样本进行蒙洛卡特积分，得出最终的band2个系数
	for (int i = 0; i < sampleNumber; i++)
	{
		vec3 dir = sampler.samples[i].coord;
		for (int j = 0; j < band2; j++)
		{
			float sh = sampler.samples[i].SHvalue[j];
			if (useImage)
			{
				coeffs[j] += sh*ProbeColor(dir);
			}
			else
			{
				//采用直接光照
				coeffs[j] += sh*vec3(1.0);
			}
		}
	}

	//为每一个系数乘上权值
	for (int i = 0; i < band2; i++)
	{
		coeffs[i] *= weight;
	}
}

vec3 Light::ProbeColor(vec3 dir)			//根据样点所提供的方向转换到贴图上的一个颜色值
{
	float d = sqrt(dir.x * dir.x + dir.y * dir.y);

	float r;
	if (fabs(d) <= ZERO)
	{
		r = 0.0f;
	}
	else
	{
		r = (1.0f / (2.0f * (float)PI)) * acos(dir.z) / d;
	}

	vec2 texCoord;
	texCoord.x = 0.5f + dir.x * r;
	texCoord.y = 0.5f + dir.y * r;

	glm::ivec2 pixelCoord;
	pixelCoord.x = (int)(width * texCoord.x);
	pixelCoord.y = (int)(height * (1.0f - texCoord.y));

	//int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;
	int index = pixelCoord.y * width + pixelCoord.x;

	int offset = 3 * index;

	vec3 test((float)pImage[offset] / 255, (float)pImage[offset + 1] / 255, (float)pImage[offset + 2] / 255);

	return test;
}

void Light::WriteToFile(string fileName)
{
	ofstream out(fileName, ofstream::binary);			//二进制形式输出到文件
	out.write((char*)(&band), sizeof(int));
	int band2 = band*band;
	for (int i = 0; i < band2; i++)
	{
		out.write((char*)(&coeffs[i].x), sizeof(float));
		out.write((char*)(&coeffs[i].y), sizeof(float));
		out.write((char*)(&coeffs[i].z), sizeof(float));
	}
	out.close();

	cout << "Light Coeffs write end" << endl;
}

void Light::ReadFromDisk(string fileName)
{
	ifstream in(fileName, ifstream::binary);
	in.read((char*)(&band), sizeof(int));
	int band2 = band*band;
	for (int i = 0; i < band2; i++)
	{
		vec3 temp(0, 0, 0);
		in.read((char*)(&temp.x), sizeof(float));
		in.read((char*)(&temp.y), sizeof(float));
		in.read((char*)(&temp.z), sizeof(float));
		Rcoeffs.push_back(temp);
	}

	in.close();
}

