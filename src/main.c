#include "matrix.h"
#include <stdio.h>

Matrix *subtract_matrices(const Matrix *A, const Matrix *B) {
    if (!A || !B || A->rows != B->rows || A->cols != B->cols) return NULL;

    Matrix *result = create_matrix(A->rows, A->cols);
    if (!result) return NULL;

    for (size_t row = 0; row < (size_t)A->rows; row++)
        for (size_t col = 0; col < (size_t)A->cols; col++)
            result->data[row][col] = A->data[row][col] - B->data[row][col];

    return result;
}

Matrix *dot_matrices(const Matrix *A, const Matrix *B) {
    if (!A || !B || A->cols != B->rows) return NULL;

    Matrix *res = create_matrix(A->rows, B->cols);
    if (!res) return NULL;

    for (size_t row = 0; row < (size_t)A->rows; row++)
        for (size_t col = 0; col < (size_t)B->cols; col++) {
            double sum = 0;
            for (size_t k = 0; k < (size_t)A->cols; k++)
                sum += A->data[row][k] * B->data[k][col];
            res->data[row][col] = sum;
        }

    return res;
}

Matrix *add_matrices(const Matrix *A, const Matrix *B) {
    if (!A || !B || A->rows != B->rows || A->cols != B->cols) return NULL;

    Matrix *res = create_matrix(A->rows, A->cols);
    if (!res) return NULL;

    for (size_t row = 0; row < (size_t)A->rows; row++)
        for (size_t col = 0; col < (size_t)A->cols; col++)
            res->data[row][col] = A->data[row][col] + B->data[row][col];

    return res;
}

Matrix *compute_expression(const Matrix *A, const Matrix *B, const Matrix *C, const Matrix *D) {
    if (!A || !B || !C || !D) return NULL;

    Matrix *AT = transpose_matrix(A);
    if (!AT) return NULL;

    Matrix *ATB = dot_matrices(AT, B);
    free_matrix(AT);
    if (!ATB) return NULL;

    Matrix *ATB_C = subtract_matrices(ATB, C);
    free_matrix(ATB);
    if (!ATB_C) return NULL;

    Matrix *result = add_matrices(ATB_C, D);
    free_matrix(ATB_C);

    return result;
}

Matrix *calculate_expression(const char *fileA, const char *fileB, const char *fileC, const char *fileD) {
Matrix *A = load_matrix(fileA), *B = load_matrix(fileB);
Matrix *C = load_matrix(fileC), *D = load_matrix(fileD);

    if (!A || !B || !C || !D) {
        fprintf(stderr, "Error loading matrices.\n");
        goto cleanup;
    }

    Matrix *result = compute_expression(A, B, C, D);

cleanup:
    free_matrix(A); free_matrix(B);
    free_matrix(C); free_matrix(D);
    
    return result;
}

int main() {
    Matrix *A = create_matrix(3, 3);
    if (!A) {
        fprintf(stderr, "Memory allocation failed for A\n");
        return 1;
    }

    fill_matrix(A, 1);
    printf("Matrix A:\n");
    print_matrix(A);
    printf("Sum of diagonal: %f\n", sum_diagonal(A));
    free_matrix(A);

    Matrix *result = calculate_expression("tests/test_A.txt", "tests/test_B.txt", "tests/test_C.txt", "tests/test_D.txt");
    if (result) {
        printf("Result matrix:\n");
        print_matrix(result);
        free_matrix(result);
    } else {
        fprintf(stderr, "Failed to compute matrix expression.\n");
    }

    return 0;
}

