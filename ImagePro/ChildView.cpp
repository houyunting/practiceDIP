// ChildView.cpp : CChildView 类的实现
//

#include "stdafx.h"
#include "ImagePro.h"
#include "ChildView.h"
#include "DFT2D.h"
#include "IDFT2D.h"
#include <cmath>
#define DISTANCE 20

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView

CChildView::CChildView()
: ImageNameOrg(_T(""))
, IsGray(false)
, DFTRe(NULL)
, DFTIm(NULL)
{
	IsGray = false;
	ImageSizeFlag = SIZE_ORG;
}

CChildView::~CChildView()
{
	free(DFTRe);
	DFTRe = 0;
	free(DFTIm);
	DFTIm = 0;
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_FILE_OPEN, &CChildView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CChildView::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, &CChildView::OnFileSaveAs)
	ON_COMMAND(ID_IMG_SIZE_ORG, &CChildView::OnImgSizeOrg)
	ON_COMMAND(ID_IMG_SIZE_HALF, &CChildView::OnImgSizeHalf)
	ON_COMMAND(ID_IMG_SIZE_DOUBLE, &CChildView::OnImgSizeDouble)
	ON_COMMAND(ID_IMG_COLOR_GRAY, &CChildView::OnImgColorGray)
	ON_COMMAND(ID_IMG_COLOR_BINARY, &CChildView::OnImgColorBinary)
	ON_COMMAND(ID_SPATIAL_ENHANCEMANT_NEGATIVE, &CChildView::OnSpatialEnhancemantNegative)
	ON_COMMAND(ID_SPATIAL_ENHANCEMANT_HISTOGRAM, &CChildView::OnSpatialEnhancemantHistogram)
	ON_COMMAND(ID_SPATIAL_ENHANCEMANT_HISTOGRAM_EQUALIZATION, &CChildView::OnSpatialEnhancemantHistogramEqualization)
	ON_COMMAND(ID_SPATIAL_ENHANCEMANT_AVERAGING_FILTER, &CChildView::OnSpatialEnhancemantAveragingFilter)
	ON_COMMAND(ID_SPATIAL_ENHANCEMANT_MEDIAN_FILTER, &CChildView::OnSpatialEnhancemantMedianFilter)
	ON_COMMAND(ID_SPATIAL_ENHANCEMANT_SHARPEN_LAPLACION, &CChildView::OnSpatialEnhancemantSharpenLaplacion)
	ON_COMMAND(ID_FREQUENCY_ENHANCEMENT_DFT, &CChildView::OnFrequencyEnhancementDft)
	ON_COMMAND(ID_FREQUENCY_ENHANCEMENT_IDFT, &CChildView::OnFrequencyEnhancementIdft)
	ON_COMMAND(ID_FREQUENCY_ENHANCEMENT_SMOOTH_IDEAL, &CChildView::OnFrequencyEnhancementSmoothIdeal)
	ON_COMMAND(ID_FREQUENCY_ENHANCEMENT_SHARPEN_IDEAL, &CChildView::OnFrequencyEnhancementSharpenIdeal)
	ON_COMMAND(ID_IMG_SIZE_QUADRUPLE, &CChildView::OnImgSizeQuadruple)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE, &CChildView::OnUpdateFileSave)
	ON_UPDATE_COMMAND_UI(ID_FILE_SAVE_AS, &CChildView::OnUpdateFileSaveAs)
	ON_UPDATE_COMMAND_UI(ID_IMG_SIZE_HALF, &CChildView::OnUpdateImgSizeHalf)
	ON_UPDATE_COMMAND_UI(ID_IMG_SIZE_ORG, &CChildView::OnUpdateImgSizeOrg)
	ON_UPDATE_COMMAND_UI(ID_IMG_SIZE_DOUBLE, &CChildView::OnUpdateImgSizeDouble)
	ON_UPDATE_COMMAND_UI(ID_IMG_SIZE_QUADRUPLE, &CChildView::OnUpdateImgSizeQuadruple)
	ON_UPDATE_COMMAND_UI(ID_IMG_COLOR_GRAY, &CChildView::OnUpdateImgColorGray)
	ON_UPDATE_COMMAND_UI(ID_IMG_COLOR_BINARY, &CChildView::OnUpdateImgColorBinary)
	ON_UPDATE_COMMAND_UI(ID_SPATIAL_ENHANCEMANT_NEGATIVE, &CChildView::OnUpdateSpatialEnhancemantNegative)
	ON_UPDATE_COMMAND_UI(ID_SPATIAL_ENHANCEMANT_HISTOGRAM, &CChildView::OnUpdateSpatialEnhancemantHistogram)
	ON_UPDATE_COMMAND_UI(ID_SPATIAL_ENHANCEMANT_HISTOGRAM_EQUALIZATION, &CChildView::OnUpdateSpatialEnhancemantHistogramEqualization)
	ON_UPDATE_COMMAND_UI(ID_SPATIAL_ENHANCEMANT_AVERAGING_FILTER, &CChildView::OnUpdateSpatialEnhancemantAveragingFilter)
	ON_UPDATE_COMMAND_UI(ID_SPATIAL_ENHANCEMANT_MEDIAN_FILTER, &CChildView::OnUpdateSpatialEnhancemantMedianFilter)
	ON_UPDATE_COMMAND_UI(ID_SPATIAL_ENHANCEMANT_SHARPEN_LAPLACION, &CChildView::OnUpdateSpatialEnhancemantSharpenLaplacion)
	ON_UPDATE_COMMAND_UI(ID_FREQUENCY_ENHANCEMENT_DFT, &CChildView::OnUpdateFrequencyEnhancementDft)
	ON_UPDATE_COMMAND_UI(ID_FREQUENCY_ENHANCEMENT_IDFT, &CChildView::OnUpdateFrequencyEnhancementIdft)
	ON_UPDATE_COMMAND_UI(ID_FREQUENCY_ENHANCEMENT_SMOOTH_IDEAL, &CChildView::OnUpdateFrequencyEnhancementSmoothIdeal)
	ON_UPDATE_COMMAND_UI(ID_FREQUENCY_ENHANCEMENT_SHARPEN_IDEAL, &CChildView::OnUpdateFrequencyEnhancementSharpenIdeal)
