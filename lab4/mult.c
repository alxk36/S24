#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "alloc.h"
#include "mult.h"



matrix* mm_matrix_mult(matrix* mat1, matrix* mat2)
{
/*
Notes:
  First check that it is actually possible to multiply the two inputs
  If so, construct a result matrix
  Then perform the multiplication
  Then return a pointer to your result matrix
*/
  if (mat1->cols != mat2->rows) {
    printf("mm_matrix_mult: dimension mismatch between matrices.\n");
    exit(-1);
  }
  
  matrix* result = (matrix*)malloc(sizeof(matrix));
  result->rows = mat1->rows;
  result->cols = mat2->cols;
  mm_alloc(result);
  
  for(int i = 0; i < mat1->rows; ++i) {
    for(int j = 0; j < mat2->cols; ++j) {
      for(int k = 0; k < mat1->cols; ++k) {
        // Note: because I called calloc() to initialize, I can
        // directly place results into and update data[i][j]
        result->data[i][j] +=  mat1->data[i][k] * mat2->data[k][j];
      }
    }
  }
  
  return result;
}
