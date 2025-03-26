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

    for (int iter = 0; iter < rows; iter++) {
        mat->data[iter] = (double *)calloc(cols, sizeof(double));
        if (!mat->data[iter]) {
            while (--iter >= 0) free(mat->data[iter]);
            free(mat->data);
            free(mat);
            return NULL;
        }
    }
    return mat;
}

void free_matrix(Matrix *mat) {
    if (!mat) return;
    for (int iter = 0; iter < mat->rows; iter++)
        free(mat->data[iter]);
    free(mat->data);
    free(mat);
}

void print_matrix(const Matrix *mat) {
    for (int iter = 0; iter < mat->rows; iter++) {
        for (int j = 0; j < mat->cols; j++)
            printf("%8.2f ", mat->data[iter][j]);
        printf("\n");
    }
}

Matrix *transpose_matrix(const Matrix *mat) {
    Matrix *transposed = create_matrix(mat->cols, mat->rows);
    if (!transposed) return NULL;
    for (int iter = 0; iter < mat->rows; iter++)
        for (int j = 0; j < mat->cols; j++)
            transposed->data[j][iter] = mat->data[iter][j];
    return transposed;
}

double sum_diagonal(const Matrix *mat) {
    if (!mat || mat->rows != mat->cols) return 0;
    double sum = 0;
    for (int iter = 0; iter < mat->rows; iter++)
        sum += mat->data[iter][iter];
    return sum;
}

void fill_matrix(Matrix *mat, double value) {
    if (!mat) return;
    for (int iter = 0; iter < mat->rows; iter++)
        for (int j = 0; j < mat->cols; j++)
            mat->data[iter][j] = value;
}

Matrix *load_matrix(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return NULL;
    }

    int rows, cols;
    if (fscanf(file, "%d %d", &rows, &cols) != 2) {
        perror("Invalid file format");
        fclose(file);
        return NULL;
    }

    Matrix *mat = create_matrix(rows, cols);
    if (!mat) {
        fclose(file);
        return NULL;
    }

    for (int iter = 0; iter < rows; iter++)
        for (int j = 0; j < cols; j++)
            if (fscanf(file, "%lf", &mat->data[iter][j]) != 1) {
                perror("Invalid matrix data");
                free_matrix(mat);
                fclose(file);
                return NULL;
            }

    fclose(file);
    return mat;
}
