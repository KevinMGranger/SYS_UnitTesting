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