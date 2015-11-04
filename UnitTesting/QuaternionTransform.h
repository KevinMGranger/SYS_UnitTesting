#pragma once

#include <DirectXMath.h>
#include <iostream>
using namespace std;
using namespace DirectX;

struct QuaternionTransform
{
	XMFLOAT3 pos, scale;
	XMFLOAT4 quat;

	QuaternionTransform(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT4 quat) :
		pos(pos), scale(scale), quat(quat) { }
};

void make_worldmatrix(QuaternionTransform const&, XMFLOAT4X4&);
XMFLOAT4X4 make_worldmatrix(QuaternionTransform const&);
ostream& operator<<(ostream& os, QuaternionTransform const& at);