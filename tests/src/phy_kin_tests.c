/*
 * Copyright (c) 2019 Kevin Townsend (KTOWN)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>
#include <zsl/zsl.h>
#include <zsl/matrices.h>
#include <zsl/vectors.h>
#include <zsl/physics/kinematics.h>
#include "floatcheck.h"

void test_phy_kin_dist(void)
{
	int rc;
	zsl_real_t dist;

	rc = zsl_phy_kin_dist(15.0, 5.0, -2.0, &dist);
	zassert_true(rc == 0, NULL);
	zassert_true(val_is_equal(dist, 50.0, 1E-6), NULL);

	rc = zsl_phy_kin_dist(15.0, -1.0, -2.0, &dist);
	zassert_true(rc == -EINVAL, NULL);
	/* IEEE standard states that x != x is true only for NAN values. */
	zassert_true(dist != dist, NULL);
}

void test_phy_kin_time(void)
{
	int rc;
	zsl_real_t time;

	rc = zsl_phy_kin_time(15.0, 10.0, -5.0, &time);
	zassert_true(rc == 0, NULL);
	zassert_true(val_is_equal(time, 1.0, 1E-6), NULL);

	/* Case for negative time. */
	rc = zsl_phy_kin_time(15.0, 10.0, 5.0, &time);
	zassert_true(rc == -EINVAL, NULL);
	/* IEEE standard states that x != x is true only for NAN values. */
	zassert_true(time != time, NULL);

	/* Case for zero acceleration. */
	rc = zsl_phy_kin_time(15.0, 10.0, 0.0, &time);
	zassert_true(rc == -EINVAL, NULL);
	/* IEEE standard states that x != x is true only for NAN values. */
	zassert_true(time != time, NULL);
}

void test_phy_kin_vel(void)
{
	int rc;
	zsl_real_t vf;

	rc = zsl_phy_kin_vel(30.0, 10.0, -5.0, &vf);
	zassert_true(rc == 0, NULL);
	zassert_true(val_is_equal(vf, -20.0, 1E-6), NULL);

	/* Case for negative time. */
	rc = zsl_phy_kin_vel(30.0, -10.0, -5.0, &vf);
	zassert_true(rc == -EINVAL, NULL);
	/* IEEE standard states that x != x is true only for NAN values. */
	zassert_true(vf != vf, NULL);
}

void test_phy_kin_vel2(void)
{
	int rc;
	zsl_real_t vf;

	rc = zsl_phy_kin_vel2(5.0, 12.0, 6.0, &vf);
	zassert_true(rc == 0, NULL);
	zassert_true(val_is_equal(vf, 13.0, 1E-6), NULL);

	rc = zsl_phy_kin_vel2(5.0, 12.0, -6.0, &vf);
	zassert_true(rc == -EINVAL, NULL);
	/* IEEE standard states that x != x is true only for NAN values. */
	zassert_true(vf != vf, NULL);
}

void test_phy_kin_av_vel(void)
{
	int rc;
	zsl_real_t vel;

	rc = zsl_phy_kin_av_vel(15.0, 5.0, &vel);
	zassert_true(rc == 0, NULL);
	zassert_true(val_is_equal(vel, 3.0, 1E-6), NULL);

	/* Case for zero time. */
	rc = zsl_phy_kin_av_vel(15.0, 0.0, &vel);
	zassert_true(rc == -EINVAL, NULL);
	/* IEEE standard states that x != x is true only for NAN values. */
	zassert_true(vel != vel, NULL);

	/* Case for negative time. */
	rc = zsl_phy_kin_av_vel(15.0, -5.0, &vel);
	zassert_true(rc == -EINVAL, NULL);
	/* IEEE standard states that x != x is true only for NAN values. */
	zassert_true(vel != vel, NULL);
}

void test_phy_kin_accel(void)
{
	int rc;
	zsl_real_t accel;

	rc = zsl_phy_kin_accel(15.0, -5.0, 4.0, &accel);
	zassert_true(rc == 0, NULL);
	zassert_true(val_is_equal(accel, -5.0, 1E-6), NULL);

	/* Case for zero time. */
	rc = zsl_phy_kin_accel(15.0, -5.0, 0.0, &accel);
	zassert_true(rc == -EINVAL, NULL);
	/* IEEE standard states that x != x is true only for NAN values. */
	zassert_true(accel != accel, NULL);

	/* Case for negative time. */
	rc = zsl_phy_kin_accel(15.0, -5.0, -4.0, &accel);
	zassert_true(rc == -EINVAL, NULL);
	/* IEEE standard states that x != x is true only for NAN values. */
	zassert_true(accel != accel, NULL);
}

void test_phy_kin_ener(void)
{
	int rc;
	zsl_real_t ke;

	rc = zsl_phy_kin_ener(10.0, 1.1, &ke);
	zassert_true(rc == 0, NULL);
	zassert_true(val_is_equal(ke, 55.0, 1E-6), NULL);

	/* Case for zero mass. */
	rc = zsl_phy_kin_ener(10.0, 0.0, &ke);
	zassert_true(rc == -EINVAL, NULL);
	/* IEEE standard states that x != x is true only for NAN values. */
	zassert_true(ke != ke, NULL);

	/* Case for negative mass. */
	rc = zsl_phy_kin_ener(10.0, -1.1, &ke);
	zassert_true(rc == -EINVAL, NULL);
	/* IEEE standard states that x != x is true only for NAN values. */
	zassert_true(ke != ke, NULL);
}