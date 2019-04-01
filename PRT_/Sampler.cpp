#include "Sampler.h"

Sampler::Sampler(unsigned n)
{
	srand((unsigned)time(NULL));		//��ϵͳʱ�������������

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			vec3 c;
			vec2 a;
			//�����������е�x��y����
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

			//���ݦȺͦ�ת��Ϊx��y��z��ʽ
			float theta2 = atan(z / sqrt(x*x + y*y));
			float phi2 = atan(y / x);
			//����������������ת�����������ЦȺͦյı�ʾ
			a.x = theta2;
			a.y = phi2;


			/*//����������������ת�����������ЦȺͦյı�ʾ
			a[0] = 2.0f*acos(sqrt(1 - x));
			a[1] = 2.0f*(float)PI*y;
			//���ݦȺͦ�ת��Ϊx��y��z��ʽ					��------------------------------��
			c[2] = sin(a.x)*cos(a.y);
			c[0]= sin(a.x)*cos(a.y);
			c[1]= cos(a.x);*/

			Sample S(c, a);
			samples.push_back(S);					//һ�����Եõ�n*n=sampleNumber��������
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
				int index = (l + 1)*l + m;			//������ʾ��ǰ����ĵڼ���SH
				samples[i].SHvalue[index] = SphericalTerm::SH(samples[i].angle.x, samples[i].angle.y, l, m);	//���ݲ���������Ӧ��SHֵ



				if (_isnan(samples[i].SHvalue[index]))
				{
					system("pause");
					std::cout << "SHֵΪ������." << std::endl;

				}

				if (fabs(samples[i].SHvalue[index]) > 1)
				{
					system("pause");
					std::cout << "SH��ֵ������1." << std::endl;

				}
			}
		}
	}
}
