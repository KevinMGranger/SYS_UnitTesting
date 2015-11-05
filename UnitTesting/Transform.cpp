#include "AxisTransform.h"
#include "QuaternionTransform.h"
#include "Util.h"

#include <math.h>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

XMFLOAT3 up(0, 1, 0);

SCENARIO("Quaternion and Axis-Rotation Transforms behave equivalently") {
	GIVEN("Two equivalent transforms of different rotation implementations") {

		AxisTransform at(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1), up, XMConvertToRadians(90));

		// we must convert to the equivalent quaternion-- putting the hard-coded values
		// in ourselves is counterintuitive (unless you're really good at 4D geometry)
		auto quat = quat_from_axis_angle(up, 90);
		QuaternionTransform qt(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1), quat);

		WHEN("Their world matrices are calculated") {

			auto axis_mat = make_worldmatrix(at);
			auto quat_mat = make_worldmatrix(qt);

			THEN("They should be roughly equivalent") {
				// if each respective member float is roughly equivalent, then we're good

				for (auto i = 0; i < 4; ++i) for (auto j = 0; j < 4; ++j) {
					REQUIRE(quat_mat.m[i][j] == Approx(axis_mat.m[i][j]));
				}
			}
		}
	}
}
/*
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

	cout << "AT:\n" << atmat << "\n\n";

	cout << "QT:\n" << qtmat << "\n\n";

	char in;

	cin >> in;
}
*/