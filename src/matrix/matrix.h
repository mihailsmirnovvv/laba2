#ifndef MATRIX_H
#define MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "../../include/config.h"

/**
 * @brief Создает новую матрицу с заданными размерами
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Указатель на созданную матрицу или NULL в случае ошибки
 */
Matrix *create_matrix(int rows, int cols);

/**
 * @brief Освобождает память, выделенную под матрицу
 * @param matrix Указатель на матрицу
 */
void free_matrix(Matrix *matrix);

/**
 * @brief Загружает матрицу из текстового файла
 * @param filename Имя файла
 * @return Указатель на загруженную матрицу или NULL в случае ошибки
 */
Matrix *load_matrix_from_file(const char *filename);

/**
 * @brief Копирует матрицу
 * @param source Указатель на исходную матрицу
 * @return Указатель на копию матрицы или NULL в случае ошибки
 */
Matrix *copy_matrix(const Matrix *source);

/**
 * @brief Складывает две матрицы
 * @param A Указатель на первую матрицу
 * @param B Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат сложения, либо NULL в случае
 * ошибки
 */
Matrix *sum_matrices(const Matrix *A, const Matrix *B);

/**
 * @brief Считает матрицу разницы двух матриц
 * @param A Указатель на первую матрицу
 * @param B Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат сложения, либо NULL в случае
 * ошибки
 */
Matrix *sub_matrices(const Matrix *A, const Matrix *B);

/**
 * @brief Умножает две матрицы
 * @param A Указатель на первую матрицу
 * @param B Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат умножения, либо NULL в случае
 * ошибки
 */
Matrix *dot_matrices(const Matrix *A, const Matrix *B);

/** @brief Транспонирует матрицу
 * @param matrix Указатель на матрицу
 * @return Указатель на новую транспонированную матрицу, либо NULL в случае
 * ошибки
 */
Matrix *transpose_matrix(const Matrix *matrix);

/**
 * @brief Вычисляет детерминант квадратной матрицы
 * @param matrix Указатель на квадратную матрицу
 * @return Значение детерминанта матрицы
 */
MATRIX_TYPE determinant(const Matrix *matrix);

/**
 * @brief Считает минор матрицы, без указанных rows cols
 * @param matrix Указатель на матрицу
 * @return Указатель на минорную матрицу
 */
Matrix *getMinorMatrix(const Matrix *A, int rows, int columns);

/**
 * @brief Вспомогательная функция для проверки корректности матрицы (валидный указатель и размеры)
 * @param matrix Указатель на матрицу
 * @return 1 - корректная, 0 - некорректная
 */
int isCorrectMatrix(const Matrix *A);

/**
 * @brief Вспомогательная функция для проверки на эквивалентность размеров матриц
 * @param B Указатель на матрицу
 * @param A Указатель на матрицу
 * @return 1 - размеры одинаковые, 0 - размеры разные
 */
int isSizeEqual(const Matrix *A, const Matrix *B);

#endif // MATRIX_H