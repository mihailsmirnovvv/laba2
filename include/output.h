#ifndef OUTPUT_H
#define OUTPUT_H

#include "matrix.h"

/**
 * @brief Выводит матрицу на экран.
 * 
 * @param mat Указатель на матрицу.
 */
void print_matrix(const Matrix *mat);

/**
 * @brief Выводит сообщение об ошибке.
 * 
 * @param message Текст ошибки.
 */
void print_error(const char *message);

#endif // OUTPUT_H

/**
 * @brief Выводит текстовое сообщение.
 * 
 * @param message Сообщение для вывода.
 */
void print_message(const char *message);

/**
 * @brief Выводит сообщение и число с плавающей точкой.
 * 
 * @param message Сообщение.
 * @param value Число.
 */
void print_double(const char *message, double value);

