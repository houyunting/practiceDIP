#ifndef DFT2D_H
#define DFT2D_H
#include <iostream>
#include <cmath>
using namespace std;
#define PI 3.1415926

////////////////////////////////////////////////////////
//�������ƣ�2άDFT
//���ߣ�    ����͢
//Email��    houyunting@gmail.com
//License:    GPL V3
//����汾��1.0
//���ڣ�    2011,07,20
////////////////////////////////////////////////////////
//����˵��
//DFTIn:	DFT����
//DFTOutRe:	DFT���ʵ��
//DFTOutIm:	DFT����鲿
//M:		���ݿ������
//N:		���ݿ������
////////////////////////////////////////////////////////
template<class T>
int DFT2D(T * DFTIn, T*DFTOutRe, T * DFTOutIm, int M, int N)
{
	T TempRe = 0, TempIm = 0;
	for(T *ii = DFTIn, *ori = DFTOutRe, *oii = DFTOutIm; ii < DFTIn + M * N; ii += N, ori += N, oii += N)
	{
		for(T *ij = ii, *orj = ori, *oij = oii; ij < ii + N; ij++, orj++, oij++)
		{
			TempRe = 0;
			TempIm = 0;

			for(T *ik = DFTIn; ik < DFTIn + M * N; ik += N)
			{
				for(T *im = ik; im < ik + N; im++)
				{
					T u, x, v, y;
					u = (T)((ori - DFTOutRe) / N);
					x = (T)((ik - DFTIn) / N);
					v = (T)(orj - ori);
					y = (T)(im - ik);
					//cout << u << " " << x << " " << v << " " << y << endl;
					TempRe += (*im) * cos(2 * PI * ((u * x)/M + (v * y)/N)) / (M * N);
					TempIm += -(*im) * sin(2 * PI * ((u * x) / M + (v * y)/N)) / (M * N);
				}
			}

			*orj = TempRe;
			*oij = TempIm;
		}
	}

	return 0;
}

#endif
