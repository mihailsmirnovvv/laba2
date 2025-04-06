#include "matrix.h"

/**
 * @brief Создает новую матрицу с заданными размерами
 * @param rows Количество строк
 * @param cols Количество столбцов
 * @return Указатель на созданную матрицу или NULL в случае ошибки
 */
Matrix *create_matrix(int rows, int cols) {
    Matrix *result = (Matrix *)malloc(sizeof(Matrix));

    if (rows <= 0 || cols <= 0) {
        free(result);
        result = NULL;
    } else {
        result->rows = rows;
        result->cols = cols;

        result->data = (MATRIX_TYPE **)calloc(rows, sizeof(MATRIX_TYPE *));

        for (int iter = 0; (int) iter < rows; iter++)
            result->data[iter] = (double *)calloc(cols, sizeof(double));
    }
    return result;
}

/**
 * @brief Освобождает память, выделенную под матрицу
 * @param matrix Указатель на матрицу
 */
void free_matrix(Matrix *matrix) {
    if (matrix) {
        if (matrix->data) {
            for (int iter = 0; iter < matrix->rows; iter++) {
                free(matrix->data[iter]);
            }
            free(matrix->data);
        }
        free(matrix);
    }
}

/**
 * @brief Загружает матрицу из текстового файла
 * @param filename Имя файла
 * @return Указатель на загруженную матрицу или NULL в случае ошибки
 */
Matrix *load_matrix_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    int rows = 0, cols = 0;
    Matrix *res;

    if (file && fscanf(file, "%d%d", &rows, &cols) == 2) {
        res = create_matrix(rows, cols);
        for (int iter = 0; iter < rows; iter++)
            for (int j = 0; j < cols; j++)
                fscanf(file, "%lf", &(res->data[iter][j]));
        fclose(file);
    } else
        res = NULL;

    return res;
}

/**
 * @brief Копирует матрицу
 * @param source Указатель на исходную матрицу
 * @return Указатель на копию матрицы или NULL в случае ошибки
 */
Matrix *copy_matrix(const Matrix *source) {
    Matrix *result = create_matrix(source->rows, source->cols);

    for (int iter = 0; iter < source->rows; iter++)
        for (int j = 0; j < source->cols; j++)
            result->data[iter][j] = source->data[iter][j];

    return result;
}

/**
 * @brief Складывает две матрицы
 * @param A Указатель на первую матрицу
 * @param B Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат сложения, либо NULL в случае
 * ошибки
 */
Matrix *sum_matrices(const Matrix *A, const Matrix *B) {
    Matrix *result = NULL;
    if (isSizeEqual(A, B) && isCorrectMatrix(A) && isCorrectMatrix(B)) {
        result = create_matrix(A->rows, A->cols);

        for (int iter = 0; iter < A->rows; iter++)
            for (int j = 0; j < A->cols; j++)
                result->data[iter][j] = A->data[iter][j] + B->data[iter][j];
    }
    return result;
}

/**
 * @brief Считает матрицу разницы двух матриц
 * @param A Указатель на первую матрицу
 * @param B Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат сложения, либо NULL в случае
 * ошибки
 */
Matrix *sub_matrices(const Matrix *A, const Matrix *B) {
    Matrix *result = NULL;
    if (isSizeEqual(A, B) && isCorrectMatrix(A) && isCorrectMatrix(B)) {
        result = create_matrix(A->rows, A->cols);

        for (int iter = 0; iter < A->rows; iter++)
            for (int j = 0; j < A->cols; j++)
                result->data[iter][j] = A->data[iter][j] - B->data[iter][j];
    }
    return result;
}

/**
 * @brief Умножает две матрицы
 * @param A Указатель на первую матрицу
 * @param B Указатель на вторую матрицу
 * @return Указатель на новую матрицу — результат умножения, либо NULL в случае
 * ошибки
 */
Matrix *dot_matrices(const Matrix *A, const Matrix *B) {
    Matrix *result = NULL;
    if (A->cols == B->rows && isCorrectMatrix(A) && isCorrectMatrix(B)) {
        result = create_matrix(A->rows, A->cols);

        for (int iter = 0; iter < A->rows; iter++)
            for (int j = 0; j < B->cols; j++)
                for (int k = 0; k < A->cols; k++)
                    result->data[iter][j] += A->data[iter][k] * B->data[k][j];
    }
    return result;
}

/** @brief Транспонирует матрицу
 * @param matrix Указатель на матрицу
 * @return Указатель на новую транспонированную матрицу, либо NULL в случае ошибки
 */
Matrix *transpose_matrix(const Matrix *matrix) {
    Matrix *result = NULL;

    if (isCorrectMatrix(matrix)) {
        result = create_matrix(matrix->cols, matrix->rows);
        result->cols = matrix->rows;
        result->rows = matrix->cols;
        for (int iter = 0; iter < matrix->rows; iter++)
            for (int j = 0; j < matrix->cols; j++)
                result->data[j][iter] = matrix->data[iter][j];
    }
    return result;
}

/**
 * @brief Вычисляет детерминант квадратной матрицы
 * @param matrix Указатель на квадратную матрицу
 * @return Значение детерминанта матрицы
 */
MATRIX_TYPE determinant(const Matrix *A) {
    MATRIX_TYPE det = 0;

    if (!A || A->rows != A->cols)
        det = NAN;
    else {
        if (A->rows == 1)
            det = A->data[0][0];
        else if (A->rows == 2)
            det = A->data[0][0] * A->data[1][1] - A->data[0][1] * A->data[1][0];
        else
            for (int k = 0; k < A->cols; k++) {
                Matrix *minor = getMinorMatrix(A, 0, k);
                det += pow(-1, k) * A->data[0][k] * determinant(minor);
                free_matrix(minor);
            }
    }
    return det;
}

/**
 * @brief Считает минор матрицы, без указанных rows cols
 * @param matrix Указатель на матрицу
 * @return Указатель на минорную матрицу
 */
Matrix *getMinorMatrix(const Matrix *A, int rows, int columns) {
    Matrix *minor = create_matrix(A->rows - 1, A->cols - 1);

    for (int iter = 0, mi = 0; iter < A->rows; iter++) {
        if (iter != rows) {
            for (int j = 0, mj = 0; j < A->cols; j++) {
                if (j != columns) {
                    minor->data[mi][mj] = A->data[iter][j];
                    mj++;
                }
            }
            mi++;
        }
    }

    return minor;
}

/**
 * @brief Вспомогательная функция для проверки корректности матрицы (валидный указатель и размеры)
 * @param matrix Указатель на матрицу
 * @return 1 - корректная, 0 - некорректная
 */
int isCorrectMatrix(const Matrix *A) {
    return !(A->cols < 1 || A->rows < 1 || (A->data == NULL));
}

/**
 * @brief Вспомогательная функция для проверки на эквивалентность размеров матриц
 * @param B Указатель на матрицу
 * @param A Указатель на матрицу
 * @return 1 - размеры одинаковые, 0 - размеры разные
 */
int isSizeEqual(const Matrix *A, const Matrix *B) {
    return (A->rows == B->rows && A->cols == B->cols);
}
