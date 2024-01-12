#include "test.h"

int main() {
  SRunner *sr = srunner_create(suite_create_matrix());
  srunner_add_suite(sr, suite_eq_matrix());
  srunner_add_suite(sr, suite_sum_matrix());
  srunner_add_suite(sr, suite_sub_matrix());
  srunner_add_suite(sr, suite_mult_number());
  srunner_add_suite(sr, suite_mult_matrix());
  srunner_add_suite(sr, suite_transpose_matrix());
  srunner_add_suite(sr, suite_determinant());
  srunner_add_suite(sr, suite_calc_complements());
  srunner_add_suite(sr, suite_inverse_matrix());
  srunner_run_all(sr, CK_NORMAL);
  srunner_free(sr);
}

double getRandom(unsigned min, unsigned max, unsigned minus) {
  srand(time(NULL));
  double value = 0, integer, fractional;
  integer = rand() % max + min;
  fractional = integer;
  for (int i = 0; i < 7; i++) fractional += rand() % 10;
  fractional -= (int)fractional;
  value = integer + fractional;
  if (minus && rand() % 2 == 0) value = -value;
  return value;
}

void s21_gen_matrix(matrix_t *A) {
  double num = 1;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++, num++) {
      A->matrix[i][j] = num;
    }
  }
}

void s21_anti_gen_matrix(matrix_t *A) {
  double num = 32;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++, num--) {
      A->matrix[i][j] = num;
    }
  }
}

void s21_fill(matrix_t *matrixStruct, double value) {
  for (int i = 0; i < matrixStruct->rows; i++) {
    for (int j = 0; j < matrixStruct->columns; j++) {
      matrixStruct->matrix[i][j] = value;
    }
  }
}
