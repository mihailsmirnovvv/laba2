#include "matrix.h"
#include <stdio.h>

int main() {
  Matrix *A = create_matrix(3, 3);
  fill_matrix(A, 1);

  printf("Matrix A:\n");
  print_matrix(A);

  printf("Sum of diagonal: %f\n", sum_diagonal(A));

  free_matrix(A);
  return 0;
}
