/*
 * Copyright (c) 2019 Kevin Townsend (KTOWN)
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <ztest.h>
#include <zsl/zsl.h>
#include <zsl/matrices.h>
#include <zsl/vectors.h>
#include "floatcheck.h"

/**
 * @brief zsl_mtx_init unit tests.
 *
 * This test verifies the zsl_mtx_init function.
 */
void test_matrix_init(void)
{
	int rc;
	zsl_real_t x;

	ZSL_MATRIX_DEF(m, 3, 3);

	/* Initialise the matrix with the default (empty) entry_fn. */
	rc = zsl_mtx_init(&m, NULL);
	zassert_equal(rc, 0, NULL);

	rc = zsl_mtx_get(&m, 1, 0, &x);
	zassert_equal(rc, 0, NULL);
	zassert_equal(x, 0.0, NULL);

	rc = zsl_mtx_get(&m, 2, 2, &x);
	zassert_equal(rc, 0, NULL);
	zassert_equal(x, 0.0, NULL);

	/* Reinitialise the matrix as an identity/diagonal matrix. */
	rc = zsl_mtx_init(&m, zsl_mtx_entry_fn_identity);
	zassert_equal(rc, 0, NULL);

	rc = zsl_mtx_get(&m, 0, 0, &x);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(x, 1.0, 1E-5), NULL);

	rc = zsl_mtx_get(&m, 1, 1, &x);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(x, 1.0, 1E-5), NULL);

	rc = zsl_mtx_get(&m, 2, 2, &x);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(x, 1.0, 1E-5), NULL);

	rc = zsl_mtx_get(&m, 0, 1, &x);
	zassert_equal(x, 0.0, NULL);
	zassert_equal(rc, 0, NULL);
}

/**
 * @brief zsl_mtx_from_arr unit tests.
 *
 * This test verifies the zsl_mtx_from_arr function.
 */
void test_matrix_from_arr(void)
{
	int rc;
	zsl_real_t x;

	/* Destination matrix. */
	ZSL_MATRIX_DEF(m, 3, 3);

	/* Source array. */
	zsl_real_t data[9] = { 1.0, 0.0, 0.0,
			       0.0, 0.5, 0.0,
			       0.0, 0.0, 0.1 };

	/* Init matrix m. */
	zsl_mtx_init(&m, NULL);

	/* Initialise the matrix with the default (empty) entry_fn. */
	rc = zsl_mtx_from_arr(&m, data);
	zassert_true(rc == 0, NULL);

	rc = zsl_mtx_get(&m, 0, 0, &x);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(x, 1.0, 1E-5), NULL);

	rc = zsl_mtx_get(&m, 1, 1, &x);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(x, 0.5, 1E-5), NULL);

	rc = zsl_mtx_get(&m, 2, 2, &x);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(x, 0.1, 1E-5), NULL);

	rc = zsl_mtx_get(&m, 1, 0, &x);
	zassert_equal(rc, 0, NULL);
	zassert_equal(x, 0.0, NULL);
}

/**
 * @brief zsl_mtx_copy and zsl_mtx_is_equal unit tests.
 *
 * This test verifies the zsl_mtx_copy and zsl_mtx_is_equal functions.
 */
void test_matrix_copy(void)
{
	int rc;

	/* Source array. */
	zsl_real_t data[9] = { 1.0, 0.0, 0.0,
			       0.0, 0.5, 0.0,
			       0.0, 0.0, 0.1 };

	/* Destination matrix. */
	ZSL_MATRIX_DEF(m, 3, 3);
	zsl_mtx_init(&m, NULL);

	/* Source matrix. */
	ZSL_MATRIX_DEF(msrc, 3, 3);
	rc = zsl_mtx_from_arr(&msrc, data);
	zassert_true(rc == 0, NULL);

	/* Copy msrc to m. */
	rc = zsl_mtx_copy(&m, &msrc);
	zassert_true(rc == 0, NULL);

	/* Verify copy using zsl_mtx_is_equal. */
	zassert_true(zsl_mtx_is_equal(&m, &msrc), NULL);
}

/**
 * @brief zsl_mtx_get unit tests.
 *
 * This test verifies the zsl_mtx_get function.
 */
void test_matrix_get(void)
{
	int rc;
	zsl_real_t x;
	zsl_real_t data[9] = { 1.0, 0.0, 0.0,
			       0.0, 0.5, 0.0,
			       0.0, 0.0, 0.1 };

	struct zsl_mtx m = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = data
	};

	/* Read values from the matrix above. */
	rc = zsl_mtx_get(&m, 0, 0, &x);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(x, 1.0, 1E-5), NULL);

	rc = zsl_mtx_get(&m, 1, 0, &x);
	zassert_equal(rc, 0, NULL);
	zassert_equal(x, 0.0, NULL);

	rc = zsl_mtx_get(&m, 2, 2, &x);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(x, 0.1, 1E-5), NULL);

	/* Check for out of bounds error. */
	zassert_true(zsl_mtx_get(&m, 3, 3, &x) == -EINVAL, NULL);
}

/**
 * @brief zsl_mtx_set unit tests.
 *
 * This test verifies the zsl_mtx_set function.
 */
void test_matrix_set(void)
{
	int rc = 0;
	zsl_real_t x;

	ZSL_MATRIX_DEF(m, 3, 3);

	/* Init matrix m. */
	zsl_mtx_init(&m, NULL);

	/* Set values in matrix m. */
	rc = zsl_mtx_set(&m, 0, 0, 1.0);
	zassert_equal(rc, 0, NULL);

	rc = zsl_mtx_set(&m, 1, 1, 0.5);
	zassert_equal(rc, 0, NULL);

	rc = zsl_mtx_set(&m, 2, 2, 0.1);
	zassert_equal(rc, 0, NULL);

	/* Verify assigned values */
	rc = zsl_mtx_get(&m, 0, 0, &x);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(x, 1.0, 1E-5), NULL);

	rc = zsl_mtx_get(&m, 1, 1, &x);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(x, 0.5, 1E-5), NULL);

	rc = zsl_mtx_get(&m, 2, 2, &x);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(x, 0.1, 1E-5), NULL);

	/* Check for out of bounbds error. */
	zassert_true(zsl_mtx_set(&m, 3, 3, 0.0) == -EINVAL, NULL);
}

