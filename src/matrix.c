#include "matrix.h"
#include <stdlib.h>

/**
 * @brief Создает новую матрицу заданного размера.
 * @param rows Количество строк.
 * @param cols Количество столбцов.
 * @return Указатель на созданную матрицу или NULL в случае ошибки.
 */
Matrix *create_matrix(size_t rows, size_t cols) {
    Matrix *mat = (Matrix *)malloc(sizeof(Matrix));
    if (!mat) return NULL;
    mat->rows = rows;
    mat->cols = cols;
    mat->data = (double **)malloc(rows * sizeof(double *));
    if (!mat->data) {
        free(mat);
        return NULL;
    }
    for (size_t iter = 0; iter < rows; iter++) {
        mat->data[iter] = (double *)calloc(cols, sizeof(double));
        if (!mat->data[iter]) {
            for (size_t jter = 0; jter < iter; jter++)
                free(mat->data[jter]);
            free(mat->data);
            free(mat);
            return NULL;
        }
    }
    return mat;
}

/**
 * @brief Освобождает память, выделенную под матрицу.
 * @param mat Указатель на матрицу.
 */
void free_matrix(Matrix *mat) {
    if (!mat) return;
    for (size_t iter = 0; iter < mat->rows; iter++)
        free(mat->data[iter]);
    free(mat->data);
    free(mat);
}

/**
 * @brief Транспонирует матрицу.
 * @param A Исходная матрица.
 * @return Новая транспонированная матрица или NULL в случае ошибки.
 */
Matrix *transpose_matrix(const Matrix *A) {
    if (!A) return NULL;
    Matrix *res = create_matrix(A->cols, A->rows);
    if (!res) return NULL;
    for (size_t iter = 0; iter < A->rows; iter++)
        for (size_t jter = 0; jter < A->cols; jter++)
            res->data[jter][iter] = A->data[iter][jter];
    return res;
}