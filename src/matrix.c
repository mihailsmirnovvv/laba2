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

double sum_diagonal(const Matrix *mat) {
    if (!mat || mat->rows != mat->cols) return 0;
    
    double sum = 0;
    for (int i = 0; i < mat->rows; i++) {
        sum += mat->data[i][i];
    }
    return sum;
}



void fill_matrix(Matrix *mat, double value) {
    if (!mat) return;
    
    for (int i = 0; i < mat->rows; i++) {
        for (int j = 0; j < mat->cols; j++) {
            mat->data[i][j] = value;
        }
    }
}


Matrix *load_matrix(const char *filename) {
    printf("Trying to open file: %s\n", filename);
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

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (fscanf(file, "%lf", &mat->data[i][j]) != 1) {
                perror("Invalid matrix data");
                free_matrix(mat);
                fclose(file);
                return NULL;
            }

    fclose(file);
    return mat;
}

Matrix *calculate_expression(const char *fileA, const char *fileB, const char *fileC, const char *fileD) {
    Matrix *A = load_matrix(fileA); 
    Matrix *B = load_matrix(fileB);  
    Matrix *C = load_matrix(fileC);  
    Matrix *D = load_matrix(fileD);  



    if (!A || !B || !C || !D) {
        fprintf(stderr, "Error loading matrices.\n");
        free_matrix(A);
        free_matrix(B);
        free_matrix(C);
        free_matrix(D);
        return NULL;
    }

    if (A == NULL || B == NULL || C == NULL || D == NULL) {
        fprintf(stderr, "Error loading matrices.\n");
        return NULL;
    }
    

// Транспонируем A
Matrix *AT = transpose_matrix(A);
if (!AT) {
    fprintf(stderr, "Error transposing A.\n");
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(D);
    return NULL;
}
printf("Matrix A^T:\n");
print_matrix(AT);
printf("Size of A^T: %dx%d\n", AT->rows, AT->cols);

// Выводим матрицу B
printf("Matrix B:\n");
print_matrix(B);
printf("Size of B: %dx%d\n", B->rows, B->cols);

// Умножаем A^T * B
Matrix *ATB = multiply_matrices(AT, B);
if (!ATB) {
    fprintf(stderr, "Error multiplying AT * B.\n");
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(D);
    free_matrix(AT);
    return NULL;
}

// Проверяем размеры
printf("Size of (A^T * B): %dx%d\n", ATB->rows, ATB->cols);
printf("Size of C: %dx%d\n", C->rows, C->cols);
printf("Size of D: %dx%d\n", D->rows, D->cols);

// Выводим результат умножения
printf("Result of A^T * B:\n");
print_matrix(ATB);

// Выводим матрицу C перед вычитанием
printf("Matrix C:\n");
print_matrix(C);

// Вычитаем C
Matrix *ATB_C = subtract_matrices(ATB, C);
if (!ATB_C) {
    fprintf(stderr, "Error subtracting C. Size mismatch?\n");
    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(D);
    free_matrix(AT);
    free_matrix(ATB);
    return NULL;
}

// Выводим D перед сложением
printf("Matrix D:\n");
print_matrix(D);

// Складываем с D
Matrix *result = add_matrices(ATB_C, D);
if (!result) {
    fprintf(stderr, "Error adding D. Size mismatch?\n");
}

// Освобождаем память
free_matrix(A);
free_matrix(B);
free_matrix(C);
free_matrix(D);
free_matrix(AT);
free_matrix(ATB);
free_matrix(ATB_C);

return result;
}