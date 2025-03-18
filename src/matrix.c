#include "../include/matrix.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Matrix *create_matrix(int rows, int cols) {
    Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
    if (!mat) return NULL;
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double **)malloc(rows * sizeof(double *));
    if (!mat->data) {
        free(mat);
        return NULL;
    }
    for (int i = 0; i < rows; i++) {
        mat->data[i] = (double *)calloc(cols, sizeof(double));
        if (!mat->data[i]) {
            for (int j = 0; j < i; j++)
                free(mat->data[j]);
            free(mat->data);
            free(mat);
            return NULL;
        }
    }
    return mat;
}

void free_matrix(Matrix *mat) {
    if (!mat) return;
    for (int i = 0; i < mat->rows; i++)
        free(mat->data[i]);
    free(mat->data);
    free(mat);
}

void print_matrix(const Matrix *mat) {
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            printf("%8.2f ", mat->data[i][j]);
        }
        printf("\n");
    }
}

Matrix *transpose_matrix(const Matrix *mat) {
    Matrix *transposed = create_matrix(mat->cols, mat->rows);
    if (!transposed) return NULL;
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            transposed->data[j][i] = mat->data[i][j];
        }
    }
    return transposed;
}

Matrix *multiply_matrices(const Matrix *A, const Matrix *B) {
    if (A->cols != B->rows) return NULL;
    Matrix *result = create_matrix(A->rows, B->cols);
    if (!result) return NULL;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->cols; j++) {
            for (int k = 0; k < A->cols; k++) {
                result->data[i][j] += A->data[i][k] * B->data[k][j];
            }
        }
    }
    return result;
}

Matrix *add_matrices(const Matrix *A, const Matrix *B) {
    if (A->rows != B->rows || A->cols != B->cols) return NULL;
    Matrix *result = create_matrix(A->rows, A->cols);
    if (!result) return NULL;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            result->data[i][j] = A->data[i][j] + B->data[i][j];
        }
    }
    return result;
}

Matrix *subtract_matrices(const Matrix *A, const Matrix *B) {
    if (A->rows != B->rows || A->cols != B->cols) return NULL;
    Matrix *result = create_matrix(A->rows, A->cols);
    if (!result) return NULL;
    for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->cols; j++) {
            result->data[i][j] = A->data[i][j] - B->data[i][j];
        }
    }
    return result;
}

Matrix *compute_expression(const Matrix *A, const Matrix *B, const Matrix *C, const Matrix *D) {
    Matrix *AT = transpose_matrix(A);
    if (!AT) return NULL;
    Matrix *ATB = multiply_matrices(AT, B);
    free_matrix(AT);
    if (!ATB) return NULL;
    Matrix *ATB_minus_C = subtract_matrices(ATB, C);
    free_matrix(ATB);
    if (!ATB_minus_C) return NULL;
    Matrix *result = add_matrices(ATB_minus_C, D);
    free_matrix(ATB_minus_C);
    return result;
}

