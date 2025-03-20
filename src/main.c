#include "matrix.h"
#include <stdio.h>

int main() {
  Matrix *A = create_matrix(3, 3);
  fill_matrix(A, 1);

  printf("Matrix A:\n");
  print_matrix(A);

  printf("Sum of diagonal: %f\n", sum_diagonal(A));

  free_matrix(A);


  Matrix *result = calculate_expression("tests/test_A.txt", "tests/test_B.txt", "tests/test_C.txt", "tests/test_D.txt");
    if (result) {
        printf("Result:\n");
        print_matrix(result);
        free_matrix(result);
    }

  return 0;
}