void test_matrix_get_set_row(void)
{
	int rc = 0;
	zsl_real_t x;
	zsl_real_t v[] = { 1.0, 2.0, 3.0 };

	ZSL_MATRIX_DEF(m, 3, 3);
	ZSL_VECTOR_DEF(v2, 3);

	/* Init matrix m. */
	zsl_mtx_init(&m, NULL);

	/* Set row 0 in m with the values in 3-vector v. */
	rc = zsl_mtx_set_row(&m, 0, v);
	zassert_equal(rc, 0, NULL);

	/* Set row 2 in m with the values in 3-vector v. */
	rc = zsl_mtx_set_row(&m, 2, v);
	zassert_equal(rc, 0, NULL);

	/* Verify row 0. */
	rc = zsl_mtx_get(&m, 0, 0, &x);
	zassert_true(val_is_equal(x, v[0], 1E-5), NULL);
	rc = zsl_mtx_get(&m, 0, 1, &x);
	zassert_true(val_is_equal(x, v[1], 1E-5), NULL);
	rc = zsl_mtx_get(&m, 0, 2, &x);
	zassert_true(val_is_equal(x, v[2], 1E-5), NULL);

	/* Verify row 1 (should be all zeroes). */
	rc = zsl_mtx_get(&m, 1, 0, &x);
	zassert_true(val_is_equal(x, 0.0, 1E-5), NULL);
	rc = zsl_mtx_get(&m, 1, 0, &x);
	zassert_true(val_is_equal(x, 0.0, 1E-5), NULL);
	rc = zsl_mtx_get(&m, 1, 0, &x);
	zassert_true(val_is_equal(x, 0.0, 1E-5), NULL);

	/* Verify row 2. */
	rc = zsl_mtx_get(&m, 2, 0, &x);
	zassert_true(val_is_equal(x, v[0], 1E-5), NULL);
	rc = zsl_mtx_get(&m, 2, 1, &x);
	zassert_true(val_is_equal(x, v[1], 1E-5), NULL);
	rc = zsl_mtx_get(&m, 2, 2, &x);
	zassert_true(val_is_equal(x, v[2], 1E-5), NULL);

	/* Now test the get method. */
	rc = zsl_vec_init(&v2);
	zassert_equal(rc, 0, NULL);

	/* Read row zero, assigning it to v2.data. */
	rc = zsl_mtx_get_row(&m, 0, v2.data);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(v2.data[0], v[0], 1E-5), NULL);
	zassert_true(val_is_equal(v2.data[1], v[1], 1E-5), NULL);
	zassert_true(val_is_equal(v2.data[2], v[2], 1E-5), NULL);
}

void test_matrix_get_set_col(void)
{
	int rc = 0;
	zsl_real_t x;
	zsl_real_t v[] = { 1.0, 2.0, 3.0 };

	ZSL_MATRIX_DEF(m, 3, 3);
	ZSL_VECTOR_DEF(v2, 3);

	/* TODO: Test get method! */

	/* Init matrix m. */
	zsl_mtx_init(&m, NULL);

	/* Set col 0 in m with the values in 3-vector v. */
	rc = zsl_mtx_set_col(&m, 0, v);
	zassert_equal(rc, 0, NULL);

	/* Set col 2 in m with the values in 3-vector v. */
	rc = zsl_mtx_set_col(&m, 2, v);
	zassert_equal(rc, 0, NULL);

	/* Verify col 0. */
	rc = zsl_mtx_get(&m, 0, 0, &x);
	zassert_true(val_is_equal(x, v[0], 1E-5), NULL);
	rc = zsl_mtx_get(&m, 1, 0, &x);
	zassert_true(val_is_equal(x, v[1], 1E-5), NULL);
	rc = zsl_mtx_get(&m, 2, 0, &x);
	zassert_true(val_is_equal(x, v[2], 1E-5), NULL);

	/* Verify col 1 (should be all zeroes). */
	rc = zsl_mtx_get(&m, 0, 1, &x);
	zassert_true(val_is_equal(x, 0.0, 1E-5), NULL);
	rc = zsl_mtx_get(&m, 1, 1, &x);
	zassert_true(val_is_equal(x, 0.0, 1E-5), NULL);
	rc = zsl_mtx_get(&m, 2, 1, &x);
	zassert_true(val_is_equal(x, 0.0, 1E-5), NULL);

	/* Verify col 2. */
	rc = zsl_mtx_get(&m, 0, 2, &x);
	zassert_true(val_is_equal(x, v[0], 1E-5), NULL);
	rc = zsl_mtx_get(&m, 1, 2, &x);
	zassert_true(val_is_equal(x, v[1], 1E-5), NULL);
	rc = zsl_mtx_get(&m, 2, 2, &x);
	zassert_true(val_is_equal(x, v[2], 1E-5), NULL);

	/* Now test the get method. */
	rc = zsl_vec_init(&v2);
	zassert_equal(rc, 0, NULL);

	/* Read row zero, assigning it to v2.data. */
	rc = zsl_mtx_get_col(&m, 2, v2.data);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(v2.data[0], v[0], 1E-5), NULL);
	zassert_true(val_is_equal(v2.data[1], v[1], 1E-5), NULL);
	zassert_true(val_is_equal(v2.data[2], v[2], 1E-5), NULL);
}

void test_matrix_row_from_vec(void)
{
	int rc;
	zsl_real_t x;

	ZSL_VECTOR_DEF(v, 3);
	ZSL_MATRIX_DEF(m, 3, 3);

	/* Init matrix m. */
	zsl_mtx_init(&m, NULL);

	/* Assign some values to the vector. */
	v.data[0] = 1.0;
	v.data[1] = 2.0;
	v.data[2] = 3.0;

	/* Now assign the vector to matrix row 1 via the .data field. */
	rc = zsl_mtx_set_row(&m, 1, v.data);
	zassert_true(rc == 0, NULL);

	/* Make sure the row assignment worked. */
	rc = zsl_mtx_get(&m, 1, 0, &x);
	zassert_true(val_is_equal(x, v.data[0], 1E-5), NULL);
	rc = zsl_mtx_get(&m, 1, 1, &x);
	zassert_true(val_is_equal(x, v.data[1], 1E-5), NULL);
	rc = zsl_mtx_get(&m, 1, 2, &x);
	zassert_true(val_is_equal(x, v.data[2], 1E-5), NULL);

	/* Now read one back. */
	rc = zsl_mtx_get_row(&m, 0, v.data);
	zassert_true(rc == 0, NULL);

	/* Vector values should have changed to all be 0.0 now. */
	zassert_true(val_is_equal(v.data[0], 0.0, 1E-5), NULL);
	zassert_true(val_is_equal(v.data[1], 0.0, 1E-5), NULL);
	zassert_true(val_is_equal(v.data[2], 0.0, 1E-5), NULL);
}

void test_matrix_unary_op(void)
{
	int rc;

	zsl_real_t data[9] = { 1.0, 0.0, 0.0,
			       0.0, 0.5, 0.0,
			       0.0, 0.0, 0.1 };

	struct zsl_mtx m = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = data
	};

	rc = zsl_mtx_unary_op(&m, ZSL_MTX_UNARY_OP_INCREMENT);
	zassert_true(rc == 0, NULL);
	zassert_true(val_is_equal(m.data[0], 2.0, 1E-5), NULL);
	zassert_true(val_is_equal(m.data[8], 1.1, 1E-5), NULL);

	/* TODO: Test other operands! */
}

void test_matrix_unary_func(void)
{

}

