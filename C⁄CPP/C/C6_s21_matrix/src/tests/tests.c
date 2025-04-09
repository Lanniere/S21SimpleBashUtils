#include <check.h>

#include "../s21_matrix.h"

void init(matrix_t *A, int k, int c) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      A->matrix[i][j] = k;
      k += c;
    }
  }
}

void s21_matrix_initialization(matrix_t *matrix, double num) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      matrix->matrix[i][j] = num;
      num++;
    }
  }
}

START_TEST(s21_create_matrix_test_1) {
  matrix_t A = {0};
  ck_assert_int_eq(s21_create_matrix(5, 5, &A), OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_matrix_test_2) {
  matrix_t A = {0};
  ck_assert_int_eq(s21_create_matrix(0, 0, &A), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_test_3) {
  ck_assert_int_eq(s21_create_matrix(5, 5, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_create_matrix_test_4) {
  ck_assert_int_eq(s21_create_matrix(0, 0, NULL), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_remove_matrix_test_1) {
  matrix_t A = {0};
  s21_create_matrix(5, 5, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(s21_remove_matrix_test_2) {
  s21_remove_matrix(NULL);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(s21_remove_matrix_test_3) {
  matrix_t A = {0};
  s21_remove_matrix(&A);
  ck_assert_int_eq(1, 1);
}
END_TEST

START_TEST(s21_remove_matrix_test_4) {
  matrix_t A = {0};
  s21_create_matrix(4, 4, &A);
  s21_remove_matrix(&A);
  ck_assert_ptr_null(A.matrix);
}
END_TEST

START_TEST(s21_eq_matrix_test_1) {
  matrix_t A = {0}, B = {0};
  int result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  init(&A, 1, 1);
  init(&B, 1, 1);
  result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_2) {
  matrix_t A = {0}, B = {0};
  int result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  init(&A, 1.0, 1.0);
  init(&A, 1.0, 1.0);
  B.matrix[1][1] = 0.0;
  result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_3) {
  matrix_t A = {0}, B = {0};
  double num = 0.00001;
  int result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = num;
      B.matrix[i][j] = num;
      num += 0.00001;
    }
  }
  result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_4) {
  matrix_t A = {0}, B = {0};
  double num = 1;
  int result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = num;
      B.matrix[i][j] = num;
      num++;
      num *= num;
    }
  }
  result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_5) {
  matrix_t A = {0}, B = {0};
  int result;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(1, 1, &B);
  init(&A, 1.0, 1.0);
  init(&A, 1.0, 1.0);
  result = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_matrix_test_6) {
  matrix_t A = {0};
  int result;
  s21_create_matrix(3, 3, &A);
  init(&A, 1.0, 1.0);
  result = s21_eq_matrix(&A, NULL);
  ck_assert_int_eq(result, FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_eq_matrix_test_7) {
  matrix_t A = {0}, B = {0};
  s21_create_matrix(0, 0, &A);
  init(&A, 1.0, 1.0);
  s21_create_matrix(0, 0, &B);
  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_sum_matrix_test_1) {
  matrix_t A = {0}, B = {0}, result = {0}, check = {0};
  double numA = 1, numB = 2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &check);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = numA;
      B.matrix[i][j] = numB;
      check.matrix[i][j] = numA + numB;
      numA++;
      numB++;
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_sum_matrix_test_2) {
  matrix_t A = {0}, result = {0};
  double numA = 1, numB = 2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, NULL);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = numA;
      numA++;
      numB++;
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&A, NULL, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_test_3) {
  matrix_t B = {0}, result = {0};
  double numA = 1, numB = 2;
  s21_create_matrix(3, 3, NULL);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      B.matrix[i][j] = numB;
      numA++;
      numB++;
    }
  }
  ck_assert_int_eq(s21_sum_matrix(NULL, &B, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_test_4) {
  matrix_t A = {0}, B = {0}, result = {0};
  double numA = 1, numB = 2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &B);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = numA;
      numA++;
    }
  }

  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      B.matrix[i][j] = numB;
      numB++;
    }
  }

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_test_5) {
  matrix_t A = {0}, B = {0}, result = {0};
  double numA = 1;
  double numB = 1;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = numA;
      numA++;
    }
  }
  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      B.matrix[i][j] = numB;
      numB++;
    }
  }

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_test_6) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(0, 3, &A);
  s21_create_matrix(0, 3, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sum_matrix_test_7) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(3, 0, &A);
  s21_create_matrix(3, 0, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_1) {
  matrix_t A = {0}, B = {0}, result = {0}, check = {0};
  double numA = 1, numB = 2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &check);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = numA;
      B.matrix[i][j] = numB;
      check.matrix[i][j] = numA - numB;
      numA++;
      numB++;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_sub_matrix_test_2) {
  matrix_t A = {0}, result = {0};
  double numA = 1, numB = 2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, NULL);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = numA;
      numA++;
      numB++;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, NULL, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_3) {
  matrix_t B = {0}, result = {0};
  double numA = 1, numB = 2;
  s21_create_matrix(3, 3, NULL);
  s21_create_matrix(3, 3, &B);
  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      B.matrix[i][j] = numB;
      numA++;
      numB++;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(NULL, &B, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_4) {
  matrix_t A = {0}, B = {0}, result = {0};
  double numA = 1, numB = 2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = numA;
      numA++;
    }
  }
  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      B.matrix[i][j] = numB;
      numB++;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_5) {
  matrix_t A = {0}, B = {0}, result = {0};
  double numA = 1;
  double numB = 1;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &B);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = numA;
      numA++;
    }
  }
  for (int i = 0; i < B.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      B.matrix[i][j] = numB;
      numB++;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_6) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(0, 3, &A);
  s21_create_matrix(0, 3, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_sub_matrix_test_7) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(3, 0, &A);
  s21_create_matrix(3, 0, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_test_1) {
  matrix_t A = {0}, result = {0}, check = {0};
  double numA = 1.5, number = 5.0;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &check);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = numA;
      check.matrix[i][j] = numA * number;
      numA++;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, number, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_mult_number_test_2) {
  matrix_t A = {0}, result = {0};
  double numA = 1.5, number = 3;
  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = numA;
      numA++;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, number, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_test_3) {
  matrix_t result = {0};
  double number = 5.0;
  s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(s21_mult_number(NULL, number, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_test_4) {
  matrix_t A = {0}, result = {0};
  double number = 5.0;
  s21_create_matrix(3, 0, &A);
  ck_assert_int_eq(s21_mult_number(&A, number, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_test_5) {
  matrix_t A = {0}, result = {0};
  double number = 5.0;
  s21_create_matrix(0, 3, &A);
  ck_assert_int_eq(s21_mult_number(&A, number, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_test_6) {
  matrix_t A = {0}, result = {0};
  double number = 5.0;

  ck_assert_int_eq(s21_mult_number(NULL, number, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_number_test_7) {
  matrix_t A = {0}, result = {0}, check = {0};
  double numA = 0.0, number = 5.0;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &check);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = numA;
      check.matrix[i][j] = numA;
    }
  }
  ck_assert_int_eq(s21_mult_number(&A, number, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_transpose_test_1) {
  matrix_t A = {0}, result = {0}, check = {0};
  double num = 1.0;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &check);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = num;
      check.matrix[j][i] = num;
      num++;
    }
  }
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_test_2) {
  matrix_t A = {0}, result = {0}, check = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &check);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = 1;
      check.matrix[i][j] = 1;
    }
  }
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_test_3) {
  matrix_t A = {0}, result = {0}, check = {0};
  double num = 1.0;
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &check);
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < A.columns; j++) {
      A.matrix[i][j] = num;
      check.matrix[j][i] = num;
      num++;
    }
  }
  ck_assert_int_eq(s21_transpose(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&check);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_test_4) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(s21_transpose(&A, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_test_5) {
  matrix_t result = {0};
  s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(s21_transpose(NULL, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_transpose_test_6) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(0, 0, NULL);
  ck_assert_int_eq(s21_transpose(NULL, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_test_1) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 5, &B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_test_2) {
  matrix_t A = {0}, B = {0}, result = {0}, check = {0};
  double num = 1.0;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 5, &B);
  s21_create_matrix(3, 5, &check);
  s21_matrix_initialization(&A, num);
  num = 1;
  s21_matrix_initialization(&B, num);
  num = 1;
  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      check.matrix[i][j] = 0;
      for (int k = 0; k < A.columns; k++) {
        check.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
      }
    }
  }
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &check), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_mult_matrix_test_3) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(4, 5, &B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_test_4) {
  matrix_t A = {0}, B = {0}, result = {0};
  s21_create_matrix(0, 0, &A);
  s21_create_matrix(0, 0, &B);
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_mult_matrix_test_5) {
  matrix_t result = {0};
  s21_create_matrix(3, 3, NULL);
  s21_create_matrix(3, 5, NULL);
  ck_assert_int_eq(s21_mult_matrix(NULL, NULL, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_determinant_test_1) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(1, 1, &A);
  s21_matrix_initialization(&A, 1.0);
  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, 1.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_2) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(2, 2, &A);
  s21_matrix_initialization(&A, 1.0);
  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, -2.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_3) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(3, 3, &A);
  s21_matrix_initialization(&A, 1.0);
  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, 0.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_4) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(4, 4, &A);
  s21_matrix_initialization(&A, 1.0);
  ck_assert_int_eq(s21_determinant(&A, &result), OK);
  ck_assert_double_eq(result, 0.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_5) {
  double result;
  ck_assert_int_eq(s21_determinant(NULL, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_determinant_test_6) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(2, 3, &A);
  s21_matrix_initialization(&A, 1.0);
  ck_assert_int_eq(s21_determinant(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_7) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(s21_determinant(&A, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_determinant_test_8) {
  matrix_t A = {0};
  double result;
  s21_create_matrix(0, 2, &A);
  s21_matrix_initialization(&A, 1);
  ck_assert_int_eq(s21_determinant(&A, &result), INCORRECT_MATRIX);
  // ck_assert_double_eq(result, -2.0);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_calc_complements_test_1) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;
  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_double_eq(result.matrix[0][0], 0.0);
  ck_assert_double_eq(result.matrix[0][1], 10.0);
  ck_assert_double_eq(result.matrix[0][2], -20.0);
  ck_assert_double_eq(result.matrix[1][0], 4.0);
  ck_assert_double_eq(result.matrix[1][1], -14.0);
  ck_assert_double_eq(result.matrix[1][2], 8.0);
  ck_assert_double_eq(result.matrix[2][0], -8.0);
  ck_assert_double_eq(result.matrix[2][1], -2.0);
  ck_assert_double_eq(result.matrix[2][2], 4.0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_test_2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(s21_calc_complements(&A, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_test_3) {
  matrix_t result = {0};
  s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(s21_calc_complements(NULL, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_test_4) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 4, &A);
  ck_assert_int_eq(s21_calc_complements(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_test_5) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 1;
  ck_assert_int_eq(s21_calc_complements(&A, &result), OK);
  ck_assert_double_eq(result.matrix[0][0], 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_calc_complements_test_6) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = 112.0;
  A.matrix[0][1] = 243.0;
  A.matrix[0][2] = 3.0;
  A.matrix[0][3] = -8.0;
  A.matrix[1][0] = 47.0;
  A.matrix[1][1] = 51.0;
  A.matrix[1][2] = -66.0;
  A.matrix[1][3] = 99.0;
  A.matrix[2][0] = -74.0;
  A.matrix[2][1] = 85.0;
  A.matrix[2][2] = 97.0;
  A.matrix[2][3] = 63.0;
  A.matrix[3][0] = -13.0;
  A.matrix[3][1] = 79.0;
  A.matrix[3][2] = -99.0;
  A.matrix[3][3] = -121.0;

  s21_calc_complements(&A, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = -2879514.0;
  X.matrix[0][1] = -1236631.0;
  X.matrix[0][2] = -1685096.0;
  X.matrix[0][3] = 880697.0;
  X.matrix[1][0] = 1162090.0;
  X.matrix[1][1] = -714015.0;
  X.matrix[1][2] = 4046255.0;
  X.matrix[1][3] = -3901600.0;
  X.matrix[2][0] = 4362897.0;
  X.matrix[2][1] = -2049432.0;
  X.matrix[2][2] = -532912.0;
  X.matrix[2][3] = -1370781.0;
  X.matrix[3][0] = 3412773.0;
  X.matrix[3][1] = -1569493.0;
  X.matrix[3][2] = 3144517.0;
  X.matrix[3][3] = 1284666.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_calc_complements_test_7) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[0][3] = 9.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[2][3] = 21.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;

  s21_calc_complements(&A, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = -30.0;
  X.matrix[0][2] = -108.0;
  X.matrix[0][3] = 106.0;
  X.matrix[1][0] = 138.0;
  X.matrix[1][1] = -726.0;
  X.matrix[1][2] = -1137.0;
  X.matrix[1][3] = 1061.0;
  X.matrix[2][0] = 0.0;
  X.matrix[2][1] = 12.0;
  X.matrix[2][2] = 57.0;
  X.matrix[2][3] = -47.0;
  X.matrix[3][0] = 0.0;
  X.matrix[3][1] = 6.0;
  X.matrix[3][2] = -75.0;
  X.matrix[3][3] = 57.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_calc_complements_test_8) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(4, 3, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;

  res = s21_calc_complements(&A, &Z);

  s21_remove_matrix(&A);

  ck_assert_int_eq(res, CALCULATION_ERROR);
}
END_TEST

START_TEST(s21_calc_complements_test_9) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);

  res = s21_calc_complements(&A, &Z);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_inverse_matrix_test_1) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;
  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 1.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][1], -1.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[0][2], 1.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][0], -38.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][1], 41.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[1][2], -34.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][0], 27.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][1], -29.0, 1e-7);
  ck_assert_double_eq_tol(result.matrix[2][2], 24.0, 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_test_2) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(0, 0, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_test_3) {
  matrix_t result = {0};
  s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(s21_inverse_matrix(NULL, &result), INCORRECT_MATRIX);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_test_4) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 4, &A);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_test_5) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_double_eq_tol(result.matrix[0][0], 0.2, 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_test_6) {
  matrix_t A = {0}, result = {0};
  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 4;
  A.matrix[1][1] = 5;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 7;
  A.matrix[2][1] = 8;
  A.matrix[2][2] = 9;
  ck_assert_int_eq(s21_inverse_matrix(&A, NULL), CALCULATION_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(s21_inverse_matrix_test_7) {
  // failure when matrix has determinant equal to zero
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(3, 3, &A);
  init(&A, 1.0, 1.0);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_test_8) {
  // failure with non-square matrix
  matrix_t A = {};
  matrix_t result = {};
  s21_create_matrix(5, 3, &A);
  init(&A, 1.0, 1.0);
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_test_9) {
  // success matrix 1x1
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &eq_matrix);
  A.matrix[0][0] = 21.0;
  eq_matrix.matrix[0][0] = 1.0 / 21.0;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_inverse_matrix_test_10) {
  // success with task reference values
  matrix_t A = {};
  matrix_t result = {};
  matrix_t eq_matrix = {};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &eq_matrix);
  A.matrix[0][0] = 2.0, A.matrix[0][1] = 5.0, A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0, A.matrix[1][1] = 3.0, A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0, A.matrix[2][1] = -2.0, A.matrix[2][2] = -3.0;
  eq_matrix.matrix[0][0] = 1, eq_matrix.matrix[0][1] = -1,
  eq_matrix.matrix[0][2] = 1;
  eq_matrix.matrix[1][0] = -38, eq_matrix.matrix[1][1] = 41,
  eq_matrix.matrix[1][2] = -34;
  eq_matrix.matrix[2][0] = 27, eq_matrix.matrix[2][1] = -29,
  eq_matrix.matrix[2][2] = 24;
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), OK);
  ck_assert_int_eq(s21_eq_matrix(&result, &eq_matrix), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&eq_matrix);
}
END_TEST

