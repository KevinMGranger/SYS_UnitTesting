#include "Util.h"

ostream& operator<<(ostream &os, XMFLOAT4X4 const& mat)
{
	// matrices are stored column-major
	return os <<
		mat._11 << '\t' << mat._21 << '\t' << mat._31 << '\t' << mat._41 << '\n' <<
		mat._12 << '\t' << mat._22 << '\t' << mat._32 << '\t' << mat._42 << '\n' <<
		mat._13 << '\t' << mat._23 << '\t' << mat._33 << '\t' << mat._43 << '\n' <<
		mat._14 << '\t' << mat._24 << '\t' << mat._34 << '\t' << mat._44 << '\n';
}

ostream& operator<<(ostream &os, XMFLOAT3 const& v)
{
	return os << v.x << ", " << v.y << ", " << v.z;
}

XMFLOAT4 quat_from_axis_angle(XMFLOAT3 axis, float angle)
{
	auto qr = XMQuaternionRotationAxis(XMLoadFloat3(&axis), XMConvertToRadians(angle));
	XMFLOAT4 quat;
	XMStoreFloat4(&quat, qr);
	return quat;
}

XMFLOAT3 trans(XMFLOAT4X4 const& w, XMFLOAT3 point)
{
	XMMATRIX world = XMLoadFloat4x4(&w);
	XMVECTOR pt = XMLoadFloat3(&point);

	XMVECTOR result = XMVector3Transform(pt, world);

	XMFLOAT3 res;
	XMStoreFloat3(&res, result);

	return res;
}
