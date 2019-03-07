/* [TFTEasyGLCharMan]
	FTEasyGL用キャラクタ表示クラス
 	1998.02.15-  F/T
*/

#include "FTEasyGL.h"
#include <math.h>
#include <stdlib.h>

class TFTEasyGLCharMan {
// アトリビュート
public:
	double	m_dFootAngle;
	double	m_dWalkSpeed;

// 生成・消滅
public:
	TFTEasyGLCharMan() {
		m_dFootAngle = 0;
		m_dWalkSpeed = 0;
	}

// オペレーション
public:
	void Draw( FTEasyGL& gl , FTVect3d& rVect = FTVect3d(0,0,0) , BOOL fShadow=FALSE ) {

		FTVect3d vectFootL,vectFootR;
		if ( fabs(m_dWalkSpeed)>0.05 ) {
			vectFootL = FTVect3d::CalcNormal( m_dFootAngle ,1,0,0 )*.2;
			if ( vectFootL.y<0 ) vectFootL.y=0;
			vectFootR = FTVect3d::CalcNormal( m_dFootAngle+180 ,1,0,0 )*.2;
			if ( vectFootR.y<0 ) vectFootR.y=0;
		} else {
			vectFootR = vectFootL = FTVect3d(0,0,0);
		}
		
		FTVect3d vect[5];
		int	i=0;

		vect[i++] = FTVect3d( -.1,.8,0);	// Head Right
		vect[i++] = FTVect3d( .1,.8,0);		// Head Left
		vect[i++] = FTVect3d( .1,0,0) + vectFootR;		// RightLeg
		vect[i++] = FTVect3d( 0,.3,0);
		vect[i++] = FTVect3d( -.1,0,0) + vectFootL;		// LeftReg

/*		i=4;
		vect[i--] = FTVect3d( -.1,.8,0);	// Head Right
		vect[i--] = FTVect3d( .1,.8,0);		// Head Left
		vect[i--] = FTVect3d( .1,0,0) + vectFootR;		// RightLeg
		vect[i--] = FTVect3d( 0,.3,0);
		vect[i--] = FTVect3d( -.1,0,0) + vectFootL;		// LeftReg
		i=5;
*/
		if ( fShadow ) {
			for ( int i2=0; i2<i; i2++ ) vect[i2].y = vect[i2].y/10;
		}
		
		gl.DrawPolygon( vect , i );

		;
	}

	void DrawShadow( FTEasyGL& gl , FTVect3d& rVect = FTVect3d(0,0,0) ) {
		Draw( gl , rVect , TRUE );
	}

	void ActionWalk( double dSpeed ) {
		m_dWalkSpeed = dSpeed;
		if ( fabs(dSpeed)>0.05 ) {
			m_dFootAngle+= m_dWalkSpeed*400;
		} else {
			m_dFootAngle=0;
		}

	}

};