void test_matrix_binary_op(void)
{
	int rc;

	ZSL_MATRIX_DEF(mc, 3, 3);

	zsl_real_t data_a[9] = { 1.0, 0.0, 0.0,
				 0.0, 0.5, 0.0,
				 0.0, 0.0, 0.1 };

	zsl_real_t data_b[9] = { 1.0, 0.0, 0.0,
				 0.0, 0.5, 0.0,
				 0.0, 0.0, 0.1 };

	struct zsl_mtx ma = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = data_a
	};

	struct zsl_mtx mb = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = data_b
	};

	/* Init matrix mc. */
	zsl_mtx_init(&mc, NULL);

	rc = zsl_mtx_binary_op(&ma, &mb, &mc, ZSL_MTX_BINARY_OP_ADD);
	zassert_true(rc == 0, NULL);
	zassert_true(val_is_equal(mc.data[0], ma.data[0] + mb.data[0], 1E-5),
		     NULL);
	zassert_true(val_is_equal(mc.data[8], ma.data[8] + mb.data[8], 1E-5),
		     NULL);

	/* TODO: Test other operands! */
}

void test_matrix_binary_func(void)
{

}

void test_matrix_add(void)
{
	int rc;
	zsl_real_t x;

	ZSL_MATRIX_DEF(mc, 3, 4);

	zsl_real_t a[12] = { 1.0, 2.0, 4.0, 7.0,
			     0.0, 0.5, 0.0, 6.2,
			     9.0, 0.8, 0.1, 0.4 };

	zsl_real_t b[12] = { 3.0, 0.0, 0.0, 5.1,
			     6.0, 2.5, 1.0, 4.4,
			     0.0, 7.0, 4.1, 2.1 };

	struct zsl_mtx ma = {
		.sz_rows = 3,
		.sz_cols = 4,
		.data = a
	};

	struct zsl_mtx mb = {
		.sz_rows = 3,
		.sz_cols = 4,
		.data = b
	};

	/* Init matrix mc. */
	rc = zsl_mtx_init(&mc, NULL);
	zassert_true(rc == 0, NULL);

	/* Add 'ma' and 'mb'. */
	rc = zsl_mtx_add(&ma, &mb, &mc);
	zassert_true(rc == 0, NULL);

	/* Check the output. */
	for (size_t g = 0; g < (ma.sz_rows * ma.sz_cols); g++) {
		x = ma.data[g] + mb.data[g];
		zassert_true(val_is_equal(mc.data[g], x, 1E-5), NULL);
	}
}

void test_matrix_add_d(void)
{

}

void test_matrix_sum_rows_d(void)
{

}

void test_matrix_sum_rows_scaled_d(void)
{

}

void test_matrix_sub(void)
{

}

void test_matrix_sub_d(void)
{

}

/**
 * @brief zsl_mtx_mult unit tests with square matrices.
 *
 * This test verifies the zsl_mtx_mult function with square matrices.
 */
void test_matrix_mult_sq(void)
{
	int rc = 0;

	ZSL_MATRIX_DEF(mc, 3, 3);

	/* Input matrix a. */
	zsl_real_t data_a[9] = { 1.0, 2.0, 3.0,
				 4.0, 5.0, 6.0,
				 7.0, 8.0, 9.0 };
	struct zsl_mtx ma = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = data_a
	};

	/* Input matrix b. */
	zsl_real_t data_b[9] = { 10.0, 20.0, 30.0,
				 40.0, 50.0, 60.0,
				 70.0, 80.0, 90.0 };
	struct zsl_mtx mb = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = data_b
	};

	/* Init matrix mc. */
	zsl_mtx_init(&mc, NULL);

	/* Output reference matrix (for comparison). */
	zsl_real_t data_ref[9] = { 300.0,  360.0,  420.0,
				   660.0,  810.0,  960.0,
				   1020.0, 1260.0, 1500.0 };
	struct zsl_mtx mref = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = data_ref
	};

	/* Perform a valid 3x3 square matrix multiplication. */
	rc = zsl_mtx_mult(&ma, &mb, &mc);
	zassert_equal(rc, 0, NULL);
	zassert_equal(mref.data[0], mc.data[0], NULL);
	zassert_equal(mref.data[1], mc.data[1], NULL);
	zassert_equal(mref.data[2], mc.data[2], NULL);
	zassert_equal(mref.data[3], mc.data[3], NULL);
	zassert_equal(mref.data[4], mc.data[4], NULL);
	zassert_equal(mref.data[5], mc.data[5], NULL);
	zassert_equal(mref.data[6], mc.data[6], NULL);
	zassert_equal(mref.data[7], mc.data[7], NULL);
	zassert_equal(mref.data[8], mc.data[8], NULL);
}

/**
 * @brief zsl_mtx_mult unit tests with rectangular matrices.
 *
 * This test verifies the zsl_mtx_mult function with rectangular matrices.
 */
void test_matrix_mult_rect(void)
{
	int rc = 0;

	ZSL_MATRIX_DEF(mc, 4, 3);
	ZSL_MATRIX_DEF(merr, 5, 3);

	/* Init matrix mc, merr */
	zsl_mtx_init(&mc, NULL);
	zsl_mtx_init(&merr, NULL);

	/* Input matrix a (4x2). */
	zsl_real_t data_a[8] = { 2.0, 3.0,
				 1.0, 4.0,
				 4.0, 3.0,
				 3.0, 4.0 };
	struct zsl_mtx ma = {
		.sz_rows = 4,
		.sz_cols = 2,
		.data = data_a
	};

	/* Input matrix b (2x3). */
	zsl_real_t data_b[9] = { 3.0, 1.0, 2.0,
				 2.0, 4.0, 2.0 };
	struct zsl_mtx mb = {
		.sz_rows = 2,
		.sz_cols = 3,
		.data = data_b
	};

	/* Output reference matrix (4x3). */
	zsl_real_t data_ref[12] = { 12.0, 14.0, 10.0,
				    11.0, 17.0, 10.0,
				    18.0, 16.0, 14.0,
				    17.0, 19.0, 14.0 };
	struct zsl_mtx mref = {
		.sz_rows = 4,
		.sz_cols = 3,
		.data = data_ref
	};

	/* Attempt an invalid 4x2 x 5x3 matrix multiplication. */
	rc = zsl_mtx_mult(&merr, &mb, &mc);
	zassert_equal(rc, -EINVAL, NULL);

	/* Perform a valid 3x3 square matrix multiplication. */
	rc = zsl_mtx_mult(&ma, &mb, &mc);
	zassert_equal(rc, 0, NULL);
	zassert_equal(mref.data[0], mc.data[0], NULL);
	zassert_equal(mref.data[1], mc.data[1], NULL);
	zassert_equal(mref.data[2], mc.data[2], NULL);
	zassert_equal(mref.data[3], mc.data[3], NULL);
	zassert_equal(mref.data[4], mc.data[4], NULL);
	zassert_equal(mref.data[5], mc.data[5], NULL);
	zassert_equal(mref.data[6], mc.data[6], NULL);
	zassert_equal(mref.data[7], mc.data[7], NULL);
	zassert_equal(mref.data[8], mc.data[8], NULL);
	zassert_equal(mref.data[9], mc.data[9], NULL);
	zassert_equal(mref.data[10], mc.data[10], NULL);
	zassert_equal(mref.data[11], mc.data[11], NULL);
}

