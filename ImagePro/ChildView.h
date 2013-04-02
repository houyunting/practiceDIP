// ChildView.h : CChildView ��Ľӿ�
//


#pragma once
#include "atltypes.h"

// CChildView ����

enum EImageSizeFlag
{
	SIZE_ORG,
	SIZE_HALF,
	SIZE_DOUBLE,
	SIZE_QUADRUPLE
};

class CChildView : public CWnd
{
// ����
public:
	CChildView();

// ����
public:

// ����
public:

// ��д
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CChildView();

	// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()	
public:
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
	afx_msg void OnImgSizeOrg();
	afx_msg void OnImgSizeHalf();
	afx_msg void OnImgSizeDouble();
	afx_msg void OnImgColorGray();
	afx_msg void OnImgColorBinary();
	afx_msg void OnSpatialEnhancemantNegative();
	afx_msg void OnSpatialEnhancemantHistogram();
	afx_msg void OnSpatialEnhancemantHistogramEqualization();
	afx_msg void OnSpatialEnhancemantAveragingFilter();
	afx_msg void OnSpatialEnhancemantMedianFilter();
	afx_msg void OnSpatialEnhancemantSharpenLaplacion();
	afx_msg void OnFrequencyEnhancementDft();
	afx_msg void OnFrequencyEnhancementIdft();
private:
	void AdjustWindowSize(void);	
private:
	CImage ImageOrg;
	CString ImageNameOrg;
	EImageSizeFlag ImageSizeFlag;
	bool IsGray;
	CSize ImageSize;
	double *DFTRe;
	double *DFTIm;
public:
	afx_msg void OnFrequencyEnhancementSmoothIdeal();
	afx_msg void OnFrequencyEnhancementSharpenIdeal();
	afx_msg void OnImgSizeQuadruple();
	afx_msg void OnUpdateFileSave(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFileSaveAs(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImgSizeHalf(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImgSizeOrg(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImgSizeDouble(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImgSizeQuadruple(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImgColorGray(CCmdUI *pCmdUI);
	afx_msg void OnUpdateImgColorBinary(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSpatialEnhancemantNegative(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSpatialEnhancemantHistogram(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSpatialEnhancemantHistogramEqualization(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSpatialEnhancemantAveragingFilter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSpatialEnhancemantMedianFilter(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSpatialEnhancemantSharpenLaplacion(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFrequencyEnhancementDft(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFrequencyEnhancementIdft(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFrequencyEnhancementSmoothIdeal(CCmdUI *pCmdUI);
	afx_msg void OnUpdateFrequencyEnhancementSharpenIdeal(CCmdUI *pCmdUI);
};

