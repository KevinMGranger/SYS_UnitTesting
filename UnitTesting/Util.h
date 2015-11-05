#pragma once

#include <DirectXMath.h>
#include <iostream>

using namespace std;
using namespace DirectX;

/// Translate a point through the given world matrix W.
XMFLOAT3 trans(XMFLOAT4X4 const& w, XMFLOAT3 point);

/// Make a quaternion from an axis and angle.
XMFLOAT4 quat_from_axis_angle(XMFLOAT3 axis, float angle);

/// Output the textual representation of a XMFLOAT4X4
ostream& operator<<(ostream &os, XMFLOAT4X4 const& mat);

/// Output the textual representation of a XMFLOAT3, for debugging purposes.
ostream& operator<<(ostream &os, XMFLOAT3 const& v);