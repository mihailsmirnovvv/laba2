#include "test_matrix.h"

int double_compare(MATRIX_TYPE a, MATRIX_TYPE b) {
    return fabs(a - b) < EPS;
}

Matrix *create_test_matrix(int rows, int cols, MATRIX_TYPE data[]) {
    Matrix *m = create_matrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            m->data[i][j] = data[i * cols + j];
        }
    }
    return m;
}

void test_copy_matrix(void) {
    MATRIX_TYPE data[] = {1, 2, 3, 4};
    Matrix *orig = create_test_matrix(2, 2, data);
    Matrix *copy = copy_matrix(orig);

    CU_ASSERT_EQUAL(copy->rows, orig->rows);
    CU_ASSERT_EQUAL(copy->cols, orig->cols);
    CU_ASSERT_TRUE(double_compare(copy->data[0][0], 1));
    CU_ASSERT_TRUE(double_compare(copy->data[1][1], 4));

    free_matrix(orig);
    free_matrix(copy);
}

void test_matrix_addition(void) {
    MATRIX_TYPE a[] = {1, 2, 3, 4};
    MATRIX_TYPE b[] = {5, 6, 7, 8};
    MATRIX_TYPE expected[] = {6, 8, 10, 12};

    Matrix *m1 = create_test_matrix(2, 2, a);
    Matrix *m2 = create_test_matrix(2, 2, b);
    Matrix *result = sum_matrices(m1, m2);

    CU_ASSERT_PTR_NOT_NULL(result);
    for (int i = 0; i < 4; i++) {
        CU_ASSERT_TRUE(double_compare(result->data[i / 2][i % 2], expected[i]));
    }

    free_matrix(m1);
    free_matrix(m2);
    free_matrix(result);
}

void test_matrix_multiplication(void) {
    MATRIX_TYPE a[] = {1, 2, 3, 4};
    MATRIX_TYPE b[] = {5, 6, 7, 8};
    MATRIX_TYPE expected[] = {19, 22, 43, 50};

    Matrix *m1 = create_test_matrix(2, 2, a);
    Matrix *m2 = create_test_matrix(2, 2, b);
    Matrix *result = dot_matrices(m1, m2);

    CU_ASSERT_PTR_NOT_NULL(result);
    for (int i = 0; i < 4; i++) {
        CU_ASSERT_TRUE(double_compare(result->data[i / 2][i % 2], expected[i]));
    }

    free_matrix(m1);
    free_matrix(m2);
    free_matrix(result);
}

void test_determinant(void) {
    MATRIX_TYPE data1[] = {5};
    MATRIX_TYPE data2[] = {1, 2, 3, 4};
    MATRIX_TYPE data3[] = {2, 3, 1, 1, 2, 3, 3, 1, 2};

    Matrix *m1 = create_test_matrix(1, 1, data1);
    Matrix *m2 = create_test_matrix(2, 2, data2);
    Matrix *m3 = create_test_matrix(3, 3, data3);

    CU_ASSERT_DOUBLE_EQUAL(determinant(m1), 5.0, EPS);
    CU_ASSERT_DOUBLE_EQUAL(determinant(m2), -2.0, EPS);
    CU_ASSERT_DOUBLE_EQUAL(determinant(m3), 18.0, EPS);

    free_matrix(m1);
    free_matrix(m2);
    free_matrix(m3);
}

void test_transpose(void) {
    MATRIX_TYPE data[] = {1, 2, 3, 4, 5, 6};
    Matrix *m = create_test_matrix(2, 3, data);
    Matrix *transposed = transpose_matrix(m);

    CU_ASSERT_EQUAL(transposed->rows, 3);
    CU_ASSERT_EQUAL(transposed->cols, 2);
    CU_ASSERT_TRUE(double_compare(transposed->data[0][0], 1));
    CU_ASSERT_TRUE(double_compare(transposed->data[1][1], 5));

    free_matrix(m);
    free_matrix(transposed);
}

void test_load_from_file(void) {
    const char filename[] = "test_matrix.txt";
    FILE *f = fopen(filename, "w");
    fprintf(f, "2 3\n1.5 2.5 3.5\n4.5 5.5 6.5\n");
    fclose(f);

    Matrix *m = load_matrix_from_file(filename);
    CU_ASSERT_PTR_NOT_NULL(m);
    CU_ASSERT_EQUAL(m->rows, 2);
    CU_ASSERT_EQUAL(m->cols, 3);
    CU_ASSERT_TRUE(double_compare(m->data[1][2], 6.5));

    free_matrix(m);
}

void test_create_and_free(void) {
    Matrix *m = create_matrix(3, 4);
    CU_ASSERT_PTR_NOT_NULL(m);
    CU_ASSERT_EQUAL(m->rows, 3);
    CU_ASSERT_EQUAL(m->cols, 4);
    free_matrix(m);

    Matrix *invalid = create_matrix(-1, 5);
    CU_ASSERT_PTR_NULL(invalid);
}

int main() {
    CU_pSuite suite = NULL;

    if (CU_initialize_registry() != CUE_SUCCESS)
        return CU_get_error();

    suite = CU_add_suite("Matrix Tests", NULL, NULL);
    if (!suite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_add_test(suite, "Matrix Copy", test_copy_matrix);
    CU_add_test(suite, "Matrix Addition", test_matrix_addition);
    CU_add_test(suite, "Matrix Multiplication", test_matrix_multiplication);
    CU_add_test(suite, "Determinant Calculation", test_determinant);
    CU_add_test(suite, "Matrix Transpose", test_transpose);
    CU_add_test(suite, "Load from File", test_load_from_file);
    CU_add_test(suite, "Create and Free", test_create_and_free);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}

