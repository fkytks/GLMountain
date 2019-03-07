/*	[FTVect3d]
	Vector操作クラス
 	1998.02.12-  F/T
*/

#ifndef _INC_FTVect3d_H_
#define _INC_FTVect3d_H_

#include <math.h>


class FTVect3d {
// アトリビュート
public:
	double	x;
	double	y;
	double	z;

// 生成・消滅
public:
	FTVect3d( double dX = 0 , double dY = 0 , double dZ = 0) {
		x = dX;
		y = dY;
		z = dZ;
	};
	FTVect3d( const FTVect3d* pVect ) {
		x = pVect->x;
		y = pVect->y;
		z = pVect->z;
	}
	FTVect3d( const FTVect3d& rVect ) {
		x = rVect.x;
		y = rVect.y;
		z = rVect.z;
	}
	FTVect3d( FTVect3d& rVect1,FTVect3d& rVect2,FTVect3d& rVect3 ) {
		FTVect3d vectN;
		vectN = CalcNormal( rVect1 , rVect2 , rVect3 ) ;
		x = vectN.x;
		y = vectN.y;
		z = vectN.z;
	}


// オペレーション
public:
	double GetLength();

	const FTVect3d& operator=( const FTVect3d& rVect ) {
		x = rVect.x;
		y = rVect.y;
		z = rVect.z;
		return *this;
	}
	const FTVect3d& operator=( const FTVect3d* pVect ) {
		x = pVect->x;
		y = pVect->y;
		z = pVect->z;
		return *this;
	}
	FTVect3d& operator*( double dMul ) {
		static FTVect3d vect;
		vect = FTVect3d( x*dMul , y*dMul ,z*dMul );
		return vect;
	}
	FTVect3d& operator/( double dDev ) {
		static FTVect3d vect;
		vect = FTVect3d( x/dDev , y/dDev ,z/dDev );
		return vect;
	}
/*
	FTVect3d& operator+( const FTVect3d &rVect ) {
		static FTVect3d vect;
		vect = FTVect3d( x+rVect.x , y+rVect.y , z+rVect.z );
		return vect;
	}
*/
	FTVect3d operator+( const FTVect3d &rVect ) {
		return FTVect3d( x+rVect.x , y+rVect.y , z+rVect.z );
	}
/*	FTVect3d operator+( const FTVect3d &rVect1 , const FTVect3d &rVect2 ) {
		return FTVect3d( rVect1.x+rVect2.x , rVect1.y+rVect2.y , rVect1.z+rVect2.z );
	}
*/
	FTVect3d operator+( const FTVect3d *pVect ) {
		return FTVect3d( x+pVect->x , y+pVect->y , z+pVect->z );
	}

	const FTVect3d& operator+=( const FTVect3d& rVect ) {
		x += rVect.x;
		y += rVect.y;
		z += rVect.z;
		return *this;
	}


/*	FTVect3d& operator-( FTVect3d &rVect ) {
		static FTVect3d vect;
		vect = FTVect3d( x-rVect.x , y-rVect.y , z-rVect.z );
		return vect;
	}
*/
	FTVect3d operator-( const FTVect3d &rVect ) {
		return FTVect3d( x-rVect.x , y-rVect.y , z-rVect.z );
	}
	FTVect3d operator-( const FTVect3d *pVect ) {
		return FTVect3d( x-pVect->x , y-pVect->y , z-pVect->z );
	}

	FTVect3d operator-() {
		return FTVect3d( -x,-y,-z );
	}


// 静的関数
public:
	static FTVect3d& CalcNormal( FTVect3d& rVect1,FTVect3d& rVect2,FTVect3d& rVect3 );
	static FTVect3d& CalcNormal( FTVect3d* pVect ) {
		return CalcNormal( pVect[0],pVect[1],pVect[2]);
	}
	static FTVect3d& CalcNormal( double dAngle , double dX , double dY , double dZ ) {
		static FTVect3d vectR;
		
		double dRH = sin( (double)dAngle * 3.14159265/180 );
		double dRV = -cos( (double)dAngle * 3.14159265/180 );
		if ( dX ) {
			vectR.x = 0;
			vectR.y = dRV;
			vectR.z = dRH;
		} else if ( dY ) {
			vectR.x = dRH;
			vectR.y = 0;
			vectR.z = dRV;
		} else if ( dZ ) {
			vectR.x = dRH;
			vectR.y = dRV;
			vectR.z = 0;
		}
		return vectR;
	}
};

#endif