END_MESSAGE_MAP()



// CChildView 消息处理程序

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);
	return TRUE;
}

void CChildView::OnPaint() 
{
	CPaintDC dc(this); // 用于绘制的设备上下文
	
	// TODO: 在此处添加消息处理程序代码
	if(!ImageOrg.IsNull())
	{
		switch(ImageSizeFlag)
		{
		case SIZE_ORG:
			AdjustWindowSize();
			ImageOrg.Draw(dc.m_hDC,0,0,ImageOrg.GetWidth(),ImageOrg.GetHeight(),0,0,ImageOrg.GetWidth(),ImageOrg.GetHeight());
		break;
		case SIZE_HALF:
			AdjustWindowSize();
			ImageOrg.StretchBlt(dc,0,0,ImageOrg.GetWidth()/2,ImageOrg.GetHeight()/2,SRCCOPY);
		break;
		case SIZE_DOUBLE:
			AdjustWindowSize();
			ImageOrg.StretchBlt(dc,0,0,ImageOrg.GetWidth()*2,ImageOrg.GetHeight()*2,SRCCOPY);
		break;
		case SIZE_QUADRUPLE:
			AdjustWindowSize();
			ImageOrg.StretchBlt(dc,0,0,ImageOrg.GetWidth()*4,ImageOrg.GetHeight()*4,SRCCOPY);
		break;
		default:
		break;
		}
	}
	// 不要为绘制消息而调用 CWnd::OnPaint()
}

void CChildView::AdjustWindowSize(void)
{
	//根据图片的大小，设置窗口的大小
	//client 的 rect 的参考点是本窗口的左上角
	CRect org_window_rect, org_client_rect;
	GetParentFrame()->GetWindowRect(&org_window_rect);
	GetClientRect(&org_client_rect);

	ImageSize.SetSize(ImageOrg.GetWidth(), ImageOrg.GetHeight());

	CSize size;
	switch(ImageSizeFlag)
	{
	case SIZE_ORG:
		size.cx = (org_window_rect.right - org_window_rect.left - (org_client_rect.right - org_client_rect.left)) + ImageSize.cx;
		size.cy = org_client_rect.top - org_window_rect.top +  org_window_rect.bottom - org_client_rect.bottom + ImageSize.cy;
	break;
	case SIZE_HALF:
		size.cx = (org_window_rect.right - org_window_rect.left - (org_client_rect.right - org_client_rect.left)) + ImageSize.cx/2;
		size.cy = org_client_rect.top - org_window_rect.top +  org_window_rect.bottom - org_client_rect.bottom + ImageSize.cy/2;
	break;
	case SIZE_DOUBLE:
		size.cx = (org_window_rect.right - org_window_rect.left - (org_client_rect.right - org_client_rect.left)) + ImageSize.cx*2;
		size.cy = org_client_rect.top - org_window_rect.top +  org_window_rect.bottom - org_client_rect.bottom + ImageSize.cy*2;
	break;
	case SIZE_QUADRUPLE:
		size.cx = (org_window_rect.right - org_window_rect.left - (org_client_rect.right - org_client_rect.left)) + ImageSize.cx*4;
		size.cy = org_client_rect.top - org_window_rect.top +  org_window_rect.bottom - org_client_rect.bottom + ImageSize.cy*4;
	break;
	default:
	break;
	}

	if(! ((ImageSize.cx < 512) && (ImageSize.cy < 512)))  
	{
		GetParentFrame()->SetWindowPos(&GetParentFrame()->wndTop,0,0,size.cx,size.cy,SWP_NOMOVE);
	}
}

