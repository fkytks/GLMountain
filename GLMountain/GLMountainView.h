
// GLMountainView.h : CGLMountainView クラスのインターフェイス
//

#pragma once

#include "FTEasyGL.h"
#include "TFTEasyGLGround.h"
#include "TFTEasyGLCharMan.h"

class CGLMountainView : public CView
{
protected: // シリアル化からのみ作成します。
	CGLMountainView() noexcept;
	DECLARE_DYNCREATE(CGLMountainView)

// 属性
public:
	CGLMountainDoc* GetDocument() const;

// 操作
public:

protected:
	FTEasyGL	m_gl;
	TFTEasyGLGround	m_glground;
	TFTEasyGLCharMan	m_glman;

	FTVect3d	m_vectView;
	int	m_nViewPitch;
	int	m_nViewHead;
	FTVect3d	m_vectMove;

	BOOL	m_fMouseCapture;
	POINT	m_ptBeforePoint;

// オーバーライド
public:
	virtual void OnDraw(CDC* pDC);  // このビューを描画するためにオーバーライドされます。
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 実装
public:
	virtual ~CGLMountainView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成された、メッセージ割り当て関数
protected:
	//{{AFX_MSG(CTestGL2View)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GLMountainView.cpp のデバッグ バージョン
inline CGLMountainDoc* CGLMountainView::GetDocument() const
   { return reinterpret_cast<CGLMountainDoc*>(m_pDocument); }
#endif