/**
 * @brief zsl_mtx_scalar_mult_d unit tests.
 *
 * This test verifies the zsl_mtx_scalar_mult_d function.
 */
void test_matrix_scalar_mult_d(void)
{
	int rc = 0;
	zsl_real_t s = 10.0;

	/* Input matrix. */
	zsl_real_t data[8] = { 2.0, 3.0,
			       1.0, 4.0,
			       4.0, 3.0,
			       3.0, 4.0 };
	struct zsl_mtx m = {
		.sz_rows = 4,
		.sz_cols = 2,
		.data = data
	};

	rc = zsl_mtx_scalar_mult_d(&m, s);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(m.data[0], 20.0, 1E-5), NULL);
	zassert_true(val_is_equal(m.data[1], 30.0, 1E-5), NULL);
	zassert_true(val_is_equal(m.data[2], 10.0, 1E-5), NULL);
	zassert_true(val_is_equal(m.data[3], 40.0, 1E-5), NULL);
	zassert_true(val_is_equal(m.data[4], 40.0, 1E-5), NULL);
	zassert_true(val_is_equal(m.data[5], 30.0, 1E-5), NULL);
	zassert_true(val_is_equal(m.data[6], 30.0, 1E-5), NULL);
	zassert_true(val_is_equal(m.data[7], 40.0, 1E-5), NULL);
}

void test_matrix_scalar_mult_row_d(void)
{

}

/**
 * @brief zsl_mtx_scalar_trans unit tests.
 *
 * This test verifies the zsl_mtx_trans function.
 */
void test_matrix_trans(void)
{
	int rc = 0;

	ZSL_MATRIX_DEF(mt, 2, 4);

	/* Input matrix. */
	zsl_real_t data[8] = { 2.0, 3.0,
			       1.0, 4.0,
			       4.0, 3.0,
			       3.0, 4.0 };
	struct zsl_mtx m = {
		.sz_rows = 4,
		.sz_cols = 2,
		.data = data
	};

	/* Init matrix mt. */
	zsl_mtx_init(&mt, NULL);

	rc = zsl_mtx_trans(&m, &mt);
	zassert_equal(rc, 0, NULL);
	zassert_equal(mt.sz_cols, m.sz_rows, NULL);
	zassert_equal(mt.sz_rows, m.sz_cols, NULL);
	zassert_true(val_is_equal(mt.data[0], 2.0, 1E-5), NULL);
	zassert_true(val_is_equal(mt.data[1], 1.0, 1E-5), NULL);
	zassert_true(val_is_equal(mt.data[2], 4.0, 1E-5), NULL);
	zassert_true(val_is_equal(mt.data[3], 3.0, 1E-5), NULL);
	zassert_true(val_is_equal(mt.data[4], 3.0, 1E-5), NULL);
	zassert_true(val_is_equal(mt.data[5], 4.0, 1E-5), NULL);
	zassert_true(val_is_equal(mt.data[6], 3.0, 1E-5), NULL);
	zassert_true(val_is_equal(mt.data[7], 4.0, 1E-5), NULL);
}

void test_matrix_adjoint_3x3(void)
{

}

void test_matrix_adjoint(void)
{

}

void test_matrix_reduce(void)
{

}

void test_matrix_reduce_iter(void)
{

}

void test_matrix_augm_diag(void)
{

}

void test_matrix_deter_3x3(void)
{

}

void test_matrix_deter(void)
{

}

void test_matrix_gauss_elim(void)
{

}

void test_matrix_gauss_elim_d(void)
{

}

void test_matrix_gauss_reduc(void)
{

}

void test_matrix_cols_norm(void)
{

}

void test_matrix_norm_elem(void)
{

}

void test_matrix_norm_elem_d(void)
{

}

void test_matrix_inv_3x3(void)
{
	int rc = 0;

	ZSL_MATRIX_DEF(mi, 3, 3);

	/* Input matrix. */
	zsl_real_t data[9] = {  67.5,  43.0,  31.5,
				226.5, 256.5,  94.5,
				226.5, 415.0, 302.0 };
	struct zsl_mtx m = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = data
	};

	/* Init matrix mi. */
	zsl_mtx_init(&mi, NULL);

	rc = zsl_mtx_inv_3x3(&m, &mi);
	zassert_equal(rc, 0, NULL);
	zassert_true(val_is_equal(mi.data[0],  0.02261063, 1E-6), NULL);
	zassert_true(val_is_equal(mi.data[1],  0.00005114, 1E-6), NULL);
	zassert_true(val_is_equal(mi.data[2], -0.00237440, 1E-6), NULL);
	zassert_true(val_is_equal(mi.data[3], -0.02778553, 1E-6), NULL);
	zassert_true(val_is_equal(mi.data[4],  0.00783351, 1E-6), NULL);
	zassert_true(val_is_equal(mi.data[5],  0.00044695, 1E-6), NULL);
	zassert_true(val_is_equal(mi.data[6],  0.02122413, 1E-6), NULL);
	zassert_true(val_is_equal(mi.data[7], -0.01080295, 1E-6), NULL);
	zassert_true(val_is_equal(mi.data[8],  0.00447788, 1E-6), NULL);
}

void test_matrix_inv(void)
{
	int rc = 0;

	ZSL_MATRIX_DEF(mi, 5, 5);

	/* Input matrix. */
	zsl_real_t data[25] = { 1.0, 1.0, 2.0, 2.0, 1.0,
				0.0, 0.0, 0.0, 1.0, 2.0,
				0.0, 0.0, 1.0, 2.0, 2.0,
				0.0, 0.0, 1.0, 1.0, 2.0,
				0.0, 1.0, 1.0, 2.0, 1.0 };
	struct zsl_mtx m = {
		.sz_rows = 5,
		.sz_cols = 5,
		.data = data
	};

	/* The inverse of data for test purposes. */
	zsl_real_t dtst[25] = {  1.0,  1.0,  0.0, -1.0, -1.0,
				 0.0,  0.5, -1.5,  0.5,  1.0,
				 0.0, -1.0,  0.0,  1.0,  0.0,
				 -0.0, -0.0,  1.0, -1.0, -0.0,
				 -0.0,  0.5, -0.5,  0.5, -0.0 };
	struct zsl_mtx mtst = {
		.sz_rows = 5,
		.sz_cols = 5,
		.data = dtst
	};

	/* Init matrix mi. */
	zsl_mtx_init(&mi, NULL);

	rc = zsl_mtx_inv(&m, &mi);
	zassert_equal(rc, 0, NULL);
	zassert_true(zsl_mtx_is_equal(&mi, &mtst), NULL);
}

