#include "AxisTransform.h"
#include "QuaternionTransform.h"


ostream& operator<<(ostream &os, XMFLOAT4X4 const& mat)
{
	return os <<
		mat._11 << '\t' << mat._12 << '\t' << mat._13 << '\t' << mat._14 << '\n' <<
		mat._21 << '\t' << mat._22 << '\t' << mat._23 << '\t' << mat._24 << '\n' <<
		mat._31 << '\t' << mat._32 << '\t' << mat._33 << '\t' << mat._34 << '\n' <<
		mat._41 << '\t' << mat._42 << '\t' << mat._43 << '\t' << mat._44 << '\n';
}

int main()
{
	AxisTransform at(XMFLOAT3(1, 1, 1), XMFLOAT3(1, 1, 1), XMFLOAT3(0, 1, 0), 0);
	QuaternionTransform qt(XMFLOAT3(1, 1, 1), XMFLOAT3(1, 1, 1), XMFLOAT4(0, 1, 0, 0));

	XMFLOAT4X4 atmat = make_worldmatrix(at);

	XMFLOAT4X4 qtmat = make_worldmatrix(qt);

	cout << "AT:\n" << atmat << "\n\n";

	cout << "QT:\n" << qtmat << "\n\n";

	char in;

	cin >> in;
}