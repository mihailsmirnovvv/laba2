#include "../include/output.h"
#include <stdio.h>

void print_matrix(const Matrix *mat) {
    if (!mat) {
        print_error("Матрица отсутствует.");
        return;
    }

    for (size_t row = 0; row < (size_t)mat->rows; row++) {
        for (size_t col = 0; col < (size_t)mat->cols; col++)
            printf("%8.3lf ", mat->data[row][col]);  // Вывод с форматированием
        printf("\n");
    }
}

void print_error(const char *message) {
    fprintf(stderr, "Ошибка: %s\n", message);
}

void print_message(const char *message) {
    printf("%s\n", message);
}

void print_double(const char *message, double value) {
    printf("%s %8.3lf\n", message, value);
}

