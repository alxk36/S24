#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "alloc.h"


int mm_alloc(matrix* mat)
{
/*
Notes:
  Allocate an array of pointers to a double
  Then, allocate an row/array of doubles and assign each double pointer that row
  Make sure you're allocating using mat->data in the matrix struct
  You can use calloc for allocation and zeroing out all the bytes
  - otherwise, you'd want to manually set all arrays to 0 (good practice)
  If your malloc/calloc returns null, the allocation failed
*/
  mat->data = calloc(mat->rows, sizeof(double*));
  if (mat->data == NULL) {
    printf("mm_alloc: allocation failed.\n");
    exit(-1);
  }
  
  for (int i = 0; i < mat->rows; ++i) {
    mat->data[i] = (double *)calloc(mat->cols, sizeof(double));
    if(mat->data[i] == NULL) {
      printf("mm_alloc: allocation failed.\n");
      exit(-1);
    }
  }
  
  return 0;
}



int mm_free(matrix* mat)
{
/*
Notes:
  Reverse the allocation process, but you'll be calling free() instead
*/
  for (int i = 0; i < mat->rows; ++i) {
    free(mat->data[i]);
  }
  free(mat->data);
  /* note: free does not return a value */
  
  return 0;
}