void test_matrix_balance(void)
{
	int rc;

	ZSL_MATRIX_DEF(moa, 4, 4);
	ZSL_MATRIX_DEF(mob, 4, 4);

	/* Input non-symmetric matrix. */
	zsl_real_t data[16] = { 5.1, -3.2, 4.9, -8.1,
				2.3, -4.1, -2.8, 0.2,
				0.0, -7.7, 2.1, 0.0,
				-0.7, 8.1, -5.5, 3.7 };

	struct zsl_mtx ma = {
		.sz_rows = 4,
		.sz_cols = 4,
		.data = data
	};

	/* Input symmetric matrix. */
	zsl_real_t datb[16] = { 5.1, 2.3, 0.0, -8.1,
				2.3, -4.1, -2.8, 0.2,
				0.0, -2.8, 2.1, -5.5,
				-8.1, 0.2, -5.5, 3.7 };

	struct zsl_mtx mb = {
		.sz_rows = 4,
		.sz_cols = 4,
		.data = datb
	};

	/* Expected output. */
	zsl_real_t dt[16] = { 5.1, -1.6, 2.45, -8.1,
			      4.6, -4.1, -2.8, 0.4,
			      0.0, -7.7, 2.1, 0.0,
			      -0.7, 4.05, -2.75, 3.7 };

	struct zsl_mtx mt = {
		.sz_rows = 4,
		.sz_cols = 4,
		.data = dt
	};

	/* Init output matrices. */
	rc = zsl_mtx_init(&moa, NULL);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_init(&mob, NULL);
	zassert_equal(rc, 0, NULL);

	/* Balance the input matrices. */
	rc = zsl_mtx_balance(&ma, &moa);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_balance(&mb, &mob);
	zassert_equal(rc, 0, NULL);

	/* Check the output. */
	for (size_t g = 0; g < (ma.sz_rows * ma.sz_cols); g++) {
		zassert_true(val_is_equal(moa.data[g], mt.data[g], 1E-6), NULL);
		zassert_true(val_is_equal(mob.data[g], mb.data[g], 1E-6), NULL);
	}
}

void test_matrix_householder_sq(void)
{
	int rc;

	ZSL_MATRIX_DEF(h, 3, 3);

	/* Input matrix. */
	zsl_real_t data[9] = { 0.0, 0.0, 4.0,
			       2.0, 4.0, -2.0,
			       0.0, 4.0, 2.0 };

	struct zsl_mtx m = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = data
	};

	/* The holseholder matrix data for test purposes. */
	zsl_real_t dtst[9] = { 0.0, 1.0, 0.0,
			       1.0, 0.0, 0.0,
			       0.0, 0.0, 1.0 };

	struct zsl_mtx mt = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = dtst
	};

	/* Init matrix h. */
	rc = zsl_mtx_init(&h, NULL);
	zassert_equal(rc, 0, NULL);

	/* Compute the Householder matrix. */
	rc = zsl_mtx_householder(&m, &h, false);
	zassert_equal(rc, 0, NULL);

	/* Check the output. */
	for (size_t g = 0; g < (m.sz_rows * m.sz_cols); g++) {
		zassert_true(val_is_equal(h.data[g], mt.data[g], 1E-6), NULL);
	}
}

void test_matrix_householder_rect(void)
{
	int rc;

	ZSL_MATRIX_DEF(h, 4, 4);

	/* Input matrix. */
	zsl_real_t data[12] = { 1.0, -1.0, 4.0,
				1.0, 4.0, -2.0,
				1.0, 4.0, 2.0,
				1.0, -1.0, 0.0 };

	struct zsl_mtx m = {
		.sz_rows = 4,
		.sz_cols = 3,
		.data = data
	};

	/* The holseholder matrix data for test purposes. */
	zsl_real_t dtst[16] = { 0.5, 0.5, 0.5, 0.5,
				0.5, 0.5, -0.5, -0.5,
				0.5, -0.5, 0.5, -0.5,
				0.5, -0.5, -0.5, 0.5 };

	struct zsl_mtx mt = {
		.sz_rows = 4,
		.sz_cols = 4,
		.data = dtst
	};

	/* Init matrix h. */
	rc = zsl_mtx_init(&h, NULL);
	zassert_equal(rc, 0, NULL);

	/* Compute the Householder matrix. */
	rc = zsl_mtx_householder(&m, &h, false);
	zassert_equal(rc, 0, NULL);

	/* Check the output. */
	zassert_true(zsl_mtx_is_equal(&h, &mt), NULL);
}

void test_matrix_qrd(void)
{
	int rc;

	ZSL_MATRIX_DEF(q, 3, 3);
	ZSL_MATRIX_DEF(r, 3, 3);

	/* Input matrix. */
	zsl_real_t data[9] = { 0.0, 0.0, 4.0,
			       2.0, 4.0, -2.0,
			       0.0, 4.0, 2.0 };

	struct zsl_mtx m = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = data
	};

	/* The expected results for Q and R matrices for test purposes. */
	zsl_real_t qdata[9] = { 0.0, 0.0, 1.0,
				1.0, 0.0, 0.0,
				0.0, 1.0, 0.0 };

	struct zsl_mtx q2 = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = qdata
	};

	zsl_real_t rdata[9] = { 2.0, 4.0, -2.0,
				0.0, 4.0, 2.0,
				0.0, 0.0, 4.0 };

	struct zsl_mtx r2 = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = rdata
	};


	/* Init matrices Q and R. */
	rc = zsl_mtx_init(&q, NULL);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_init(&r, NULL);
	zassert_equal(rc, 0, NULL);

	/* Calculate the QR decomposition. */
	rc = zsl_mtx_qrd(&m, &q, &r, false);
	zassert_equal(rc, 0, NULL);

	/* Check the output. */
	for (size_t g = 0; g < (m.sz_rows * m.sz_cols); g++) {
		zassert_true(val_is_equal(q.data[g], q2.data[g], 1E-6), NULL);
		zassert_true(val_is_equal(r.data[g], r2.data[g], 1E-6), NULL);

	}
}

