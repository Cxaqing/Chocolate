
// TestView.h : interface of the CTestView class
//

#pragma once
#include"Cube.h"
#include "Transform3.h"

class CTestView : public CView
{
protected: // create from serialization only
	CTestView();
	DECLARE_DYNCREATE(CTestView)

// Attributes
public:
	CTestDoc* GetDocument() const;

// Operations
public:
	void DoubleBuffer(CDC* pDC);//双缓冲绘图
	void LoadWallpaper(CDC* pDC);
	void InitializeLightingScene(void);//初始化光照场景
	void DrawObject(CDC* pDC);//绘制对象
public:
	BOOL bFlatShade;//平面着色

	int	 nLightSourceNumber;//光源数量
	CLighting* pLight;//光照环境
	CMaterial* pMaterial;//物体材质
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CCube* cube;//长方体对象数组
	//CProjection projection;//投影
	CTransform3 transform[25];//变换
	double Alpha, Beta;//x方向旋转α角,y方向旋转β角
	BOOL bPlay;//动画开关
// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnGraphAnimation();
	afx_msg void OnUpdateGraphAnimation(CCmdUI *pCmdUI);
};

#ifndef _DEBUG  // debug version in TestView.cpp
inline CTestDoc* CTestView::GetDocument() const
   { return reinterpret_cast<CTestDoc*>(m_pDocument); }
#endif