void CChildView::OnFileOpen()
{
	// TODO: Add your command handler code here
	//CString filter(_T("JPG (*.jpg)|*.jpg|PNG (*.png)|*.png|BMP (*.bmp)|*.bmp| All Files (*.*)|*.*||"));
	CString filter(_T("JPG (*.jpg)|*.jpg|PNG (*.png)|*.png|BMP (*.bmp)|*.bmp| JPG(*.jpg) PNG(*.png) GIF(*.gif) BMP(*.bmp) | *.jpg;*.png;*.gif;*.bmp|All Files (*.*)|*.*||"));
	CFileDialog dlg(TRUE,0,0,4|2,filter);

	if(dlg.DoModal() == IDOK)
	{
		try
		{
			ImageOrg.Destroy();
			ImageOrg.Load(dlg.GetPathName());
			ImageNameOrg = dlg.GetPathName();
		}
		catch(CException *e)
		{
			e->ReportError();
			e->Delete();
		}
		
		AdjustWindowSize();
		IsGray = false;

		Invalidate();
	}	
}

void CChildView::OnFileSave()
{
	// TODO: Add your command handler code here
	ImageOrg.Save(ImageNameOrg);
}

void CChildView::OnFileSaveAs()
{
	// TODO: Add your command handler code here
	if(ImageOrg.IsNull())
	{
		AfxMessageBox(_T("无图片需要保存"));
		return;
	}

	CString filter(_T("JPG (*.jpg)|*.jpg|PNG (*.png)|*.png|BMP (*.bmp)|*.bmp|GIF (*.gif)|*.gif||"));
	CFileDialog dlg(FALSE,0,0,4|2,filter);

	if(dlg.DoModal() == IDOK)
	{
		CString file_name = dlg.GetPathName();

		switch(dlg.m_ofn.nFilterIndex)
		{
		case 1:
			file_name += ".jpg";
		break;
		case 2:
			file_name += ".png";
		break;
		case 3:
			file_name += ".bmp";
		break;
		case 4:
			file_name += ".gif";
		break;
		default:
		break;
		}

		try
		{
			ImageOrg.Save(file_name);
			ImageNameOrg = file_name;
		}
		catch(CException *e)
		{
			e->ReportError();
			e->Delete();
		}
	}
}

void CChildView::OnImgSizeOrg()
{
	// TODO: Add your command handler code here
	ImageSizeFlag = SIZE_ORG;
	Invalidate();
}

void CChildView::OnImgSizeHalf()
{
	// TODO: Add your command handler code here
	ImageSizeFlag = SIZE_HALF;
	Invalidate();
}

void CChildView::OnImgSizeDouble()
{
	// TODO: Add your command handler code here
	ImageSizeFlag = SIZE_DOUBLE;
	Invalidate();
}

void CChildView::OnImgSizeQuadruple()
{
	// TODO: Add your command handler code here
	ImageSizeFlag = SIZE_QUADRUPLE;
	Invalidate();
}

void CChildView::OnImgColorGray()
{
	// TODO: Add your command handler code here
	COLORREF color, gray_color;
	int gray;

	for(int x = 0; x < ImageSize.cx; x++)
	{
		for(int y = 0; y < ImageSize.cy; y++)
		{
			color = ImageOrg.GetPixel(x, y);
			gray = ((color >> 16) + ((color & 0x0000FFFF) >> 8) + (color & 0x000000FF)) / 3;
			gray_color = RGB(gray, gray, gray);
			ImageOrg.SetPixel(x, y, gray_color);
		}

		Invalidate(0);
		UpdateWindow();
	}
	
	IsGray = true;
	Invalidate();
}

void CChildView::OnImgColorBinary()
{
	// TODO: Add your command handler code here
	COLORREF color, gray_color;
	int gray;

	if(IsGray)
	{
		for(int x = 0; x < ImageSize.cx; x++)
		{
			for(int y = 0; y < ImageSize.cy; y++)
			{
				color = ImageOrg.GetPixel(x, y);
				(GetRValue(color) > 127) ? ImageOrg.SetPixel(x, y, RGB(255, 255, 255)) : ImageOrg.SetPixel(x, y, RGB(0, 0, 0));
			}

			Invalidate(0);
			UpdateWindow();
		}
	}
	else
	{
		for(int x = 0; x < ImageOrg.GetWidth(); x++)
		{
			for(int y = 0; y < ImageOrg.GetHeight(); y++)
			{
				color = ImageOrg.GetPixel(x, y);
				gray = ((color >> 16) + ((color & 0x0000FFFF) >> 8) + (color & 0x000000FF)) / 3;
				gray_color = RGB(gray, gray, gray);
				(GetRValue(gray_color) > 127) ? ImageOrg.SetPixel(x, y, RGB(255, 255, 255)) : ImageOrg.SetPixel(x, y, RGB(0, 0, 0));
			}

			Invalidate(0);
			UpdateWindow();
		}
	}

	Invalidate();
}

