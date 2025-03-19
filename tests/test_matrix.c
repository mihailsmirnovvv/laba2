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

void test_fill_matrix() {
    Matrix *mat = create_matrix(2, 2);
    fill_matrix(mat, 5.0);
    CU_ASSERT_EQUAL(mat->data[0][0], 5.0);
    CU_ASSERT_EQUAL(mat->data[1][1], 5.0);
    free_matrix(mat);
}

void test_sum_diagonal() {
    Matrix *mat = create_matrix(3, 3);
    for (int i = 0; i < 3; i++)
        mat->data[i][i] = i + 1;
    CU_ASSERT_EQUAL(sum_diagonal(mat), 6.0);
    free_matrix(mat);
}

void test_add_matrices() {
    Matrix *A = create_matrix(2, 2);
    Matrix *B = create_matrix(2, 2);
    fill_matrix(A, 2.0);
    fill_matrix(B, 3.0);
    Matrix *C = add_matrices(A, B);
    CU_ASSERT_PTR_NOT_NULL(C);
    CU_ASSERT_EQUAL(C->data[0][0], 5.0);
    CU_ASSERT_EQUAL(C->data[1][1], 5.0);
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

void test_multiply_matrices() {
    Matrix *A = create_matrix(2, 2);
    Matrix *B = create_matrix(2, 2);
    A->data[0][0] = 1; A->data[0][1] = 2;
    A->data[1][0] = 3; A->data[1][1] = 4;
    B->data[0][0] = 2; B->data[0][1] = 0;
    B->data[1][0] = 1; B->data[1][1] = 2;
    Matrix *C = multiply_matrices(A, B);
    CU_ASSERT_PTR_NOT_NULL(C);
    CU_ASSERT_EQUAL(C->data[0][0], 4);
    CU_ASSERT_EQUAL(C->data[0][1], 4);
    CU_ASSERT_EQUAL(C->data[1][0], 10);
    CU_ASSERT_EQUAL(C->data[1][1], 8);
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
}

void test_transpose_matrix() {
    Matrix *A = create_matrix(2, 3);
    A->data[0][0] = 1; A->data[0][1] = 2; A->data[0][2] = 3;
    A->data[1][0] = 4; A->data[1][1] = 5; A->data[1][2] = 6;
    Matrix *T = transpose_matrix(A);
    CU_ASSERT_PTR_NOT_NULL(T);
    CU_ASSERT_EQUAL(T->rows, 3);
    CU_ASSERT_EQUAL(T->cols, 2);
    CU_ASSERT_EQUAL(T->data[0][1], 4);
    CU_ASSERT_EQUAL(T->data[2][1], 6);
    free_matrix(A);
    free_matrix(T);
}

void test_free_matrix() {
    Matrix *mat = create_matrix(3, 3);
    free_matrix(mat);
    // Тут особо нечего проверять, но важно убедиться, что нет утечек памяти
}

int main() {
    CU_initialize_registry();
    CU_pSuite suite = CU_add_suite("MatrixTests", 0, 0);
    CU_add_test(suite, "Matrix Creation", test_matrix_creation);
    CU_add_test(suite, "Fill Matrix", test_fill_matrix);
    CU_add_test(suite, "Sum Diagonal", test_sum_diagonal);
    CU_add_test(suite, "Add Matrices", test_add_matrices);
    CU_add_test(suite, "Multiply Matrices", test_multiply_matrices);
    CU_add_test(suite, "Transpose Matrix", test_transpose_matrix);
    CU_add_test(suite, "Free Matrix", test_free_matrix);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return 0;
}

