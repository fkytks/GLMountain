
// GLMountainView.cpp : CGLMountainView クラスの実装
//

#include "stdafx.h"
// SHARED_HANDLERS は、プレビュー、縮小版、および検索フィルター ハンドラーを実装している ATL プロジェクトで定義でき、
// そのプロジェクトとのドキュメント コードの共有を可能にします。
#ifndef SHARED_HANDLERS
#include "GLMountain.h"
#endif

#include "GLMountainDoc.h"
#include "GLMountainView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGLMountainView

IMPLEMENT_DYNCREATE(CGLMountainView, CView)

BEGIN_MESSAGE_MAP(CGLMountainView, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGLMountainView コンストラクション/デストラクション

CGLMountainView::CGLMountainView() noexcept
{
	// TODO: 構築コードをここに追加します。

}

CGLMountainView::~CGLMountainView()
{
}

BOOL CGLMountainView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: この位置で CREATESTRUCT cs を修正して Window クラスまたはスタイルを
	//  修正してください。

	return CView::PreCreateWindow(cs);
}

// CGLMountainView 描画

void CGLMountainView::OnDraw(CDC* /*pDC*/)
{
	CGLMountainDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。
}


// CGLMountainView の印刷

BOOL CGLMountainView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 既定の印刷準備
	return DoPreparePrinting(pInfo);
}

void CGLMountainView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷前の特別な初期化処理を追加してください。
}

void CGLMountainView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 印刷後の後処理を追加してください。
}


// CGLMountainView の診断

#ifdef _DEBUG
void CGLMountainView::AssertValid() const
{
	CView::AssertValid();
}

void CGLMountainView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGLMountainDoc* CGLMountainView::GetDocument() const // デバッグ以外のバージョンはインラインです。
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGLMountainDoc)));
	return (CGLMountainDoc*)m_pDocument;
}
#endif //_DEBUG


// CGLMountainView メッセージ ハンドラー
