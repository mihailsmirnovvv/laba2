#include "../include/matrix.h"
#include <CUnit/Basic.h>
#include <stdlib.h>

void test_matrix_creation() {
    Matrix *mat = create_matrix(3, 3);
    CU_ASSERT_PTR_NOT_NULL(mat);
    CU_ASSERT_EQUAL(mat->rows, 3);
    CU_ASSERT_EQUAL(mat->cols, 3);
    free_matrix(mat);
}

void test_sum_diagonal() {
    Matrix *mat = create_matrix(3, 3);
    for (int i = 0; i < 3; i++)
        mat->data[i][i] = i + 1;
    CU_ASSERT_EQUAL(sum_diagonal(mat), 6);
    free_matrix(mat);
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("MatrixTests", 0, 0);
    CU_add_test(suite, "Matrix Creation", test_matrix_creation);
    CU_add_test(suite, "Sum Diagonal", test_sum_diagonal);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}
