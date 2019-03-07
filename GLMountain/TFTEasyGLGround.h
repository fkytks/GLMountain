/* [TFTEasyGLGround]
	FTEasyGL用地面表示クラス
 	1998.02.13-  F/T
*/

#include "FTEasyGL.h"
#include <math.h>
#include <stdlib.h>

class TFTEasyGLGtoundCell {
// アトリビュート
public:
	double	m_dHeight[4];	
	double	m_dSize;

// 生成・消滅
public:
	TFTEasyGLGtoundCell(double dH0=0,double dH1=0,double dH2=0,double dH3=0,double dSize=1) {
		m_dHeight[0]=dH0;
		m_dHeight[1]=dH1;
		m_dHeight[2]=dH2;
		m_dHeight[3]=dH3;
		m_dSize=dSize;
	}

// オペレーション
public:
	void SetHeight( double dH0=0,double dH1=0,double dH2=0,double dH3=0 ) {
		m_dHeight[0]=dH0;
		m_dHeight[1]=dH1;
		m_dHeight[2]=dH2;
		m_dHeight[3]=dH3;
	}
	void SetHeightSame( double dH = 0 ) {
		SetHeight( dH,dH,dH,dH );
	}
	double GetHeightSame() {
		return ( m_dHeight[0]+m_dHeight[1]+m_dHeight[2]+m_dHeight[3] )/4;
	}
	double GetHeight( double dX , double dZ ) {
		return ( (m_dHeight[0]+m_dHeight[3])*dX + (m_dHeight[1]+m_dHeight[2])*(1-dX) +
					(m_dHeight[0]+m_dHeight[1])*dZ + (m_dHeight[2]+m_dHeight[3])*(1-dZ) ) / 4; 
	}
	void SetCellSize( double dSize = 1 ) {
		m_dSize = dSize;
	}


	void Draw( FTEasyGL& gl , const FTVect3d& rVect = FTVect3d(0,0,0) ) {
		FTVect3d vect[4];
		vect[3] = FTVect3d( 0,m_dHeight[0],0) + FTVect3d(rVect);
		vect[2] = FTVect3d( m_dSize,m_dHeight[1],0) + FTVect3d(rVect);
		vect[1] = FTVect3d( m_dSize,m_dHeight[2],m_dSize) + FTVect3d(rVect);
		vect[0] = FTVect3d( 0,m_dHeight[3],m_dSize) + FTVect3d(rVect);		
		gl.DrawPolygon( vect , 4 );
	}
	void DrawWallRight( FTEasyGL& gl , TFTEasyGLGtoundCell& rCellReft ,  const FTVect3d& rVect = FTVect3d(0,0,0) ) {
		FTVect3d vect[4];

/*
		vect[0] = FTVect3d( m_dSize,m_dHeight[2],m_dSize) + rVect;
		vect[1] = FTVect3d( m_dSize,m_dHeight[1],0) + rVect;
		vect[2] = FTVect3d( m_dSize,rCellReft.m_dHeight[0],0) + rVect;
		vect[3] = FTVect3d( m_dSize,rCellReft.m_dHeight[3],m_dSize) + rVect;
*/
		vect[3] = FTVect3d( m_dSize,m_dHeight[2],m_dSize) + rVect;
		vect[2] = FTVect3d( m_dSize,m_dHeight[1],0) + rVect;
		vect[1] = FTVect3d( m_dSize,rCellReft.m_dHeight[0],0) + rVect;
		vect[0] = FTVect3d( m_dSize,rCellReft.m_dHeight[3],m_dSize) + rVect;

		gl.DrawPolygon( vect , 4 );
	}

	void DrawWallUnder( FTEasyGL& gl , TFTEasyGLGtoundCell& rCellUnder ,  const FTVect3d& rVect = FTVect3d(0,0,0) ) {
		FTVect3d vect[4];
/*
		vect[0] = FTVect3d( 0,m_dHeight[3],m_dSize) + rVect;
		vect[1] = FTVect3d( m_dSize,m_dHeight[2],m_dSize) + rVect;
		vect[2] = FTVect3d( m_dSize,rCellUnder.m_dHeight[1],m_dSize) + rVect;
		vect[3] = FTVect3d( 0,rCellUnder.m_dHeight[0],m_dSize) + rVect;
*/
		vect[3] = FTVect3d( 0,m_dHeight[3],m_dSize) + rVect;
		vect[2] = FTVect3d( m_dSize,m_dHeight[2],m_dSize) + rVect;
		vect[1] = FTVect3d( m_dSize,rCellUnder.m_dHeight[1],m_dSize) + rVect;
		vect[0] = FTVect3d( 0,rCellUnder.m_dHeight[0],m_dSize) + rVect;

		gl.DrawPolygon( vect , 4 );
	}

};


