/*	[FTVect3d]
	VectorëÄçÏÉNÉâÉX
 	1998.02.12-  F/T
*/

#include "stdafx.h"
#include "FTVect3d.h"

FTVect3d& FTVect3d::CalcNormal( FTVect3d& rVect1,FTVect3d& rVect2,FTVect3d& rVect3)
{
	FTVect3d vectA( rVect2.x - rVect1.x , rVect2.y - rVect1.y , rVect2.z - rVect1.z);
	FTVect3d vectB( rVect3.x - rVect1.x , rVect3.y - rVect1.y , rVect3.z - rVect1.z);
	FTVect3d vectN( vectA.y*vectB.z - vectA.z*vectB.y,
					vectA.z*vectB.x - vectA.x*vectB.z,
					vectA.x*vectB.y - vectA.y*vectB.x);
	double	dLen = vectN.GetLength();
	static FTVect3d vectR;
	vectR = (vectN/dLen);
	return vectR;
/*
	double dVctA[3],dVctB[3];

	dVctA[0] = pdPos2[0] - pdPos1[0];
	dVctA[1] = pdPos2[1] - pdPos1[1];
	 dVctA[2] = pdPos2[2] - pdPos1[2];
	dVctB[0] = pdPos3[0] - pdPos1[0];
	dVctB[1] = pdPos3[1] - pdPos1[1];
	dVctB[2] = pdPos3[2] - pdPos1[2];

	double dVctN[3];
	dVctN[0] = dVctA[1]*dVctB[2] - dVctA[2]*dVctB[1];
	dVctN[1] = dVctA[2]*dVctB[0] - dVctA[0]*dVctB[2];
	dVctN[2] = dVctA[0]*dVctB[1] - dVctA[1]*d VctB[0];

	double dLen = sqrt(dVctN[0] * dVctN[0] + dVctN[1] * dVctN[1] + dVctN[2] * dVctN[2] );
	if ( dLen!=0 ) {
		dVctN[0] = dVctN[0] / dLen;
		dVctN[1] = dVctN[1] / dLen;
		dVctN[2] = dVctN[2] / dLen;
	}
	glNormal3d( dVctN[0] , dVctN[1] , dVctN[2] );	
*/
}

double FTVect3d::GetLength()
{
	return sqrt( x*x + y*y + z*z );
}