START_TEST(s21_inverse_matrix_test_11) {
  // failure with INCORRECT_MATRIX
  matrix_t A = {};
  matrix_t result = {};
  ck_assert_int_eq(s21_inverse_matrix(&A, &result), INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_inverse_matrix_test_12) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(4, 4, &A);
  A.matrix[0][0] = -1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 7.0;
  A.matrix[0][3] = 9.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 0.0;
  A.matrix[1][2] = 0.0;
  A.matrix[1][3] = 0.0;
  A.matrix[2][0] = 47.0;
  A.matrix[2][1] = 13.0;
  A.matrix[2][2] = 17.0;
  A.matrix[2][3] = 21.0;
  A.matrix[3][0] = 22.0;
  A.matrix[3][1] = 7.0;
  A.matrix[3][2] = 1.0;
  A.matrix[3][3] = 3.0;

  s21_inverse_matrix(&A, &Z);

  s21_create_matrix(4, 4, &X);

  X.matrix[0][0] = 0.0;
  X.matrix[0][1] = 1.0;
  X.matrix[0][2] = 0.0;
  X.matrix[0][3] = 0.0;
  X.matrix[1][0] = -5.0 / 23.0;
  X.matrix[1][1] = -121.0 / 23.0;
  X.matrix[1][2] = 2.0 / 23.0;
  X.matrix[1][3] = 1.0 / 23.0;
  X.matrix[2][0] = -18.0 / 23.0;
  X.matrix[2][1] = -379.0 / 46.0;
  X.matrix[2][2] = 19.0 / 46.0;
  X.matrix[2][3] = -25.0 / 46.0;
  X.matrix[3][0] = 53.0 / 69.0;
  X.matrix[3][1] = 1061.0 / 138.0;
  X.matrix[3][2] = -47.0 / 138.0;
  X.matrix[3][3] = 19.0 / 46.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_inverse_matrix_test_13) {
  int res;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 2;

  res = s21_inverse_matrix(&A, &Z);

  ck_assert_int_eq(Z.matrix[0][0] == (1.0 / A.matrix[0][0]), 1);
  ck_assert_int_eq(res, OK);

  s21_remove_matrix(&A);
  s21_remove_matrix(&Z);
}
END_TEST

