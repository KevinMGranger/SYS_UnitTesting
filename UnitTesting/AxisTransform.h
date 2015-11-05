#pragma once

#include <DirectXMath.h>
#include <iostream>
using namespace std;
using namespace DirectX;

struct AxisTransform
{
	XMFLOAT3 pos, scale, axis;
	float rotation_amount;

	AxisTransform(XMFLOAT3 pos, XMFLOAT3 scale, XMFLOAT3 axis, float amount) :
		pos(pos), scale(scale), axis(axis), rotation_amount(amount) { }
};

void make_worldmatrix(AxisTransform const&, XMFLOAT4X4&);

/// rotate by a number of degrees around the current axis of rotation.
void rotate_degrees(AxisTransform &, float);

XMFLOAT4X4 make_worldmatrix(AxisTransform const&);
ostream& operator<<(ostream& os, AxisTransform const& at);