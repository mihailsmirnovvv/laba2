#ifndef OUTPUT_H
#define OUTPUT_H

#include "../../include/config.h"
#include <stdio.h>

/**
 * @brief Тип колбека для форматированного вывода элемента матрицы
 * @param stream Выходной поток
 * @param value Значение элемента
 * @return Количество записанных символов или отрицательное значение при ошибке
 */
typedef int (*matrixPrint)(FILE *stream, MATRIX_TYPE value);

/**
 * @brief Универсальная функция вывода матрицы
 * @param matrix Указатель на матрицу
 * @param stream Выходной поток
 * @param callback Функция форматирования элемента
 * @return 0 в случае успеха, 1 в случае ошибки
 */
int export_matrix(const Matrix *matrix, FILE *stream, matrixPrint callback);

/**
 * @brief Выводит округленное до целого значения число
 * @param stream указатель на дескриптор
 * @param value значение для вывода
 * @return Количество выведенных байт в консоль
 */
int rounded_print(FILE *stream, MATRIX_TYPE value);

/**
 * @brief Выводит 6 знаков после запятой чисел
 * @param stream указатель на дескриптор
 * @param value значение для вывода
 * @return Количество выведенных байт в консоль
 */
int default_print(FILE *stream, MATRIX_TYPE value);

/**
 * @brief Сохраняет матрицу в текстовый файл
 * @param matrix Указатель на матрицу
 * @param filename Имя файла
 * @return 0 в случае успеха, -1 в случае ошибки
 */
int save_matrix_to_file(const Matrix *matrix, const char *filename);

/**
 * @brief Выводит матрицу в консоль
 * @param matrix Указатель на матрицу
 */
void print_matrix(const Matrix *matrix);

#endif // OUTPUT_H