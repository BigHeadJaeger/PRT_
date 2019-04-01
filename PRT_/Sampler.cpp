#include "Sampler.h"

Sampler::Sampler(unsigned n)
{
	srand((unsigned)time(NULL));		//按系统时间设置随机种子

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			vec3 c;
			vec2 a;
			//采样正方形中的x，y坐标
			//float x = ((float)i + Random(n*n)) / (float)n;
			//float y = ((float)j + Random(n*n)) / (float)n;
			float r2;
			float u;
			float v;
			while (true)
			{
				u = 2.0*rand() / RAND_MAX - 1;
				v = 2.0*rand() / RAND_MAX - 1;

				r2 = u*u + v*v;
				if (r2 < 1)
					break;
			}


			float x = 2 * u*sqrt(1 - r2);
			float y = 2 * v*sqrt(1 - r2);
			float z = 1 - 2 * r2;

			float temp = sqrt(x*x + y*y + z*z);

			c.x = x*temp;
			c.y = y*temp;
			c.z = z*temp;

			/*float theta = acos(z / 1.0);
			float phi = atan(y / x);*/

			//根据θ和φ转换为x，y，z形式
			float theta2 = atan(z / sqrt(x*x + y*y));
			float phi2 = atan(y / x);
			//将采样正方形坐标转换到球坐标中θ和φ的表示
			a.x = theta2;
			a.y = phi2;


			/*//将采样正方形坐标转换到球坐标中θ和φ的表示
			a[0] = 2.0f*acos(sqrt(1 - x));
			a[1] = 2.0f*(float)PI*y;
			//根据θ和φ转换为x，y，z形式					（------------------------------）
			c[2] = sin(a.x)*cos(a.y);
			c[0]= sin(a.x)*cos(a.y);
			c[1]= cos(a.x);*/

			Sample S(c, a);
			samples.push_back(S);					//一共可以得到n*n=sampleNumber个样本点
		}
	}
}

void Sampler::ComputeSH(int band)
{
	int band2 = band*band;
	for (int i = 0; i < samples.size(); i++)
	{
		samples[i].SHvalue = new float[band2];
		for (int l = 0; l < band; l++)
		{
			for (int m = -l; m <= l; m++)
			{
				int index = (l + 1)*l + m;			//用来表示当前样点的第几个SH
				samples[i].SHvalue[index] = SphericalTerm::SH(samples[i].angle.x, samples[i].angle.y, l, m);	//根据参数计算相应的SH值



				if (_isnan(samples[i].SHvalue[index]))
				{
					system("pause");
					std::cout << "SH值为非数字." << std::endl;

				}

				if (fabs(samples[i].SHvalue[index]) > 1)
				{
					system("pause");
					std::cout << "SH的值超过了1." << std::endl;

				}
			}
		}
	}
}