#ifndef CONFIG_ZSL_SINGLE_PRECISION
void test_matrix_qrd_iter(void)
{
	int rc;

	ZSL_MATRIX_DEF(m2, 4, 4);
	ZSL_VECTOR_DEF(v, 4);
	ZSL_VECTOR_DEF(v2, 4);

	/* Input matrix. */
	zsl_real_t data[16] = { 1.0, 2.0, -1.0, 0.0,
				0.0, 3.0, 4.0, -2.0,
				4.0, 4.0, -3.0, 0.0,
				5.0, 3.0, -5.0, 2.0 };

	struct zsl_mtx m = {
		.sz_rows = 4,
		.sz_cols = 4,
		.data = data
	};

	/* Init the output matrix. */
	rc = zsl_mtx_init(&m2, NULL);
	zassert_equal(rc, 0, NULL);

	/* Perform the QR method 1500 times matrix. */
	rc = zsl_mtx_qrd_iter(&m, &m2, 1500);
	zassert_equal(rc, 0, NULL);

	/* Check if the output matrix is upper triangular and if it is similar
	 * to the input matrix. */
	zassert_true(val_is_equal(m2.data[4], 0.0, 1E-6), NULL);
	zassert_true(val_is_equal(m2.data[8], 0.0, 1E-6), NULL);
	zassert_true(val_is_equal(m2.data[9], 0.0, 1E-6), NULL);
	zassert_true(val_is_equal(m2.data[12], 0.0, 1E-6), NULL);
	zassert_true(val_is_equal(m2.data[13], 0.0, 1E-6), NULL);
	zassert_true(val_is_equal(m2.data[14], 0.0, 1E-6), NULL);

	zsl_mtx_eigenvalues(&m, &v, 500);
	zsl_mtx_eigenvalues(&m2, &v2, 500);

	zassert_true(zsl_vec_is_equal(&v, &v2, 1E-6), NULL);
}
#endif

#ifndef CONFIG_ZSL_SINGLE_PRECISION
void test_matrix_eigenvalues(void)
{
	int rc;

	ZSL_VECTOR_DEF(va, 4);
	ZSL_VECTOR_DEF(vb, 4);
	ZSL_VECTOR_DEF(vc, 4);

	ZSL_VECTOR_DEF(va2, 4);
	ZSL_VECTOR_DEF(vb2, 2);
	ZSL_VECTOR_DEF(vc2, 4);

	/* Input real-eigenvalue matrix. */
	zsl_real_t data[16] = { 1.0, 2.0, -1.0, 0.0,
				0.0, 3.0, 4.0, -2.0,
				4.0, 4.0, -3.0, 0.0,
				5.0, 3.0, -5.0, 2.0 };

	struct zsl_mtx ma = {
		.sz_rows = 4,
		.sz_cols = 4,
		.data = data
	};

	/* Input complex-eigenvalue matrix. */
	zsl_real_t datb[16] = { 1.0, 2.0, -1.0, 0.0,
				0.0, 3.0, 4.0, -2.0,
				4.0, 4.0, -3.0, 0.0,
				9.0, 3.0, -5.0, 2.0 };

	struct zsl_mtx mb = {
		.sz_rows = 4,
		.sz_cols = 4,
		.data = datb
	};

	/* Input symmetric matrix. */
	zsl_real_t datc[16] = { 1.0, 2.0, 4.0, 0.0,
				2.0, 3.0, 4.0, -2.0,
				4.0, 4.0, -3.0, 5.0,
				0.0, -2.0, 5.0, -1.0 };

	struct zsl_mtx mc = {
		.sz_rows = 4,
		.sz_cols = 4,
		.data = datc
	};

	/* Expected output. */
	va2.data[0] = 4.8347780554139375;
	va2.data[1] = -2.6841592178899276;
	va2.data[2] = 1.8493811427083884;
	va2.data[3] = -0.9999999802303374;

	vb2.data[0] = -3.0925670160610634;
	vb2.data[1] = -1.0000000075030784;

	vc2.data[0] = -9.2890349032381003;
	vc2.data[1] = 7.4199113544017665;
	vc2.data[2] = 2.7935849909013921;
	vc2.data[3] = -0.9244614420638188;


	/* Init the output vectors. */
	rc = zsl_vec_init(&va);
	zassert_equal(rc, 0, NULL);
	rc = zsl_vec_init(&vb);
	zassert_equal(rc, 0, NULL);
	rc = zsl_vec_init(&vc);
	zassert_equal(rc, 0, NULL);

	/* Calculate the eigenvalues of 'ma', 'mb' and 'mc'. */
	rc = zsl_mtx_eigenvalues(&ma, &va, 150);
	zassert_equal(rc, 0, NULL);

	rc = zsl_mtx_eigenvalues(&mb, &vb, 150);
	zassert_equal(rc, -ECOMPLEXVAL, NULL);

	rc = zsl_mtx_eigenvalues(&mc, &vc, 150);
	zassert_equal(rc, 0, NULL);

	/* Check the output. */
	zassert_true(zsl_vec_is_equal(&va, &va2, 1E-6), NULL);
	zassert_true(zsl_vec_is_equal(&vb, &vb2, 1E-6), NULL);
	zassert_true(zsl_vec_is_equal(&vc, &vc2, 1E-6), NULL);
}
#endif

void test_matrix_gram_schmidt(void)
{
	int rc;

	ZSL_MATRIX_DEF(mot, 3, 3);

	/* Input matrix. */
	zsl_real_t data[9] = { 1.0, 5.0, -1.0,
			       2.0, -4.0, -2.0,
			       4.0, 3.0, 0.0 };

	struct zsl_mtx m = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = data
	};

	/* Expected output. */
	zsl_real_t dtst[9] = { 1.0, 4.5714285714, -1.2714138287,
			       2.0, -4.8571428571, -0.9824561404,
			       4.0, 1.2857142857, 0.8090815273 };

	struct zsl_mtx mt = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = dtst
	};

	/* Init matrix mot. */
	rc = zsl_mtx_init(&mot, NULL);
	zassert_equal(rc, 0, NULL);

	/* Perform the Gram-Schmidt process. */
	rc = zsl_mtx_gram_schmidt(&m, &mot);
	zassert_equal(rc, 0, NULL);

	/* Check the output. */
	for (size_t g = 0; g < (m.sz_rows * m.sz_cols); g++) {
		zassert_true(val_is_equal(mot.data[g], mt.data[g], 1E-6), NULL);
	}
}

