#ifndef TEST_MATRIX_H
#define TEST_MATRIX_H

#include "../src/matrix/matrix.h"
#include "../src/output/output.h"
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#define EPS 1e-6

extern void all_tests(void);

int double_compare(MATRIX_TYPE a, MATRIX_TYPE b);
Matrix *create_test_matrix(int rows, int cols, MATRIX_TYPE data[]);

#endif // TEST_MATRIX_H
