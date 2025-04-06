
#ifndef CONFIG_H
#define CONFIG_H
/**
 * @brief Определение базового типа данных для элементов матрицы
 * Можно изменить на float, int или другой подходящий тип
 */
typedef double MATRIX_TYPE;

/**
 * @brief Структура матрицы
 */
typedef struct {
    int rows;           ///< Количество строк
    int cols;           ///< Количество столбцов
    MATRIX_TYPE **data; ///< Данные матрицы
} Matrix;

#endif // CONFIG_H
