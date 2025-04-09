#include "../s21_matrix.h"

int are_matrices_same_size(matrix_t *A, matrix_t *B) {
  return (A->rows == B->rows && A->columns == B->columns) ? SUCCESS : FAILURE;
}

int cheks(matrix_t *A) {
  int result_code = OK;
  if (A == NULL || A->matrix == NULL || A->columns <= 0 || A->rows <= 0) {
    result_code = INCORRECT_MATRIX;
  }
  return result_code;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  if (rows < 1 || columns < 1 || result == NULL) {
    return INCORRECT_MATRIX;
  }

  result->rows = rows;
  result->columns = columns;

  result->matrix = calloc(rows, sizeof(double));
  if (result->matrix == NULL) {
    return INCORRECT_MATRIX;
  }
  for (int i = 0; i < rows; i++) {
    result->matrix[i] = calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      return INCORRECT_MATRIX;
    }
  }
  return OK;
}

void s21_remove_matrix(matrix_t *A) {
  if (cheks(A) == OK) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
      A->matrix[i] = NULL;
    }
    free(A->matrix);
    A->matrix = NULL;
    A->columns = 0;
    A->rows = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  if (cheks(A) || cheks(B)) {
    return FAILURE;
  }
  int error_code = SUCCESS;
  if (are_matrices_same_size(A, B)) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
          error_code = FAILURE;
        }
      }
    }
  } else {
    error_code = FAILURE;
  }
  return error_code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL) {
    return INCORRECT_MATRIX;
  }
  int error_code = OK;
  if (!are_matrices_same_size(A, B)) {
    return CALCULATION_ERROR;
  }
  error_code = s21_create_matrix(A->rows, A->columns, result);
  if (error_code == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return error_code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL) {
    return INCORRECT_MATRIX;
  }
  int error_code = OK;
  if (!are_matrices_same_size(A, B)) {
    return CALCULATION_ERROR;
  }
  error_code = s21_create_matrix(A->rows, A->columns, result);
  if (error_code == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return error_code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (cheks(A) == INCORRECT_MATRIX) return INCORRECT_MATRIX;

  int error_code = s21_create_matrix(A->rows, A->columns, result);

  if (error_code == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return error_code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL) {
    return INCORRECT_MATRIX;
  }
  if (A->columns != B->rows) return CALCULATION_ERROR;

  int error_code = s21_create_matrix(A->rows, B->columns, result);

  if (error_code == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return error_code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  if (cheks(A) == INCORRECT_MATRIX) return INCORRECT_MATRIX;

  int res = s21_create_matrix(A->columns, A->rows, result);

  if (res == OK) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  if (s21_is_matrix_valid_full(A) || result == NULL) return INCORRECT_MATRIX;
  if (A->rows != A->columns) return CALCULATION_ERROR;
  int count_row = A->rows;
  int flag = 0;
  double det = 1.0;
  matrix_t tmp = {0};
  s21_create_matrix(count_row, count_row, &tmp);
  s21_copy_matrix(A, &tmp);
  for (int i = 0; i < count_row && flag == 0; i++) {
    int max_row = i;
    for (int k = i + 1; k < count_row; k++) {
      if (fabs(tmp.matrix[k][i]) > fabs(tmp.matrix[max_row][i])) {
        max_row = k;
      }
    }
    if (max_row != i) {
      for (int j = i; j < count_row; j++) {
        double temp = tmp.matrix[i][j];
        tmp.matrix[i][j] = tmp.matrix[max_row][j];
        tmp.matrix[max_row][j] = temp;
      }
      det *= -1;
    }
    if (fabs(tmp.matrix[i][i]) < 1e-7) {
      *result = 0;
      flag = 1;
    }
    for (int k = i + 1; k < count_row && flag == 0; k++) {
      double factor = tmp.matrix[k][i] / tmp.matrix[i][i];
      for (int j = i; j < count_row; j++) {
        tmp.matrix[k][j] -= factor * tmp.matrix[i][j];
      }
    }
  }
  if (flag == 0) {
    for (int i = 0; i < count_row; i++) {
      det *= tmp.matrix[i][i];
    }
    *result = det;
  }
  s21_remove_matrix(&tmp);
  return OK;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int return_code = OK;

  if (result == NULL || s21_is_matrix_valid_full(A))
    return_code = INCORRECT_MATRIX;
  else if (A->rows != A->columns)
    return_code = CALCULATION_ERROR;
  else if (A->rows == 1 && A->columns == 1) {
    s21_create_matrix(1, 1, result);
    result->matrix[0][0] = 1.0;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    matrix_t M;
    s21_create_matrix(A->rows - 1, A->columns - 1, &M);

    double det_minor = 0.0;
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        s21_minor(i, j, A, &M);
        s21_determinant(&M, &det_minor);
        result->matrix[i][j] = det_minor * pow(-1.0, i + j);
      }
    }
    s21_remove_matrix(&M);
  }

  return return_code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int return_code = OK;

  if (s21_is_matrix_valid_full(A))
    return INCORRECT_MATRIX;
  else if (result == NULL || A->rows != A->columns)
    return CALCULATION_ERROR;

  double det = 0.0;
  s21_determinant(A, &det);

  if (det != 0.0) {
    matrix_t M;
    matrix_t T;
    s21_calc_complements(A, &M);
    s21_transpose(&M, &T);
    s21_mult_number(&T, 1.0 / det, result);
    s21_remove_matrix(&M);
    s21_remove_matrix(&T);
  } else {
    return_code = CALCULATION_ERROR;
  }
  return return_code;
}

int s21_is_matrix_valid(matrix_t *matrix) {
  return matrix != NULL && matrix->matrix != NULL && matrix->rows > 0 &&
         matrix->columns > 0;
}

int s21_is_matrix_valid_full(matrix_t *matrix) {
  int return_code = OK;

  if (s21_is_matrix_valid(matrix) == 0) {
    return_code = INCORRECT_MATRIX;
    return return_code;
  }

  for (int i = 0; i < matrix->rows && return_code == OK; i++) {
    if (matrix->matrix[i] != NULL)
      return_code = OK;
    else {
      return_code = INCORRECT_MATRIX;
    }
  }

  for (int i = 0; i < matrix->rows && return_code == OK; i++) {
    for (int j = 0; j < matrix->columns && return_code == OK; j++) {
      if (isfinite(matrix->matrix[i][j]))
        return_code = OK;
      else {
        return_code = INCORRECT_MATRIX;
      }
    }
  }

  return return_code;
}

void s21_copy_matrix(matrix_t *A, matrix_t *result) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j];
    }
  }
}

void s21_minor(int row, int col, matrix_t *A, matrix_t *result) {
  int n, m = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == row) continue;
    n = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == col) continue;
      result->matrix[m][n] = A->matrix[i][j];
      n++;
    }
    m++;
  }
}