void CChildView::OnSpatialEnhancemantNegative()
{
	// TODO: Add your command handler code here
	COLORREF color, neg_color;
	int red, green, blue;
	for(int x = 0; x < ImageSize.cx; x++)
	{
		for(int y = 0; y < ImageSize.cy; y++)
		{
			color = ImageOrg.GetPixel(x, y);

			blue = (255 - (color >> 16));
			green = (255 - ((color & 0x0000FFFF) >> 8));
			red = (255 - (color & 0x000000FF));
			neg_color = RGB(red, green, blue);

			ImageOrg.SetPixel(x, y, neg_color);
		}

		Invalidate(0);
		UpdateWindow();
	}
	
	Invalidate();
}

void CChildView::OnSpatialEnhancemantHistogram()
{
	// TODO: Add your command handler code here

	unsigned int histogram[3][256];
	memset(histogram,0,sizeof(histogram));
	COLORREF color;

	for(int x = 0; x < ImageSize.cx; x++)
	{
		for(int y = 0; y < ImageSize.cy; y++)
		{
			color = ImageOrg.GetPixel(x, y);
			//b
			histogram[0][(color >> 16)] += 1;
			//g
			histogram[1][((color & 0x0000FFFF) >> 8)] += 1;
			//r
			histogram[2][(color & 0x000000FF)] += 1;
		}
	}

	//归一化 + 在左上角画直方图
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 256; j++)
		{
			//直方图大小为256X200
			histogram[i][j] = (int)((histogram[i][j] / (double)(ImageSize.cx * ImageSize.cy)) * 4000);
		}
	}

	CClientDC dc(this);
	CPen *pOldPen;

	//b
	CPen bPen(PS_SOLID, 1, RGB(0,0,255));
	pOldPen = dc.SelectObject(&bPen);
	for(int j = 0; j < 256; j++)
	{
		dc.MoveTo(j, 200);
		dc.LineTo(j, 200 - histogram[0][j]);
	}
	//g
	CPen gPen(PS_SOLID, 1, RGB(0,255,0));
	dc.SelectObject(&gPen);
	for(int j = 0; j < 256; j++)
	{
		dc.MoveTo(j, 200);
		dc.LineTo(j, 200 - histogram[1][j]);
	}
	//r
	CPen rPen(PS_SOLID, 1, RGB(255,0,0));
	dc.SelectObject(&rPen);
	for(int j = 0; j < 256; j++)
	{
		dc.MoveTo(j, 200);
		dc.LineTo(j, 200 - histogram[2][j]);
	} 
	dc.SelectObject(pOldPen);
}