#ifndef CONFIG_ZSL_SINGLE_PRECISION
void test_matrix_eigenvectors(void)
{
	int rc;

	ZSL_MATRIX_DEF(va, 4, 4);
	ZSL_MATRIX_DEF(vb, 4, 4);
	ZSL_MATRIX_DEF(vc, 4, 4);

	ZSL_MATRIX_DEF(va2, 4, 4);
	ZSL_MATRIX_DEF(vb2, 4, 2);
	ZSL_MATRIX_DEF(vc2, 4, 2);

	/* Input real-eigenvalue matrix. */
	zsl_real_t data[16] = { 1.0, 2.0, -1.0, 0.0,
				0.0, 3.0, 4.0, -2.0,
				4.0, 4.0, -3.0, 0.0,
				5.0, 3.0, -5.0, 2.0 };

	struct zsl_mtx ma = {
		.sz_rows = 4,
		.sz_cols = 4,
		.data = data
	};

	/* Input complex-eigenvalue matrix. */
	zsl_real_t datb[16] = { 1.0, 2.0, -1.0, 0.0,
				0.0, 3.0, 4.0, -2.0,
				4.0, 4.0, -3.0, 0.0,
				9.0, 3.0, -5.0, 2.0 };

	struct zsl_mtx mb = {
		.sz_rows = 4,
		.sz_cols = 4,
		.data = datb
	};

	/* Input real-eigenvalue matrix with repeated eigenvalues. */
	zsl_real_t datc[16] = { 1.0, 2.0, 4.0, 0.0,
				0.0, 3.0, 4.0, -2.0,
				0.0, 0.0, 3.0, 5.0,
				0.0, 0.0, 0.0, 1.0 };

	struct zsl_mtx mc = {
		.sz_rows = 4,
		.sz_cols = 4,
		.data = datc
	};

	/* Init the output matrices. */
	rc = zsl_mtx_init(&va, NULL);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_init(&vb, NULL);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_init(&vb, NULL);
	zassert_equal(rc, 0, NULL);

	/* Calculate the eigenvectors of 'ma', 'mb' and 'mc'
	 * non-orthonormalised. */
	rc = zsl_mtx_eigenvectors(&ma, &va, 1500, false);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_eigenvectors(&mb, &vb, 1500, false);
	zassert_equal(rc, -EEIGENSIZE, NULL);
	rc = zsl_mtx_eigenvectors(&mc, &vc, 1500, false);
	zassert_equal(rc, -EEIGENSIZE, NULL);

	/* Expected output. */
	zsl_real_t a[16] = {
		0.7555042357,  0.6223771803,  0.2074844660,  5.5000009316,
		2.2040997676, -0.5240911326,  0.2956011625, -3.5000005906,
		1.5110084714,  1.2447543606,  0.4149689321,  4.0000005733,
		1.0000000000,  1.0000000000,  1.0000000000,  1.0000000000
	};

	zsl_real_t b[8] = { 1.2304303063, -0.5000000054,
			    -1.2873789372, 0.5000000045,
			    2.4608606125, -0.0000000055,
			    1.0000000000, 1.0000000000 };

	zsl_real_t c[8] = { 1.0, 1.0,
			    0.0, 1.0,
			    0.0, 0.0,
			    0.0, 0.0 };

	rc = zsl_mtx_from_arr(&va2, a);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_from_arr(&vb2, b);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_from_arr(&vc2, c);
	zassert_equal(rc, 0, NULL);

	/* Check the output. */
	for (size_t g = 0; g < (va.sz_rows * va.sz_cols); g++) {
		zassert_true(val_is_equal(va.data[g], va2.data[g], 1E-6), NULL);
	}

	for (size_t g = 0; g < (vb.sz_rows * vb.sz_cols); g++) {
		// zassert_true(val_is_equal(vb.data[g], vb2.data[g], 1E-6), NULL);
		// zassert_true(val_is_equal(vc.data[g], vc2.data[g], 1E-6), NULL);
	}

	/* Calculate the eigenvectors of 'ma', 'mb' and 'mc' orthonormalised. */
	rc = zsl_mtx_eigenvectors(&ma, &va, 1500, true);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_eigenvectors(&mb, &vb, 1500, true);
	zassert_equal(rc, -EEIGENSIZE, NULL);
	rc = zsl_mtx_eigenvectors(&mc, &vc, 1500, true);
	zassert_equal(rc, -EEIGENSIZE, NULL);

	/* Expected output. */
	zsl_real_t a2[16] = {
		0.2559636199, 0.3472992698, 0.1817921832, 0.7130241030,
		0.7467454562, -0.2924536333, 0.2589976094, -0.4537426107,
		0.5119272398, 0.6945985397, 0.3635843664, 0.5185629705,
		0.3387983916, 0.5580205715, 0.8761724995, 0.1296407240
	};


	zsl_real_t b2[8] = { 0.3847511767, -0.4082482935,
			     -0.4025588109, 0.4082482928,
			     0.7695023535, -0.0000000045,
			     0.3126964402, 0.8164965782 };

	zsl_real_t c2[8] = { 1.0, 0.7071067812,
			     0.0, 0.7071067812,
			     0.0, 0.0,
			     0.0, 0.0 };

	rc = zsl_mtx_from_arr(&va2, a2);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_from_arr(&vb2, b2);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_from_arr(&vc2, c2);
	zassert_equal(rc, 0, NULL);

	/* Check the output. */
	for (size_t g = 0; g < (va.sz_rows * va.sz_cols); g++) {
		zassert_true(val_is_equal(va.data[g], va2.data[g], 1E-6), NULL);
	}
	for (size_t g = 0; g < (vb.sz_rows * vb.sz_cols); g++) {
		zassert_true(val_is_equal(vb.data[g], vb2.data[g], 1E-6), NULL);
		zassert_true(val_is_equal(vc.data[g], vc2.data[g], 1E-6), NULL);
	}
}
#endif

#ifndef CONFIG_ZSL_SINGLE_PRECISION
void test_matrix_svd(void)
{
	int rc;

	ZSL_MATRIX_DEF(u, 3, 3);
	ZSL_MATRIX_DEF(e, 3, 4);
	ZSL_MATRIX_DEF(v, 4, 4);

	ZSL_MATRIX_DEF(u2, 3, 3);
	ZSL_MATRIX_DEF(e2, 3, 4);
	ZSL_MATRIX_DEF(v2, 4, 4);

	/* Input  matrix. */
	zsl_real_t data[12] = { 1.0, 2.0, -1.0, 0.0,
				0.0, 3.0, 4.0, -2.0,
				4.0, 4.0, -3.0, 0.0 };

	struct zsl_mtx m = {
		.sz_rows = 3,
		.sz_cols = 4,
		.data = data
	};

	/* Init the output matrices. */
	rc = zsl_mtx_init(&u, NULL);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_init(&e, NULL);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_init(&v, NULL);
	zassert_equal(rc, 0, NULL);

	/* Calculate the svd of 'm'. */
	rc = zsl_mtx_svd(&m, &u, &e, &v, 1500);
	zassert_equal(rc, 0, NULL);

	/* Expected output. */
	zsl_real_t a[9] = { -0.3481845133, -0.0474852763, 0.9362225661,
			    -0.0396196056, -0.9970784021, -0.0653065614,
			    -0.9365884003, 0.0598315021, -0.3452859102 };

	zsl_real_t b[12] = { 6.8246886030, 0.0, 0.0, 0.0,
			     0.0, 5.3940011894, 0.0, 0.0,
			     0.0, 0.0, 0.5730415692, 0.0 };

	zsl_real_t c[16] = { -0.5999596982, 0.0355655710, -0.7764202435,
			     0.1896181853, -0.6683940777, -0.5277862667, 0.5154631408, 0.0948090926,
			     0.4395030259, -0.7638713255, -0.2819884104, 0.3792363705, 0.0116106706,
			     0.3696989923, 0.2279295777, 0.9006863800 };

	rc = zsl_mtx_from_arr(&u2, a);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_from_arr(&e2, b);
	zassert_equal(rc, 0, NULL);
	rc = zsl_mtx_from_arr(&v2, c);
	zassert_equal(rc, 0, NULL);

	/* Check the output. */
	for (size_t g = 0; g < (u.sz_rows * u.sz_cols); g++) {
		zassert_true(val_is_equal(u.data[g], u2.data[g], 1E-8), NULL);
	}

	for (size_t g = 0; g < (e.sz_rows * e.sz_cols); g++) {
		zassert_true(val_is_equal(e.data[g], e2.data[g], 1E-8), NULL);
	}

	for (size_t g = 0; g < (v.sz_rows * v.sz_cols); g++) {
		zassert_true(val_is_equal(v.data[g], v2.data[g], 1E-8), NULL);
	}
}
#endif


