#ifndef IDFT2D_H
#define IDFT2D_H
#include <iostream>
#include <cmath>
using namespace std;
#define PI 3.1415926

////////////////////////////////////////////////////////
//程序名称：2维IDFT
//作者：    侯运廷
//Email：    houyunting@gmail.com
//License:    GPL V3
//程序版本：1.0
//日期：    2011,07,20
////////////////////////////////////////////////////////
//参数说明
//IDFTInRe:	IDFT输入实部
//IDFTInIm:	IDFT输入虚部
//IDFTOut:	IDFT输出
//M:		数据块的行数
//N:		数据块的列数
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