void CChildView::OnSpatialEnhancemantHistogramEqualization()
{
	// TODO: Add your command handler code here
	unsigned int histogram[3][256];
	memset(histogram,0,sizeof(histogram));
	COLORREF color;
	CClientDC dc(this);

	for(int x = 0; x < ImageSize.cx; x++)
	{
		for(int y = 0; y < ImageSize.cy; y++)
		{
			color = ImageOrg.GetPixel(x, y);
			//b
			histogram[0][(color >> 16)] += 1;
			//g
			histogram[1][((color & 0x0000FFFF) >> 8)] += 1;
			//r
			histogram[2][(color & 0x000000FF)] += 1;
		}
	}

	//均衡化
	unsigned int equalization_histogram[3][256];
	memset(equalization_histogram,0,sizeof(equalization_histogram));
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 256; j++)
		{
			for(int k = 0; k <= j; k++)
			{
				equalization_histogram[i][j] += histogram[i][k];
			}	 
		}
	}

	int red, green, blue;
	unsigned int pixal_number = ImageSize.cx * ImageSize.cy;

	for(int x = 0; x < ImageSize.cx; x++)
	{
		for(int y = 0; y < ImageSize.cy; y++)
		{
			color = ImageOrg.GetPixel(x, y);

			blue = (int)((equalization_histogram[0][(color >> 16)] * 255) / (float)pixal_number);
			green = (int)((equalization_histogram[1][((color & 0x0000FFFF) >> 8)]  * 255) / (float)pixal_number);
			red = (int)((equalization_histogram[2][(color & 0x000000FF)] * 255) / (float)pixal_number);

			ImageOrg.SetPixel(x, y, RGB(red,green,blue));
		}

		Invalidate(0);
		UpdateWindow();

		dc.MoveTo(x, 0);
		dc.LineTo(x, ImageSize.cy);
	}

	//显示均衡化后的图片
	Invalidate();

	//画均衡化后的直方图
	memset(histogram,0,sizeof(histogram));

	for(int x = 0; x < ImageSize.cx; x++)
	{
		for(int y = 0; y < ImageSize.cy; y++)
		{
			color = ImageOrg.GetPixel(x, y);
			//b
			histogram[0][(color >> 16)] += 1;
			//g
			histogram[1][((color & 0x0000FFFF) >> 8)] += 1;
			//r
			histogram[2][(color & 0x000000FF)] += 1;
		}
	}

	//归一化 + 在左上角画均衡化后的直方图
	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 256; j++)
		{
			//直方图大小为256X200
			histogram[i][j] = (int)((histogram[i][j] / (double)(ImageSize.cx * ImageSize.cy)) * 4000);
		}
	}

	
	CPen *pOldPen;

	//b
	CPen bPen(PS_SOLID, 1, RGB(0,0,255));
	pOldPen = dc.SelectObject(&bPen);
	for(int j = 0; j < 256; j++)
	{
		dc.MoveTo(j, 200);
		dc.LineTo(j, 200 - histogram[0][j]);
	}
	//g
	CPen gPen(PS_SOLID, 1, RGB(0,255,0));
	dc.SelectObject(&gPen);
	for(int j = 0; j < 256; j++)
	{
		dc.MoveTo(j, 200);
		dc.LineTo(j, 200 - histogram[1][j]);
	}
	//r
	CPen rPen(PS_SOLID, 1, RGB(255,0,0));
	dc.SelectObject(&rPen);
	for(int j = 0; j < 256; j++)
	{
		dc.MoveTo(j, 200);
		dc.LineTo(j, 200 - histogram[2][j]);
	} 
	/*
	//画变换函数
	//b
	pOldPen = dc.SelectObject(&bPen);
	for(int j = 0; j < 256; j++)
	{
		blue = (int)((equalization_histogram[0][(color >> 16)] * 4000) / (float)pixal_number);	
		dc.MoveTo(j, 400 - blue);
		dc.LineTo(j, 400 - blue - 2);
	}
	//g
	dc.SelectObject(&gPen);
	for(int j = 0; j < 256; j++)
	{
		green = (int)((equalization_histogram[1][((color & 0x0000FFFF) >> 8)]  * 40000) / (float)pixal_number);
		dc.MoveTo(j, 400 - green);
		dc.LineTo(j, 400 - green - 2);
	}
	//r
	dc.SelectObject(&rPen);
	for(int j = 0; j < 256; j++)
	{
		red = (int)((equalization_histogram[2][(color & 0x000000FF)] * 4000) / (float)pixal_number);
		dc.MoveTo(j, 400 - red);
		dc.LineTo(j, 400 - red - 2);
	} 
	*/
	
	dc.SelectObject(pOldPen);
}

void CChildView::OnSpatialEnhancemantAveragingFilter()
{
	// TODO: Add your command handler code here
	COLORREF color;
	int red = 0, green = 0, blue = 0;

	CImage ImageTemp;
	ImageTemp.Create(ImageSize.cx, ImageSize.cy, 24);

	CClientDC dc(this);

	for(int x = 0; x < ImageSize.cx; x++)
	{
		for(int y = 0; y < ImageSize.cy; y++)
		{
			ImageTemp.SetPixel(x, y, ImageOrg.GetPixel(x, y));
		}
	}



	for(int x = 1; x < ImageSize.cx - 1; x++)
	{
		for(int y = 1; y < ImageSize.cy - 1; y++)
		{
			red = 0;
			green = 0;
			blue = 0;

			color = ImageTemp.GetPixel(x, y);
			blue += (color >> 16);
			green += ((color & 0x0000FFFF) >> 8);
			red += (color & 0x000000FF);

			color = ImageTemp.GetPixel(x + 1, y);
			blue += (color >> 16);
			green += ((color & 0x0000FFFF) >> 8);
			red += (color & 0x000000FF);

			color = ImageTemp.GetPixel(x - 1, y);
			blue += (color >> 16);
			green += ((color & 0x0000FFFF) >> 8);
			red += (color & 0x000000FF);

			color = ImageTemp.GetPixel(x, y + 1);
			blue += (color >> 16);
			green += ((color & 0x0000FFFF) >> 8);
			red += (color & 0x000000FF);

			color = ImageTemp.GetPixel(x, y - 1);
			blue += (color >> 16);
			green += ((color & 0x0000FFFF) >> 8);
			red += (color & 0x000000FF);

			color = ImageTemp.GetPixel(x + 1, y + 1);
			blue += (color >> 16);
			green += ((color & 0x0000FFFF) >> 8);
			red += (color & 0x000000FF);

			color = ImageTemp.GetPixel(x + 1, y - 1);
			blue += (color >> 16);
			green += ((color & 0x0000FFFF) >> 8);
			red += (color & 0x000000FF);

			color = ImageTemp.GetPixel(x - 1, y + 1);
			blue += (color >> 16);
			green += ((color & 0x0000FFFF) >> 8);
			red += (color & 0x000000FF);

			color = ImageTemp.GetPixel(x - 1, y - 1);
			blue += (color >> 16);
			green += ((color & 0x0000FFFF) >> 8);
			red += (color & 0x000000FF);

			color = RGB(red/9, green/9, blue/9);

			ImageOrg.SetPixel(x, y, color);

		}

		Invalidate(0);
		UpdateWindow();
		dc.MoveTo(x, 0);
		dc.LineTo(x, ImageSize.cy);
	}

	Invalidate();
}

