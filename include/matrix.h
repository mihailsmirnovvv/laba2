#ifndef MATRIX_H
#define MATRIX_H

typedef struct {
    int rows;
    int cols;
    double **data;
} Matrix;

Matrix *create_matrix(int rows, int cols);
void free_matrix(Matrix *matrix);
void fill_matrix_random(Matrix *matrix);
void print_matrix(const Matrix *matrix);  // Исправлено: добавлен const
double sum_diagonal(const Matrix *matrix);  // Добавлено

#endif // MATRIX_H
