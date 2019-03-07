
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

#include "FTEasyDI.h"

#include <mmsystem.h>

// CGLMountainView

IMPLEMENT_DYNCREATE(CGLMountainView, CView)

BEGIN_MESSAGE_MAP(CGLMountainView, CView)
	// 標準印刷コマンド
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	//{{AFX_MSG_MAP(CTestGL2View)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
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

void CGLMountainView::OnDraw(CDC* pDC)
{
	CGLMountainDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: この場所にネイティブ データ用の描画コードを追加します。



	DWORD dwTimeStart = timeGetTime();

	// ▼ マイキャラ移動
	static UINT uJoyBefore = 0;
	UINT uJoy = FTEasyDI::GetJoyStickBit();
	double dAddSp = 0;


	double dHeightBefore = m_glground.GetHeight(m_vectView);
	double dMoveFreq;
	if (m_vectView.y <= dHeightBefore) {
		// 地上
		if (uJoy & FTEasyDI::JSB_LEFT) {
			m_nViewHead -= 10;
			//dAddSp = 0.1;
		}
		if (uJoy & FTEasyDI::JSB_RIGHT) {
			m_nViewHead += 10;
			//dAddSp = 0.1;
		}
		if (uJoy & FTEasyDI::JSB_UP) dAddSp = 0.2;
		if (uJoy & FTEasyDI::JSB_DOWN) dAddSp = -0.1;
		if (dAddSp != 0) {
			/*			m_vectMove += FTVect3d( sin( (double)m_nViewHead * 3.14159265/180 ) * dAddSp ,
												0,
												-cos( (double)m_nViewHead * 3.14159265/180 ) * dAddSp
												);
			*/
			m_vectMove += FTVect3d::CalcNormal(m_nViewHead, 0, 1, 0) * dAddSp;
		}

		m_vectView.y = dHeightBefore;
		m_vectMove.y = 0;
		if (uJoy & FTEasyDI::JSB_TR1 && !(uJoyBefore & FTEasyDI::JSB_TR1)) {
			m_vectMove.y = m_vectMove.GetLength()*.4 + .3;
		}


		dMoveFreq = (dAddSp != 0) ? 0.4 : 0.15;
	}
	else {
		// 空中
		m_vectMove = m_vectMove + FTVect3d(0, -0.1, 0);
		dMoveFreq = 0.95;

		if (uJoy & FTEasyDI::JSB_TR2) {
			m_vectMove.y += .2;
		}

	}

	uJoyBefore = uJoy;

	//	m_vectMove = m_vectMove*.9; + FTVect3d(0,-0.1,0 );
	m_vectMove.x = m_vectMove.x * dMoveFreq;
	m_vectMove.z = m_vectMove.z * dMoveFreq;

	//	m_vectView = m_vectView + m_vectMove;
	m_vectView.y += m_vectMove.y;
	double dHeight = m_glground.GetHeight(m_vectView);
	if (m_vectView.y < dHeight) {
		m_vectMove.y = 0;
		m_vectView.y = dHeight;
	}
	m_vectView.x += m_vectMove.x;
	m_vectView.z += m_vectMove.z;

	dHeight = m_glground.GetHeight(m_vectView);
	if (m_vectView.y < dHeight) {
		if (m_vectView.y + 0.01 > dHeight) {
			m_vectMove.y = dHeight - m_vectView.y;
			m_vectView.y = dHeight;
		}
		else {
			m_vectMove.x = -m_vectMove.x / 2;
			m_vectMove.z = -m_vectMove.z / 2;
			m_vectView.x += m_vectMove.x * 2;
			m_vectView.z += m_vectMove.z * 2;
			//			m_vectMove.y = 0;
			//			m_vectView = m_vectView + m_vectMove;
						// dHeight = dHeightBefore;
		}
	}

	dHeight = m_glground.GetHeight(m_vectView);

	//	m_vectView.y -= .2;
	m_glman.ActionWalk(m_vectMove.GetLength() * (dAddSp > 0 ? 1 : -1));


	// ▼ OpenGL描画
	m_gl.DrawBegin(pDC);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	m_gl.SetEnable(GL_DEPTH_TEST);

	//	glShadeModel( GL_FLAT );



		// Buffer Clear
	//	glClearColor( 0.0f , 0.0f , 0.5f , 0.0f );
	m_gl.SetClearColor(0, 0, 0.5);
	//	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_gl.Clear();
	//	glColor3f(1.0f , 1.0f , 1.0f );
	m_gl.SetColor(1.0, 1.0, 1.0);


	// View
	m_gl.SetTranslate(0, 0, -1.5);
	m_gl.SetRotate(m_nViewPitch + (m_vectView.y - dHeight) * 0, 1, 0, 0);

	m_gl.SetRotate(m_nViewHead, 0, 1, 0);
	//	m_gl.SetRotate(180-45, 0,1,0);


		// glTranslated( 0.0 , 0.0 , 0.0);
	//	m_gl.SetTranslate( m_vectView );
	//	m_gl.SetTranslate( FTVect3d(0,0,0)-m_vectView  );
	m_gl.SetTranslate(-m_vectView.x, -(m_vectView.y + 1.5), -m_vectView.z);


	// Lighting
	FTVect3d vectLight0(-.5, 1, -2);
	FTVect3d vectLight = vectLight0 / vectLight0.GetLength();
	//	vectLight = FTVect3d::CalcNormal( &vectLight0 );


	//	m_gl.SetLightSet(GL_LIGHT0,FTVect3d(.3,.3,.3),FTVect3d(.6,.6,.6),FTVect3d(1,1,1), vectLight );
	//	m_gl.SetLightSet(GL_LIGHT0,FTVect3d(.3,.3,.3),FTVect3d(.6,.6,.6),FTVect3d(1,1,1), m_vectView,TRUE );
	//	m_gl.SetLightSet(GL_LIGHT0,FTVect3d(.0,.0,.0),FTVect3d(.6,.6,.6),FTVect3d(1,1,1), FTVect3d(0,1.5,0),TRUE );
	m_gl.SetLightSet(GL_LIGHT0, FTVect3d(.0, .0, .0), FTVect3d(.6, .6, .6), FTVect3d(1, 1, 1), FTVect3d(0, .8, 0) + m_vectView, TRUE);

	m_gl.SetEnable(GL_LIGHTING);
	m_gl.SetEnable(GL_LIGHT0);

	// Matgerial
//	m_gl.SetMaterial( GL_FRONT , GL_AMBIENT_AND_DIFFUSE , FTVect3d(1,0,0) );
	m_gl.SetMaterial(GL_FRONT_AND_BACK, GL_SPECULAR, FTVect3d(1, 1, 1));
	m_gl.SetMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE, FTVect3d(.5, .5, .5));
	m_gl.SetMaterialShininess(GL_FRONT_AND_BACK, 100);






	//	m_vectView=m_vectView+FTVect3d( 0.1 ,0,0 );

	glPolygonMode(GL_FRONT, GL_FILL);
	glPolygonMode(GL_BACK, GL_FILL);
	//	glPolygonMode( GL_FRONT , GL_LINE );


	//	m_glground.RandBIbe();
	m_glground.Draw(m_gl);


	// Draw Man
	m_gl.SetTranslate(m_vectView.x, m_vectView.y, m_vectView.z);
	m_gl.SetRotate(-m_nViewHead, 0, 1, 0);
	m_gl.SetColor(1.0, 0, 0);
	m_glman.Draw(m_gl);
	/*	vect[0] = FTVect3d( -.1,.8,0);
		vect[1] = FTVect3d( .1,.8,0);
		vect[2] = FTVect3d( .1,0,0);
		vect[3] = FTVect3d( 0,.3,0);
		vect[4] = FTVect3d( -.1,0,0);
		m_gl.DrawPolygon( vect , 5 );
	*/
	// Draw Man Shadow
	m_gl.SetTranslate(0, dHeight - m_vectView.y, 0);
	m_gl.SetColor(0.3, 0, 0);
	m_glman.DrawShadow(m_gl);
	/*	FTVect3d vect[4];
		vect[0] = FTVect3d( -.1,0.1,0);
		vect[1] = FTVect3d( .1,0.1,0);
		vect[2] = FTVect3d( .1,0,0);
		vect[3] = FTVect3d( -.1,0,0);
		m_gl.DrawPolygon( vect , 4 );
	*/

	/*
		for ( int nM=0; nM<0; nM++ ) {
			glPolygonMode( GL_FRONT_AND_BACK , (nM==0) ? GL_FILL : GL_LINE);

			double dS = 0.8;
			double dY = (nM==0) ? -1 : 1;
			for ( double dZ=-5; dZ<5; dZ+=1 ) {
				m_gl.SetColor(1.0 , (int)dZ & 1 ? 1.0 : 0.0 , 1+dZ/12 );
	//			glTranslated( 0.0 , 0.0 , 0.0);
	//			glRotated(5,0.0,1.0,0.0);

				for ( double dX=-5; dX<5; dX+=1 ) {
					if (dX==0 || dZ==0 ) {
						// glColor3d(0.0,1.0,0.0 );
						m_gl.SetColor(0.0,1.0,0.0 );
					} else {
						// glColor3d(1.0 , (int)dZ & 1 ? 1.0 : 0.0 , 1+dZ/12 );
						m_gl.SetColor(1.0 , (int)dZ & 1 ? 1.0 : 0.0 , 1+dZ/12 );
					}

					FTVect3d vect[4];
					vect[0] = FTVect3d( dX , dY , dZ );
					vect[1] = vect[0]+FTVect3d( dS,0,0);
					vect[2] = vect[0]+FTVect3d( dS,0,dS);
					vect[3] = vect[0]+FTVect3d( 0,0,dS);


					m_gl.DrawPolygon( vect , 4 );
				}
			}
		}
	*/

	m_gl.DrawEnd(pDC);


	// ▼ ステータス表示

	//Timer
	DWORD dwTimeEnd = timeGetTime();
	DWORD dwLapse = dwTimeEnd - dwTimeStart;
	if (dwLapse == 0) dwLapse = 1;
	//Disp Status
	CRect rect;
	GetClientRect(rect);
	CString strMsg;
	strMsg.Format(L"SPF=%5f FPS=%3d / Window : %d*%d=%d dot", dwLapse / 1000.0, (int)(1000.0 / dwLapse), rect.Width(), rect.Height(), rect.Width()*rect.Height());
	CStatusBar* pStatusB = (CStatusBar *)AfxGetApp()->m_pMainWnd->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	pStatusB->SetPaneText(0, strMsg);

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