void CChildView::OnSpatialEnhancemantMedianFilter()
{
	// TODO: Add your command handler code here
	COLORREF color;
	int red[9], green[9], blue[9];

	CImage ImageTemp;
	ImageTemp.Create(ImageSize.cx, ImageSize.cy, 24);

	CClientDC dc(this);


	for(int x = 0; x < ImageSize.cx; x++)
	{
		for(int y = 0; y < ImageSize.cy; y++)
		{
			ImageTemp.SetPixel(x, y, ImageOrg.GetPixel(x, y));
		}
	}

	for(int x = 1; x < ImageSize.cx - 1; x++)
	{
		for(int y = 1; y < ImageSize.cy - 1; y++)
		{
			memset(red, 0, sizeof(red));
			memset(green, 0, sizeof(green));
			memset(blue, 0, sizeof(blue));

			color = ImageTemp.GetPixel(x, y);
			blue[0] = (color >> 16);
			green[0] = ((color & 0x0000FFFF) >> 8);
			red[0] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x + 1, y);
			blue[1] = (color >> 16);
			green[1] = ((color & 0x0000FFFF) >> 8);
			red[1] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x - 1, y);
			blue[2] = (color >> 16);
			green[2] = ((color & 0x0000FFFF) >> 8);
			red[2] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x, y + 1);
			blue[3] = (color >> 16);
			green[3] = ((color & 0x0000FFFF) >> 8);
			red[3] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x, y - 1);
			blue[4] = (color >> 16);
			green[4] = ((color & 0x0000FFFF) >> 8);
			red[4] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x + 1, y + 1);
			blue[5] = (color >> 16);
			green[5] = ((color & 0x0000FFFF) >> 8);
			red[5] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x + 1, y - 1);
			blue[6] = (color >> 16);
			green[6] = ((color & 0x0000FFFF) >> 8);
			red[6] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x - 1, y + 1);
			blue[7] = (color >> 16);
			green[7] = ((color & 0x0000FFFF) >> 8);
			red[7] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x - 1, y - 1);
			blue[8] = (color >> 16);
			green[8] = ((color & 0x0000FFFF) >> 8);
			red[8] = (color & 0x000000FF);

			int temp;

			for(int i = 0; i < 9; i++)
			{
				for(int j = i + 1; j < 9; j++)
				{
					if(red[i] > red[j])
					{
						temp = red[i];
						red[i] = red[j];
						red[j] = temp;

						temp = blue[i];
						blue[i] = blue[j];
						blue[j] = temp;

						temp = green[i];
						green[i] = green[j];
						green[j] = temp;
					}
				}
			}

			color = RGB(red[4], green[4], blue[4]);
			ImageOrg.SetPixel(x, y, color);
		}

		Invalidate(0);
		UpdateWindow();

		dc.MoveTo(x, 0);
		dc.LineTo(x, ImageSize.cy);
	}

	Invalidate();
}

