#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include "read.h"

int mm_read(char* filename, matrix* mat) 
{
/*
Notes:
  Use fopen to open the matrix file, then use fgets or getline to read lines
  The first line of the matrix contains integers for "#rows #columns"
  - Use these to allocate your arrays for matrix data
  Each subsequent line contains a single data value
  - You can use sscanf to parse each matrix entry
  - First value is data[0][0], next is data[0][1] ... data[#rows-1][#columns-1]
*/
  FILE *matrix_file = NULL;
  mat->data         = NULL;
  char buffer[256];
  
  if (NULL == (matrix_file = fopen(filename, "r"))) {
    // file doesn't exist, or error occurred
    printf("mm_read: failed to open file.");
    exit(-1);
  }
  
  if (NULL == fgets(buffer, 256, matrix_file)) {
    // file is empty
    printf("mm_read: failed to read from file.");
    exit(-1);
  }
  
  if (2 != sscanf(buffer, "%d %d", &mat->rows, &mat->cols)) {
    // number of integers on first row is not equal to 2
    // so there is a formatting issue with the matrix file
    printf("mm_read: failed to read matrix dimensions.\n");
    exit(-1);
  }
  
  mm_alloc(mat);
  
  // Read matrix row by row, if we encounter eof or an empty line,
  // we know there's some formatting issues with the file
  for (int i = 0; i < mat->rows; ++i) {
    for (int j = 0; j < mat->cols; ++j) {
      if (NULL == fgets(buffer, 256, matrix_file)) {
        // we prematurely hit the end of the file
        printf("mm_read: failed to read matrix values.\n");
        exit(-1);
      }
      if (1 != sscanf(buffer, "%lf", &mat->data[i][j])) {
        // we've hit a line without any float value
        printf("mm_read: failed to read matrix values.\n");
        exit(-1);
      }
    }
  }
  
  if(0 != fclose(matrix_file)) {
    // Error closing file - you didn't need to check for this
    printf("mm_read: fclose failed: %s\n", strerror(errno));
  }
  
  return 0;
}