class TFTEasyGLGround {
// アトリビュート
public:
	TFTEasyGLGtoundCell* pCell;
	int	m_nWidth;
	int	m_nHeight;
	double m_dCellSize;	

// 生成・消滅
public:
	TFTEasyGLGround( ) {
		pCell = 0;
	}
	virtual ~TFTEasyGLGround() {
		Release();
	}

// オペレーション
public:
	void Create( int nWidth , int nHeight , double dCellSize = 1 ) {
		Release();
		m_nWidth = nWidth;
		m_nHeight = nHeight;
		m_dCellSize = dCellSize;
		pCell = new TFTEasyGLGtoundCell[ nWidth*nHeight ];
	}
	void Release() {
		if ( pCell ) {
			delete [] pCell;
			pCell = NULL;
		}
	}

	void AutoGenerate() {
		for ( int iX=0; iX<m_nWidth; iX++ ) {
			for ( int iY=0; iY<m_nHeight; iY++  ) {
				double dH = (double)iX*(double)iY / 10 + ((double)rand()/RAND_MAX);
				GetCell(iX,iY)->SetHeightSame( dH );
/*				GetCell(iX,iY)->SetHeight( dH + ((double)rand()/RAND_MAX),
											 dH + ((double)rand()/RAND_MAX),
											  dH + ((double)rand()/RAND_MAX),
											   dH + ((double)rand()/RAND_MAX) );
*/
				GetCell(iX,iY)->SetCellSize( m_dCellSize );
			}
		}
	}
	void RandBIbe() {
		for ( int iX=0; iX<m_nWidth; iX++ ) {
			for ( int iY=0; iY<m_nHeight; iY++  ) {
				GetCell(iX,iY)->SetHeightSame( GetCell(iX,iY)->GetHeightSame() + (((double)rand()/RAND_MAX)-.5)/10 );
			}
		}
	}
	void Draw( FTEasyGL& gl , FTVect3d& rVect = FTVect3d(0,0,0) ) {
		for ( int iX=0; iX<m_nWidth; iX+=1 ) {
			for ( int iY=0; iY<m_nHeight; iY+=1  ) {
				gl.SetColor(1.0 , (iX+iY) & 1 ? 1.0 : 0.0 , 1 );
				GetCell(iX,iY)->Draw( gl ,rVect+FTVect3d( (double)iX*m_dCellSize , 0,(double)iY*m_dCellSize ) );
				if ( iX<m_nWidth-1 ) {
//					gl.SetColor(0.25 , 0.0 , .5 );
					gl.SetColor(0.25 , 0.0 , 1 );
					GetCell(iX,iY)->DrawWallRight( gl ,*GetCell(iX+1,iY),rVect+FTVect3d( (double)iX*m_dCellSize , 0,(double)iY*m_dCellSize ) );
				}			
				if ( iY<m_nHeight-1 ) {
//					gl.SetColor(0.5 , 0.0 , 1 );
					gl.SetColor(0.25 , 0.0 , 1 );
					GetCell(iX,iY)->DrawWallUnder( gl ,*GetCell(iX,iY+1),rVect+FTVect3d( (double)iX*m_dCellSize , 0,(double)iY*m_dCellSize ) );
				}			
			}
		}
	}
	TFTEasyGLGtoundCell* GetCell( int nX , int nY ) {
		return &pCell[ nX + nY*m_nWidth ];
	}

	double GetHeight( FTVect3d& rVect ) {
		return GetHeight( rVect.x , rVect.z );
	}
	double GetHeight( double dX , double dZ ) {
		dX/=m_dCellSize;
		dZ/=m_dCellSize;

		int iX = (int)dX;
		int	iZ = (int)dZ;

		double dY = 0;
		if ( iX>=0 && iX<m_nWidth && iZ>=0 && iZ<m_nHeight ) {
			dY = GetCell(iX,iZ)->GetHeight( dX - (double)iX, dZ - (double)iZ);
		}
		return dY;
	}


};