#ifndef CONFIG_ZSL_SINGLE_PRECISION
void test_matrix_pinv(void)
{
	int rc;

	ZSL_MATRIX_DEF(pinv, 4, 3);

	ZSL_MATRIX_DEF(pinv2, 4, 3);

	/* Input  matrix. */
	zsl_real_t data[12] = { 1.0, 2.0, -1.0, 0.0,
				0.0, 3.0, 4.0, -2.0,
				4.0, 4.0, -3.0, 0.0 };

	struct zsl_mtx m = {
		.sz_rows = 3,
		.sz_cols = 4,
		.data = data
	};

	/* Init the output matrix. */
	rc = zsl_mtx_init(&pinv, NULL);
	zassert_equal(rc, 0, NULL);

	/* Calculate the pseudo-inverse of 'm'. */
	rc = zsl_mtx_pinv(&m, &pinv, 1500);
	zassert_equal(rc, 0, NULL);

	/* Expected output. */
	zsl_real_t a[12] = {
		-1.2382022472, 0.0853932584, 0.5505617978,
		0.8808988764, 0.0426966292, -0.2247191011,
		-0.4764044944, 0.1707865169, 0.1011235955,
		0.3685393258, -0.0943820225, -0.1348314607
	};

	rc = zsl_mtx_from_arr(&pinv2, a);
	zassert_equal(rc, 0, NULL);

	/* Check the output. */
	for (size_t g = 0; g < (pinv.sz_rows * pinv.sz_cols); g++) {
		zassert_true(val_is_equal(pinv.data[g], pinv2.data[g], 1E-8),
			     NULL);
	}
}
#endif

void test_matrix_min(void)
{
	int rc = 0;
	zsl_real_t min;

	/* Input matrix. */
	zsl_real_t data[8] = { 2.0, 3.0,
			       1.0, 4.0,
			       4.0, 3.0,
			       3.0, 4.0 };
	struct zsl_mtx m = {
		.sz_rows = 4,
		.sz_cols = 2,
		.data = data
	};

	rc = zsl_mtx_min(&m, &min);
	zassert_equal(rc, 0, NULL);
	zassert_equal(min, 1.0, NULL);
}

void test_matrix_max(void)
{
	int rc = 0;
	zsl_real_t max;

	/* Input matrix. */
	zsl_real_t data[8] = { 2.0, 3.0,
			       1.0, 4.0,
			       4.0, 3.0,
			       3.0, 4.0 };
	struct zsl_mtx m = {
		.sz_rows = 4,
		.sz_cols = 2,
		.data = data
	};

	rc = zsl_mtx_max(&m, &max);
	zassert_equal(rc, 0, NULL);
	zassert_equal(max, 4.0, NULL);
}

void test_matrix_min_idx(void)
{
	int rc = 0;
	size_t min_i;
	size_t min_j;

	/* Input matrix. */
	zsl_real_t data[8] = { 2.0, 3.0,
			       1.0, 4.0,
			       4.0, 3.0,
			       3.0, 4.0 };
	struct zsl_mtx m = {
		.sz_rows = 4,
		.sz_cols = 2,
		.data = data
	};

	rc = zsl_mtx_min_idx(&m, &min_i, &min_j);
	zassert_equal(rc, 0, NULL);
	zassert_equal(min_i, 1, NULL);
	zassert_equal(min_j, 0, NULL);
}

void test_matrix_max_idx(void)
{
	int rc = 0;
	size_t max_i;
	size_t max_j;


	/* Input matrix. */
	zsl_real_t data[8] = { 2.0, 3.0,
			       1.0, 4.0,
			       4.0, 3.0,
			       3.0, 4.0 };
	struct zsl_mtx m = {
		.sz_rows = 4,
		.sz_cols = 2,
		.data = data
	};

	rc = zsl_mtx_max_idx(&m, &max_i, &max_j);
	zassert_equal(rc, 0, NULL);
	zassert_equal(max_i, 1, NULL);
	zassert_equal(max_j, 1, NULL);
}

void test_matrix_is_equal(void)
{
	bool res;

	zsl_real_t data_a[8] = { 2.0, 3.0,
				 1.0, 4.0,
				 4.0, 3.0,
				 3.0, 4.0 };
	struct zsl_mtx ma = {
		.sz_rows = 4,
		.sz_cols = 2,
		.data = data_a
	};

	zsl_real_t data_b[8] = { 2.0, 3.0,
				 1.0, 4.0,
				 4.0, 3.0,
				 3.0, 4.0 };
	struct zsl_mtx mb = {
		.sz_rows = 4,
		.sz_cols = 2,
		.data = data_b
	};

	/* Perform a test of equal elements. */
	res = zsl_mtx_is_equal(&ma, &mb);
	zassert_equal(res, true, NULL);

	/* Perform a test of unequal elements. */
	zsl_mtx_set(&mb, 1, 1, 0.5);
	res = zsl_mtx_is_equal(&ma, &mb);
	zassert_equal(res, false, "");
}

void test_matrix_is_notneg(void)
{
	bool res;

	/* Input matrix. */
	zsl_real_t data[8] = { 2.0, 3.0,
			       1.0, 4.0,
			       4.0, 3.0,
			       3.0, 4.0 };
	struct zsl_mtx m = {
		.sz_rows = 4,
		.sz_cols = 2,
		.data = data
	};

	res = zsl_mtx_is_notneg(&m);
	zassert_equal(res, true, NULL);

	zsl_mtx_set(&m, 1, 1, -0.01);
	res = zsl_mtx_is_notneg(&m);
	zassert_equal(res, false, NULL);
}

void test_matrix_is_sym(void)
{
	bool res;

	/* Input matrixes. */
	zsl_real_t a[9] = { 2.0, 3.0, 6.0,
			    3.0, 4.0, -1.0,
			    6.0, -1.0, 0.0 };
	struct zsl_mtx ma = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = a
	};

	zsl_real_t b[9] = { 5.0, 3.0, 4.0,
			    7.0, -5.0, 0.0,
			    3.0, -2.0, 3.0 };
	struct zsl_mtx mb = {
		.sz_rows = 3,
		.sz_cols = 3,
		.data = b
	};

	/* Perform a test with a symmetric matrix. */
	res = zsl_mtx_is_sym(&ma);
	zassert_equal(res, true, NULL);

	/* Perform a test with a non-symmetric matrix. */
	res = zsl_mtx_is_sym(&mb);
	zassert_equal(res, false, NULL);
}