void CChildView::OnSpatialEnhancemantSharpenLaplacion()
{
	// TODO: Add your command handler code here
	COLORREF color;
	int red[9], green[9], blue[9];

	CImage ImageTemp;
	ImageTemp.Create(ImageSize.cx, ImageSize.cy, 24);

	CClientDC dc(this);


	for(int x = 0; x < ImageSize.cx; x++)
	{
		for(int y = 0; y < ImageSize.cy; y++)
		{
			ImageTemp.SetPixel(x, y, ImageOrg.GetPixel(x, y));
		}
	}

	for(int x = 1; x < ImageSize.cx - 1; x++)
	{
		for(int y = 1; y < ImageSize.cy - 1; y++)
		{
			memset(red, 0, sizeof(red));
			memset(green, 0, sizeof(green));
			memset(blue, 0, sizeof(blue));

			color = ImageTemp.GetPixel(x, y);
			blue[0] = (color >> 16);
			green[0] = ((color & 0x0000FFFF) >> 8);
			red[0] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x + 1, y);
			blue[1] = (color >> 16);
			green[1] = ((color & 0x0000FFFF) >> 8);
			red[1] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x - 1, y);
			blue[2] = (color >> 16);
			green[2] = ((color & 0x0000FFFF) >> 8);
			red[2] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x, y + 1);
			blue[3] = (color >> 16);
			green[3] = ((color & 0x0000FFFF) >> 8);
			red[3] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x, y - 1);
			blue[4] = (color >> 16);
			green[4] = ((color & 0x0000FFFF) >> 8);
			red[4] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x + 1, y + 1);
			blue[5] = (color >> 16);
			green[5] = ((color & 0x0000FFFF) >> 8);
			red[5] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x + 1, y - 1);
			blue[6] = (color >> 16);
			green[6] = ((color & 0x0000FFFF) >> 8);
			red[6] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x - 1, y + 1);
			blue[7] = (color >> 16);
			green[7] = ((color & 0x0000FFFF) >> 8);
			red[7] = (color & 0x000000FF);

			color = ImageTemp.GetPixel(x - 1, y - 1);
			blue[8] = (color >> 16);
			green[8] = ((color & 0x0000FFFF) >> 8);
			red[8] = (color & 0x000000FF);

			red[0] *= 9;
			green[0] *= 9;
			blue[0] *= 9;
			for(int i = 1; i < 9; i++)
			{
				red[0] -= red[i];
				green[0] -= green[i];
				blue[0] -= blue[i];
			}
			color = RGB(red[0] > 0 ? red[0] : 0, green[0] > 0 ? green[0] : 0, blue[0] > 0 ? blue[0] : 0);
			ImageOrg.SetPixel(x, y, color);
		}

		Invalidate(0);
		UpdateWindow();

		dc.MoveTo(x, 0);
		dc.LineTo(x, ImageSize.cy);
	}

	Invalidate();
}

void CChildView::OnFrequencyEnhancementDft()
{
	// TODO: Add your command handler code here
	COLORREF color, gray_color;
	int gray;

	double * dfti = (double*)malloc(ImageSize.cx * ImageSize.cy * sizeof(double));
	DFTRe = (double*)malloc(ImageSize.cx * ImageSize.cy * sizeof(double));
	DFTIm = (double*)malloc(ImageSize.cx * ImageSize.cy * sizeof(double));

	if(! (dfti && DFTRe && DFTIm))
	{
		AfxMessageBox(_T("内存分配失败"));

		return;
	}
	//若不是灰度图，先转变为灰度图
	if(!IsGray)
	{
		for(int x = 0; x < ImageSize.cx; x++)
		{
			for(int y = 0; y < ImageSize.cy; y++)
			{
				color = ImageOrg.GetPixel(x, y);
				gray = ((color >> 16) + ((color & 0x0000FFFF) >> 8) + (color & 0x000000FF)) / 3;
				gray_color = RGB(gray, gray, gray);
				ImageOrg.SetPixel(x, y, gray_color);
			}

			Invalidate(0);
			UpdateWindow();
		}

		IsGray = true;
	}

	//将灰度数据装入内存块
	double * dftii = dfti;

	for(int x = 0; x < ImageSize.cx; x++)
	{
		for(int y = 0; y < ImageSize.cy; y++, dftii++)
		{
			color = ImageOrg.GetPixel(x, y);
			*dftii = (double)(color & 0x000000FF);
		}
	}
	free(dftii);
	dftii = 0;

	//DFT
	DFT2D(dfti,DFTRe,DFTIm,ImageSize.cx,ImageSize.cy);

	//获得能量频谱图
	double *dftori = DFTRe, *dftoii = DFTIm;
	double temp = 0;
	for(int x = 0; x < ImageSize.cx; x++)
	{
		for(int y = 0; y < ImageSize.cy; y++, dftori++, dftoii++)
		{
			temp = 0;
			temp = (*dftori)*(*dftori) + (*dftoii)*(*dftoii);
			color = RGB(temp,temp,temp);
			ImageOrg.SetPixel(x, y, color);
		}
	}
	free(dfti);
	dfti = 0;
	free(dftori);
	dftori = 0;
	free(dftoii);
	dftoii = 0;

	Invalidate();
}

