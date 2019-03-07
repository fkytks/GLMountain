/*	[FTEasyDI]
	ä»à’î≈Direct InputÉNÉâÉX  
	1998.01.14-  F/T
*/

class FTEasyDI {

// ê√ìIä÷êî
public:
	static UINT GetJoyStickBit( int nDev=0 );
	enum {
		JSB_UP = 0x01,
		JSB_DOWN = 0x02,
		JSB_LEFT = 0x04,
		JSB_RIGHT = 0x08,
		JSB_TR1	= 0x10,
		JSB_TR2 = 0x20
	};

	static UINT IsKeyPress( int nVKey );
};
