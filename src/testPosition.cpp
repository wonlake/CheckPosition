// testPosition.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <xnamath.h>

int _tmain(int argc, _TCHAR* argv[])
{
	XMVECTOR pos = XMVectorSet(0, 100, -200, 1);
	XMVECTOR dir = XMVectorSet(0, 0, 1, 0);
	XMVECTOR up = XMVectorSet(0, 1, 0, 0);
	XMMATRIX view = XMMatrixLookToLH(pos, dir, up);
	
	XMMATRIX proj = XMMatrixPerspectiveFovLH(XM_PI / 3, 1, 10, 300);
	XMVECTOR vTest = XMVectorSet(-11.174, 111.174, -180.64516, 1);
	XMMATRIX world = XMMatrixIdentity();
	XMVECTOR vProj = XMVector3Project(vTest, 0, 0, 512, 512, 0, 1, proj, view, world);
	XMVECTOR vTest2 = XMVectorSet(0, 0, 1, 1);
	XMVECTOR vUnproj = XMVector3Unproject(vTest2, 0, 0, 512, 512, 0, 1, proj, view, world);
	vTest2 = XMVectorSet(0, 0, 0.5, 1);
	vTest = XMVector3Unproject(vTest2, 0, 0, 512, 512, 0, 1, proj, view, world);
	XMVECTOR vTest3 = XMVector3Transform(vTest, view);
	float v = XMVectorGetZ(vTest3) / 300.0;
	XMVECTOR vDir = XMVectorSubtract(pos, vUnproj);
	XMVECTOR vDir2 = XMVectorSubtract(pos, vTest);
	XMVECTOR vDirN = XMVector3Normalize(vDir);
	XMVECTOR vDir2N = XMVector3Normalize(vDir2);
	float z = 1.0 / XMVectorGetZ(vDirN);
	XMVECTOR vDirN1 = XMVectorScale(vDirN, z);
	XMVECTOR vDirN2 = XMVectorScale(vDirN1, v*300);
	XMVECTOR vDirN3 = XMVectorAdd(vDirN2, pos);
	XMVECTOR xxx = XMVectorSubtract(pos, vTest);
	XMVECTOR newXxx = XMVector3Length(xxx);
	XMVECTOR vLast = XMVectorMultiply(vDirN, newXxx);
	vLast = XMVectorSubtract(pos, vLast);

	XMMATRIX matTest = XMMatrixIdentity();
	matTest._22 = 0.0f;
	matTest._23 = 1.0f;
	matTest._32 = 1.0f;
	matTest._33 = 0.0f;
	XMVECTOR vScale = XMVectorSet(0, 0, 0, 1);
	XMVECTOR vTrans = XMVectorSet(0, 0, 0, 1);
	XMVECTOR vRot = XMVectorSet(0, 0, 0, 1);
	XMMatrixDecompose(&vScale, &vRot, &vTrans, matTest);
	return 0;
}

