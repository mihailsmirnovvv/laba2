#include "matrix/matrix.h"
#include "output/output.h"

int main() {
    Matrix *A = load_matrix_from_file("matrix_data/matrix_a.txt");
    Matrix *B = load_matrix_from_file("matrix_data/matrix_b.txt");
    Matrix *C = load_matrix_from_file("matrix_data/matrix_c.txt");
    Matrix *D = load_matrix_from_file("matrix_data/matrix_d.txt");

    // Считаем A^T × B - C + D

    // Считаем A^T
    Matrix *transposedA = transpose_matrix(A);

    // Считаем A^T * B
    Matrix *mul_tA_B = dot_matrices(transposedA, B);

    // Считаем (A^T * B) - C
    Matrix *diff_tA_B_C = sub_matrices(mul_tA_B, C);

    // Считаем ((A^T * B) - C) + D
    Matrix *res = sum_matrices(diff_tA_B_C, D);


    print_matrix(res);

    free_matrix(A);
    free_matrix(B);
    free_matrix(C);
    free_matrix(D);

    free_matrix(transposedA);
    free_matrix(mul_tA_B);
    free_matrix(diff_tA_B_C);
    free_matrix(res);
}

