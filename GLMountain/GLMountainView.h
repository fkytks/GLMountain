
// GLMountainView.h : CGLMountainView クラスのインターフェイス
//

#pragma once


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
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GLMountainView.cpp のデバッグ バージョン
inline CGLMountainDoc* CGLMountainView::GetDocument() const
   { return reinterpret_cast<CGLMountainDoc*>(m_pDocument); }
#endif