void CChildView::OnFrequencyEnhancementIdft()
{
	// TODO: Add your command handler code here
	double * idfto = (double*)malloc(ImageSize.cx * ImageSize.cy * sizeof(double));
	if(! idfto)
	{
		AfxMessageBox(_T("内存分配失败"));

		return;
	}
	if(! (DFTRe && DFTIm))
	{
		AfxMessageBox(_T("请先进行DFT变换"));
		return;
	}

	IDFT2D(DFTRe,DFTIm,idfto,ImageSize.cx,ImageSize.cy);

	double *idftoi = idfto;
	COLORREF color;
	for(int x = 0; x < ImageSize.cx; x++)
	{
		for(int y = 0; y < ImageSize.cy; y++, idftoi++)
		{
			color = RGB(*idftoi,*idftoi,*idftoi);
			ImageOrg.SetPixel(x, y, color);
		}
	}

	free(idfto);
	idfto = 0;
	free(idftoi);
	idftoi = 0;

	Invalidate();
}

void CChildView::OnFrequencyEnhancementSmoothIdeal()
{
	// TODO: Add your command handler code here
	double *dftori = DFTRe, *dftoii = DFTIm;
	double temp = 0;
	COLORREF color;
	bool IsInD0, IsInD1, IsInD2, IsInD3;
	for(int x = 0; x < ImageSize.cx; x++)
	{
		for(int y = 0; y < ImageSize.cy; y++, dftori++, dftoii++)
		{
			temp = (x - 0) * (x - 0) + (y - 0) * (y - 0);
			IsInD0 = sqrt(temp) < DISTANCE;
			temp = (x - ImageSize.cx) * (x - ImageSize.cx) + (y - 0) * (y - 0);
			IsInD1 = sqrt(temp) < DISTANCE;
			temp = (x - 0) * (x - 0) + (y - ImageSize.cy) * (y - ImageSize.cy);
			IsInD2 = sqrt(temp) < DISTANCE;
			temp = (x - ImageSize.cx) * (x - ImageSize.cx) + (y - ImageSize.cy) * (y - ImageSize.cy);
			IsInD3 = sqrt(temp) < DISTANCE;

			if(!(IsInD0 || IsInD1 || IsInD2 || IsInD3))
			{
				color = RGB(0,0,0);
				ImageOrg.SetPixel(x, y, color);

				*(DFTRe + x * y) = 0;
				*(DFTIm + x * y) = 0;
			}	
		}
	}

	free(dftori);
	dftori = 0;
	free(dftoii);
	dftoii = 0;

	Invalidate();
}

void CChildView::OnFrequencyEnhancementSharpenIdeal()
{
	// TODO: Add your command handler code here
	double *dftori = DFTRe, *dftoii = DFTIm;
	double temp = 0;
	COLORREF color;
	bool IsInD0, IsInD1, IsInD2, IsInD3;
	for(int x = 0; x < ImageSize.cx; x++)
	{
		for(int y = 0; y < ImageSize.cy; y++, dftori++, dftoii++)
		{
			temp = (x - 0) * (x - 0) + (y - 0) * (y - 0);
			IsInD0 = sqrt(temp) < DISTANCE;
			temp = (x - ImageSize.cx) * (x - ImageSize.cx) + (y - 0) * (y - 0);
			IsInD1 = sqrt(temp) < DISTANCE;
			temp = (x - 0) * (x - 0) + (y - ImageSize.cy) * (y - ImageSize.cy);
			IsInD2 = sqrt(temp) < DISTANCE;
			temp = (x - ImageSize.cx) * (x - ImageSize.cx) + (y - ImageSize.cy) * (y - ImageSize.cy);
			IsInD3 = sqrt(temp) < DISTANCE;

			if(IsInD0 || IsInD1 || IsInD2 || IsInD3)
			{
				color = RGB(0,0,0);
				ImageOrg.SetPixel(x, y, color);

				*(DFTRe + x * y) = 0;
				*(DFTIm + x * y) = 0;
			}	
		}
	}

	free(dftori);
	dftori = 0;
	free(dftoii);
	dftoii = 0;

	Invalidate();
}
void CChildView::OnUpdateFileSave(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateFileSaveAs(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateImgSizeHalf(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateImgSizeOrg(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateImgSizeDouble(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateImgSizeQuadruple(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateImgColorGray(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateImgColorBinary(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateSpatialEnhancemantNegative(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateSpatialEnhancemantHistogram(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateSpatialEnhancemantHistogramEqualization(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateSpatialEnhancemantAveragingFilter(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateSpatialEnhancemantMedianFilter(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateSpatialEnhancemantSharpenLaplacion(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateFrequencyEnhancementDft(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(ImageOrg.IsNull())
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateFrequencyEnhancementIdft(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(!(DFTRe && DFTIm))
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateFrequencyEnhancementSmoothIdeal(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(!(DFTRe && DFTIm))
	{
		pCmdUI->Enable(0);
	}
}

void CChildView::OnUpdateFrequencyEnhancementSharpenIdeal(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	if(!(DFTRe && DFTIm))
	{
		pCmdUI->Enable(0);
	}
}
