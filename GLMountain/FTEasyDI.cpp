/*	[FTEasyDI]
	ŠÈˆÕ”ÅDirect InputƒNƒ‰ƒX  
	1998.01.14-  F/T
*/
#include "stdafx.h"
#include "afxwin.h"
#include "mmsystem.h"

#include "FTEasyDI.h"

UINT FTEasyDI::GetJoyStickBit( int nDev )
{
	UINT uJSB = 0x00;
	uJSB |=	( IsKeyPress( VK_UP ) & JSB_UP ) |
			( IsKeyPress( VK_DOWN ) & JSB_DOWN ) |
			( IsKeyPress( VK_LEFT ) & JSB_LEFT ) |
			( IsKeyPress( VK_RIGHT ) & JSB_RIGHT ) |
			( ( IsKeyPress( 'Z' ) | IsKeyPress( VK_RETURN ) ) & JSB_TR1 ) |
			( ( IsKeyPress( 'X' ) | IsKeyPress( VK_SPACE ) ) & JSB_TR2 );

	return uJSB;
}

UINT FTEasyDI::IsKeyPress( int nVKey )
{
	return ( GetAsyncKeyState( nVKey ) & 0x8000 ? (UINT)-1 : 0 );
}
