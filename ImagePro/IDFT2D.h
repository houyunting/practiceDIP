#ifndef IDFT2D_H
#define IDFT2D_H
#include <iostream>
#include <cmath>
using namespace std;
#define PI 3.1415926

////////////////////////////////////////////////////////
//�������ƣ�2άIDFT
//���ߣ�    ����͢
//Email��    houyunting@gmail.com
//License:    GPL V3
//����汾��1.0
//���ڣ�    2011,07,20
////////////////////////////////////////////////////////
//����˵��
//IDFTInRe:	IDFT����ʵ��
//IDFTInIm:	IDFT�����鲿
//IDFTOut:	IDFT���
//M:		���ݿ������
//N:		���ݿ������
////////////////////////////////////////////////////////
template<class T>
int IDFT2D(T *IDFTInRe, T * IDFTInIm, T * IDFTOut, int M, int N)
{
	T Temp =0;
	for(T *oi = IDFTOut, *iri = IDFTInRe, *iii = IDFTInIm; iri < IDFTInRe + M * N; oi += N, iri += N, iii += N)
	{
		for(T *oj = oi, *irj = iri, *iij = iii; irj < iri + N; oj++, irj++, iij++)
		{
			Temp = 0;

			for(T *irk = IDFTInRe, *iik = IDFTInIm; irk < IDFTInRe + M * N; irk += N, iik += N)
			{
				for(T *irm = irk, *iim = iik; irm < irk + N; irm++, iim++)
				{
					T u, x, v, y;
					u = (T)((irk - IDFTInRe) / N);
					x = (T)((oi - IDFTOut) / N);
					v = (T)(irm - irk);
					y = (T)(oj - oi);
					//cout << u << " " << x << " " << v << " " << y << endl;
					Temp += (*irm) * cos(2 * PI * ((u * x)/M + (v * y)/N));
					Temp += -(*iim) * sin(2 * PI * ((u * x) / M + (v * y)/N));
				}
			}

			*oj = Temp;
		}
	}

	return 0;
}

#endif
