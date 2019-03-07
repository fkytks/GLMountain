/*	[FTEasyGL]
	OpenGL簡易操作クラス
 	1998.02.12- Sunquest F/T

  Need libs:
	MFC
	OpenGL32.lib
	FTVect3d.cpp/.h
*/

#ifndef _INC_FTEasyGL_H_
#define _INC_FTEasyGL_H_

#include <gl\gl.h>
#pragma comment( lib, "opengl32.lib" )
#include "FTVect3d.h"

class FTEasyGL {
// アトリビュート
protected:
	HGLRC	m_hRC;						// OpenGLリソースハンドル
	DWORD	m_dwPFDFlag;				// OpenGLピクセルフォーマットフラグ
	CWnd*	m_pWndGL;					// OpenGL描画対象Window

	DWORD	m_dwFlag;
	enum {
		GLMODE_LIGHTING = 0x0001
	};

// 生成・消滅
public:
	FTEasyGL();
	virtual ~FTEasyGL();

// オペレーション
public:
	virtual void Init();
	void SetDrawWindow( CWnd* pWnd = NULL );
	void SetWindowSize( int nX , int nY );
	virtual void Create( CWnd* pWnd = NULL );
	void Release();

	void DrawBegin(CDC* pDC);
	void DrawEnd(CDC* pDC);

	virtual void Draw(CDC* pDC);

	void SetClearColor( double dR = 0 , double dG = 0 , double dB = 0 , double dAlpha = 0) {
		glClearColor( (float)dR , (float)dG , (float)dB , (float)dAlpha );
	}
	void SetColor( double dR = 0 , double dG = 0 , double dB = 0) {
		if ( m_dwFlag & GLMODE_LIGHTING ) {
			SetMaterial( GL_FRONT ,  GL_AMBIENT_AND_DIFFUSE , FTVect3d(dR , dG , dB) );
		} else {
			glColor3d( dR , dG , dB );
		}
	}
	void DrawPolygon( FTVect3d* pVect , int nPolygon ) {
	glBegin( GL_POLYGON );
			if ( m_dwFlag & GLMODE_LIGHTING && nPolygon>2 ) {
				SetNormal( FTVect3d::CalcNormal( pVect[0],pVect[1],pVect[3] ) );
			}
			for ( int i=0; i<nPolygon; i++ ) 
				SetVertex( pVect[i] );
		glEnd();
	}
	void SetLight( GLenum eLight , GLenum eAtr , FTVect3d& rVect , double dAlpha=1.0 ) {
		GLfloat fLight[4]={ (GLfloat)rVect.x , (GLfloat)rVect.y , (GLfloat)rVect.z , (GLfloat)dAlpha };
		glLightfv( eLight , eAtr , fLight );
	}
	void SetLightSet( GLenum eLight , FTVect3d& rVectAmbient=FTVect3d(.3,.3,.3) , FTVect3d& rVectDiffuse=FTVect3d(.5,.5,.5) , FTVect3d& rVectSpecular=FTVect3d(1,1,1) , FTVect3d& rVectPosition=FTVect3d(0.57735,0.57735,0.57735) , BOOL fPointLight = FALSE ) {
		SetLight( eLight , GL_AMBIENT , rVectAmbient );
		SetLight( eLight , GL_DIFFUSE , rVectDiffuse );
		SetLight( eLight , GL_SPECULAR , rVectSpecular );
		SetLight( eLight , GL_POSITION , rVectPosition , (fPointLight? 1.0 : 0.0) );
	}

	void SetMaterial( GLenum eSide , GLenum eAtr , FTVect3d& rVect , double dAlpha=1.0 ) {
		GLfloat fLight[4]={ (GLfloat)rVect.x , (GLfloat)rVect.y , (GLfloat)rVect.z , (GLfloat)dAlpha };
		glMaterialfv( eSide , eAtr , fLight );
	}
	void SetMaterialShininess( GLenum eSide , double dShininess ) {
		glMaterialf( eSide , GL_SHININESS , (float)dShininess );
	}

	void SetEnable( GLenum eAtr ) {
		glEnable( eAtr );
	}
	
	void SetVertex( FTVect3d& rVect ) {
		glVertex3d( rVect.x , rVect.y , rVect.z ); 
	}
	void SetNormal( FTVect3d& rVect ) {
		glNormal3d( rVect.x , rVect.y , rVect.z ); 
	}
	void SetTranslate(  FTVect3d& rVect ) {
		glTranslated( rVect.x , rVect.y , rVect.z ); 
	}
	void SetTranslate( double x=0 , double y=0 , double z=0  ) {
		glTranslated( x , y , z ); 
	}
	void SetRotate(  double dAngle ,FTVect3d& rVect ) {
		glRotated( dAngle , rVect.x , rVect.y , rVect.z ); 
	}
	void SetRotate( double dAngle , double x=0 , double y=0 , double z=0  ) {
		glRotated( dAngle , x , y , z ); 
	}
	void Clear( DWORD dwFlag = GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT) {
		glClear( dwFlag );
	}


};

#endif
