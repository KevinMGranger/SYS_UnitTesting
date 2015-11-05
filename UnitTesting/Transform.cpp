#include "AxisTransform.h"
#include "QuaternionTransform.h"
#include "Util.h"

#include <math.h>
#include <stdlib.h>

#include "catch.hpp"

XMFLOAT3 up(0, 1, 0);

SCENARIO("Quaternion and Axis-Rotation Transforms behave equivalently") {
	GIVEN("Two equivalent transforms of different rotation implementations") {

		AxisTransform at(XMFLOAT3(1, 1, 0), XMFLOAT3(1, 1, 1), up, 90);

		// we must convert to the equivalent quaternion-- putting the hard-coded values
		// in ourselves is counterintuitive (unless you're really good at 4D geometry)
		auto quat = quat_from_axis_angle(up, 90);
		QuaternionTransform qt(XMFLOAT3(1, 1, 0), XMFLOAT3(1, 1, 1), quat);

		WHEN("Their world matrices are calculated") {

			auto axis_mat = make_worldmatrix(at);
			auto quat_mat = make_worldmatrix(qt);

			THEN("They should be roughly equivalent") {

				// if each respective member float is roughly equivalent, then we're good
				for (auto i = 0; i < 4; ++i) for (auto j = 0; j < 4; ++j) {
					CHECK(quat_mat.m[i][j] == Approx(axis_mat.m[i][j]));
				}
			}

			THEN("They should transform points to roughly the same location") {

				XMFLOAT3 point(1, 2, 3);

				auto axis_pt = trans(axis_mat, point);
				auto quat_pt = trans(quat_mat, point);

				CHECK(quat_pt.x == Approx(axis_pt.x));
				CHECK(quat_pt.y == Approx(axis_pt.y));
				CHECK(quat_pt.z == Approx(axis_pt.z));
			}
		}

		AND_WHEN("They are further rotated") {
			// rotate randomly
			auto amount = rand() % 30;

			rotate_degrees(at, amount);
			rotate_degrees(qt, amount);

			auto axis_mat = make_worldmatrix(at);
			auto quat_mat = make_worldmatrix(qt);

			THEN("They should still be roughly equivalent") {

				// if each respective member float is roughly equivalent, then we're good
				for (auto i = 0; i < 4; ++i) for (auto j = 0; j < 4; ++j) {
					CHECK(quat_mat.m[i][j] == Approx(axis_mat.m[i][j]));
				}
			}

			THEN("They should still transform points to roughly the same location") {

				XMFLOAT3 point(1, 2, 3);

				auto axis_pt = trans(axis_mat, point);
				auto quat_pt = trans(quat_mat, point);

				CHECK(quat_pt.x == Approx(axis_pt.x));
				CHECK(quat_pt.y == Approx(axis_pt.y));
				CHECK(quat_pt.z == Approx(axis_pt.z));
			}
		}
	}
}