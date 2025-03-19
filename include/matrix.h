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
void print_matrix(const Matrix *matrix); 
double sum_diagonal(const Matrix *matrix); 
void fill_matrix(Matrix *mat, double value);
Matrix *transpose_matrix(const Matrix *A);
Matrix *multiply_matrices(const Matrix *A, const Matrix *B);
Matrix *add_matrices(const Matrix *A, const Matrix *B);


#endif // MATRIX_H
