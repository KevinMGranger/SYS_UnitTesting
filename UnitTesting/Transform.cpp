#include "AxisTransform.h"
#include "QuaternionTransform.h"

#include <math.h>

ostream& operator<<(ostream &os, XMFLOAT4X4 const& mat)
{
	return os <<
		mat._11 << '\t' << mat._21 << '\t' << mat._31 << '\t' << mat._41 << '\n' <<
		mat._12 << '\t' << mat._22 << '\t' << mat._32 << '\t' << mat._42 << '\n' <<
		mat._13 << '\t' << mat._23 << '\t' << mat._33 << '\t' << mat._43 << '\n' <<
		mat._14 << '\t' << mat._24 << '\t' << mat._34 << '\t' << mat._44 << '\n';
}

ostream & operator<<(ostream &os, XMFLOAT3 const& v)
{
	return os << v.x << ", " << v.y << ", " << v.z;
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

int main()
{
	XMFLOAT3 up(0, 1, 0);

	AxisTransform at(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1), XMFLOAT3(0, 1, 0), XMConvertToRadians(90));

	auto qr = XMQuaternionRotationAxis(XMLoadFloat3(&up), XMConvertToRadians(90));
	XMFLOAT4 quat;
	XMStoreFloat4(&quat, qr);
	QuaternionTransform qt(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1), quat);

	XMFLOAT4X4 atmat = make_worldmatrix(at);

	XMFLOAT4X4 qtmat = make_worldmatrix(qt);


	auto atres = trans(atmat, XMFLOAT3(1, 1, -1));
	auto qtres = trans(qtmat, XMFLOAT3(1, 1, -1));

	cout << atres << "\t\t" << qtres << "\n\n";

	/*
	auto qtemp = XMQuaternionRotationAxis(XMLoadFloat3(&up), 90);

	XMFLOAT4 q;
	XMStoreFloat4(&q, qtemp);

	cout << "Quat: " << q.x << ' ' << q.y << ' ' << q.z << ' ' << q.w << "\n\n";
	*/

	cout << "AT:\n" << atmat << "\n\n";

	cout << "QT:\n" << qtmat << "\n\n";

	char in;

	cin >> in;
}