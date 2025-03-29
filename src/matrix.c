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
    if (A->cols != B->rows) return NULL;
    Matrix *res = create_matrix(A->rows, B->cols);
    if (!res) return NULL;
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < B->cols; j++)
            for (int k = 0; k < A->cols; k++)
                res->data[i][j] += A->data[i][k] * B->data[k][j];
    return res;
}

Matrix *add_matrices(const Matrix *A, const Matrix *B) {
    if (A->rows != B->rows || A->cols != B->cols) return NULL;
    Matrix *res = create_matrix(A->rows, A->cols);
    if (!res) return NULL;
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->cols; j++)
            res->data[i][j] = A->data[i][j] + B->data[i][j];
    return res;
}

Matrix *compute_expression(const Matrix *A, const Matrix *B, const Matrix *C, const Matrix *D) {
    Matrix *AT = transpose_matrix(A);
    if (!AT) return NULL;
    Matrix *ATB = dot_matrices(AT, B);
    free_matrix(AT);
    if (!ATB) return NULL;
    Matrix *res = add_matrices(subtract_matrices(ATB, C), D);
    free_matrix(ATB);
    return res;
}