int CGLMountainView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// Init GL
	m_gl.Create(this);

	m_glground.Create(10, 10, 1);
	m_glground.AutoGenerate();

	// Init Timer
	SetTimer(1, 50, NULL);

	// Init var
	m_vectView = FTVect3d(0, 3, 0);
	m_nViewPitch = 20;
	m_nViewHead = 180 - 45;
	m_vectMove = FTVect3d(0, 0, 0);

	m_fMouseCapture = 0;

	return 0;
}

void CGLMountainView::OnDestroy()
{
	KillTimer(1);

	CView::OnDestroy();

	// TODO: この位置にメッセージ ハンドラ用のコードを追加してください
	m_gl.Release();
}

void CGLMountainView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_gl.SetWindowSize(cx, cy);

}

void CGLMountainView::OnTimer(UINT nIDEvent)
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	CClientDC dc(this);
	OnDraw(&dc);

	CView::OnTimer(nIDEvent);
}

void CGLMountainView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	SetCapture();
	m_fMouseCapture = TRUE;
	m_ptBeforePoint = point;

	CView::OnLButtonDown(nFlags, point);
}

void CGLMountainView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください
	ReleaseCapture();
	m_fMouseCapture = FALSE;



	CView::OnLButtonUp(nFlags, point);
}

void CGLMountainView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: この位置にメッセージ ハンドラ用のコードを追加するかまたはデフォルトの処理を呼び出してください

	if (m_fMouseCapture) {
		CRect rect;
		GetClientRect(rect);

		m_nViewHead -= (point.x - m_ptBeforePoint.x) * 100 / rect.Width();
		//		m_nViewPitch -= (point.y - m_ptBeforePoint.y)*100/rect.Height();

		double dUD = (double)(point.y - m_ptBeforePoint.y) * 10 / rect.Height();
		m_vectView += FTVect3d(sin((double)m_nViewHead * 3.14159265 / 180) * dUD,
			0,
			-cos((double)m_nViewHead * 3.14159265 / 180) * dUD
		);



		TRACE("m_nViewHead = %d\n", m_nViewHead);

		m_ptBeforePoint = point;

	}

	CView::OnMouseMove(nFlags, point);
}