START_TEST(s21_inverse_matrix_test_15) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(3, 2, &A);
  init(&A, 1.0, 1.0);

  res = s21_inverse_matrix(&A, &Z);
  ck_assert_int_eq(res, CALCULATION_ERROR);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_test_16) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};

  s21_create_matrix(3, 3, &A);
  init(&A, 1.0, 1.0);
  s21_remove_matrix(&A);

  res = s21_inverse_matrix(&A, &Z);

  ck_assert_int_eq(res, INCORRECT_MATRIX);
}
END_TEST

START_TEST(s21_inverse_matrix_test_17) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 8.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 9.0;

  s21_inverse_matrix(&A, &Z);

  s21_create_matrix(3, 3, &X);

  X.matrix[0][0] = -3.0 / 5.0;
  X.matrix[0][1] = 0.0;
  X.matrix[0][2] = 1.0 / 5.0;
  ;
  X.matrix[1][0] = -4.0 / 5.0;
  X.matrix[1][1] = 1.0;
  X.matrix[1][2] = -2.0 / 5.0;
  X.matrix[2][0] = 16.0 / 15.0;
  X.matrix[2][1] = -2.0 / 3.0;
  X.matrix[2][2] = 1.0 / 5.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

Suite *s21_matrix_suite() {
  Suite *s;
  TCase *tc;

  s = suite_create("s21_matrix_suite");
  tc = tcase_create("s21_matrix_case");

  tcase_add_test(tc, s21_create_matrix_test_1);
  tcase_add_test(tc, s21_create_matrix_test_2);
  tcase_add_test(tc, s21_create_matrix_test_3);
  tcase_add_test(tc, s21_create_matrix_test_4);
  tcase_add_test(tc, s21_remove_matrix_test_1);
  tcase_add_test(tc, s21_remove_matrix_test_2);
  tcase_add_test(tc, s21_remove_matrix_test_3);
  tcase_add_test(tc, s21_remove_matrix_test_4);
  tcase_add_test(tc, s21_eq_matrix_test_1);
  tcase_add_test(tc, s21_eq_matrix_test_2);
  tcase_add_test(tc, s21_eq_matrix_test_3);
  tcase_add_test(tc, s21_eq_matrix_test_4);
  tcase_add_test(tc, s21_eq_matrix_test_5);
  tcase_add_test(tc, s21_eq_matrix_test_6);
  tcase_add_test(tc, s21_eq_matrix_test_7);
  tcase_add_test(tc, s21_sum_matrix_test_1);
  tcase_add_test(tc, s21_sum_matrix_test_2);
  tcase_add_test(tc, s21_sum_matrix_test_3);
  tcase_add_test(tc, s21_sum_matrix_test_4);
  tcase_add_test(tc, s21_sum_matrix_test_5);
  tcase_add_test(tc, s21_sum_matrix_test_6);
  tcase_add_test(tc, s21_sum_matrix_test_7);
  tcase_add_test(tc, s21_sub_matrix_test_1);
  tcase_add_test(tc, s21_sub_matrix_test_2);
  tcase_add_test(tc, s21_sub_matrix_test_3);
  tcase_add_test(tc, s21_sub_matrix_test_4);
  tcase_add_test(tc, s21_sub_matrix_test_5);
  tcase_add_test(tc, s21_sub_matrix_test_6);
  tcase_add_test(tc, s21_sub_matrix_test_7);
  tcase_add_test(tc, s21_mult_number_test_1);
  tcase_add_test(tc, s21_mult_number_test_2);
  tcase_add_test(tc, s21_mult_number_test_3);
  tcase_add_test(tc, s21_mult_number_test_4);
  tcase_add_test(tc, s21_mult_number_test_5);
  tcase_add_test(tc, s21_mult_number_test_6);
  tcase_add_test(tc, s21_mult_number_test_7);
  tcase_add_test(tc, s21_transpose_test_1);
  tcase_add_test(tc, s21_transpose_test_2);
  tcase_add_test(tc, s21_transpose_test_3);
  tcase_add_test(tc, s21_transpose_test_4);
  tcase_add_test(tc, s21_transpose_test_5);
  tcase_add_test(tc, s21_transpose_test_6);
  tcase_add_test(tc, s21_mult_matrix_test_1);
  tcase_add_test(tc, s21_mult_matrix_test_2);
  tcase_add_test(tc, s21_mult_matrix_test_3);
  tcase_add_test(tc, s21_mult_matrix_test_4);
  tcase_add_test(tc, s21_mult_matrix_test_5);
  tcase_add_test(tc, s21_determinant_test_1);
  tcase_add_test(tc, s21_determinant_test_2);
  tcase_add_test(tc, s21_determinant_test_3);
  tcase_add_test(tc, s21_determinant_test_4);
  tcase_add_test(tc, s21_determinant_test_5);
  tcase_add_test(tc, s21_determinant_test_6);
  tcase_add_test(tc, s21_determinant_test_7);
  tcase_add_test(tc, s21_determinant_test_8);
  tcase_add_test(tc, s21_calc_complements_test_1);
  tcase_add_test(tc, s21_calc_complements_test_2);
  tcase_add_test(tc, s21_calc_complements_test_3);
  tcase_add_test(tc, s21_calc_complements_test_4);
  tcase_add_test(tc, s21_calc_complements_test_5);
  tcase_add_test(tc, s21_calc_complements_test_6);
  tcase_add_test(tc, s21_calc_complements_test_7);
  tcase_add_test(tc, s21_calc_complements_test_8);
  tcase_add_test(tc, s21_calc_complements_test_9);
  tcase_add_test(tc, s21_inverse_matrix_test_1);
  tcase_add_test(tc, s21_inverse_matrix_test_2);
  tcase_add_test(tc, s21_inverse_matrix_test_3);
  tcase_add_test(tc, s21_inverse_matrix_test_4);
  tcase_add_test(tc, s21_inverse_matrix_test_5);
  tcase_add_test(tc, s21_inverse_matrix_test_6);
  tcase_add_test(tc, s21_inverse_matrix_test_7);
  tcase_add_test(tc, s21_inverse_matrix_test_8);
  tcase_add_test(tc, s21_inverse_matrix_test_9);
  tcase_add_test(tc, s21_inverse_matrix_test_10);
  tcase_add_test(tc, s21_inverse_matrix_test_11);
  tcase_add_test(tc, s21_inverse_matrix_test_12);
  tcase_add_test(tc, s21_inverse_matrix_test_13);
  tcase_add_test(tc, s21_inverse_matrix_test_15);
  tcase_add_test(tc, s21_inverse_matrix_test_16);
  tcase_add_test(tc, s21_inverse_matrix_test_17);

  suite_add_tcase(s, tc);

  return s;
}

int main() {
  int failed_count = 0;

  Suite *s;
  SRunner *sr;

  s = s21_matrix_suite();
  sr = srunner_create(s);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  failed_count = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}