#include "output.h"

/**
 * @brief Универсальная функция вывода матрицы
 * @param matrix Указатель на матрицу
 * @param stream Выходной поток
 * @param callback Функция форматирования элемента
 * @return 0 в случае успеха, -1 в случае ошибки
 */
int export_matrix(const Matrix *matrix, FILE *stream, matrixPrint callback) {
    int ret_code = 0;

    if (!matrix || !stream || !callback)
        ret_code = -1;

    for (int i = 0; !ret_code && i < matrix->rows; i++) {
        for (int j = 0; !ret_code && j < matrix->cols; j++) {
            int result = callback(stream, matrix->data[i][j]);
            if (result < 0)
                ret_code = 1;
            fprintf(stream, " ");
        }
        if (fprintf(stream, "\n") < 0)
            ret_code = -1;
    }
    return ret_code;
}

/**
 * @brief Выводит 6 знаков после запятой чисел
 * @param stream указатель на дескриптор
 * @param value значение для вывода
 * @return Количество выведенных байт в консоль
 */
int default_print(FILE *stream, MATRIX_TYPE value) {
    return fprintf(stream, "%.6lf", value);
}

/**
 * @brief Выводит округленное до целого значения число
 * @param stream указатель на дескриптор
 * @param value значение для вывода
 * @return Количество выведенных байт в консоль
 */
int rounded_print(FILE *stream, MATRIX_TYPE value) {
    return fprintf(stream, "%ld", (long)value);
}

/**
 * @brief Выводит матрицу в консоль
 * @param matrix Указатель на матрицу
 */
void print_matrix(const Matrix *matrix) {
    export_matrix(matrix, stdout, default_print);
}

/**
 * @brief Сохраняет матрицу в текстовый файл
 * @param matrix Указатель на матрицу
 * @param filename Имя файла
 * @return 0 в случае успеха, -1 в случае ошибки
 */
int save_matrix_to_file(const Matrix *matrix, const char *filename) {
    int ret_code = 0;
    if (matrix && filename) {
        FILE *file = fopen(filename, "w");
        if (file)
            if (fprintf(file, "%d %d\n", matrix->rows, matrix->cols) < 0)
                ret_code = -1;

        if (!ret_code)
            ret_code = export_matrix(matrix, file, default_print);

        fclose(file);
    } else
        ret_code = -1;

    return ret_code;
}