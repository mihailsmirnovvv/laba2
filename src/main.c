#include "matrix.h"
#include "output.h"
#include "output.h"

/**
 * @brief Вычисляет выражение A^T * B - C + D
 * @param fileA путь к файлу с матрицей A
 * @param fileB путь к файлу с матрицей B
 * @param fileC путь к файлу с матрицей C
 * @param fileD путь к файлу с матрицей D
 * @return Результирующая матрица или NULL в случае ошибки
 */
Matrix *calculate_expression(const char *fileA, const char *fileB, const char *fileC, const char *fileD) {
    Matrix *A = load_matrix(fileA), *B = load_matrix(fileB);
    Matrix *C = load_matrix(fileC), *D = load_matrix(fileD);
    
    if (!A || !B || !C || !D) {
        print_error("Ошибка загрузки матриц.");
        free_matrix(A); free_matrix(B);
        free_matrix(C); free_matrix(D);
        return NULL;
    }
    
    Matrix *AT = transpose_matrix(A);
    Matrix *ATB = dot_matrices(AT, B);
    free_matrix(AT);
    if (!ATB) {
        free_matrix(A); free_matrix(B);
        free_matrix(C); free_matrix(D);
        return NULL;
    }
    
    Matrix *ATB_C = subtract_matrices(ATB, C);
    free_matrix(ATB);
    if (!ATB_C) {
        free_matrix(A); free_matrix(B);
        free_matrix(C); free_matrix(D);
        return NULL;
    }
    
    Matrix *result = add_matrices(ATB_C, D);
    free_matrix(ATB_C);
    
    free_matrix(A); free_matrix(B);
    free_matrix(C); free_matrix(D);
    
    return result;
}

/**
 * @brief Точка входа в программу
 * @return Код завершения (0 - успех, 1 - ошибка)
 */
int main() {
    Matrix *A = create_matrix(3, 3);
    if (!A) {
        print_error("Ошибка выделения памяти для A");
        return 1;
    }

    fill_matrix(A, 1);
    print_message("Матрица A:");
    print_matrix(A);
    print_double("Сумма диагонали:", sum_diagonal(A));
    free_matrix(A);

    Matrix *result = calculate_expression("tests/test_A.txt", "tests/test_B.txt", "tests/test_C.txt", "tests/test_D.txt");
    if (result) {
        print_message("Результат выражения:");
        print_matrix(result);
        free_matrix(result);
    } else {
        print_error("Ошибка вычисления выражения.");
        return 1;
    }

    return 0;
}
