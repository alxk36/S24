/*
Github: alxk36

This code was templated by Masoud Zarifneshat.
Homework 01: NxN Matrix Multiplication
CSCI-2500 Spring 2024
*/

/******************************************************************************/
/* Usual suspects to include  */
/******************************************************************************/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>


/******************************************************************************/
/* Function Calls */
/******************************************************************************/

double **mm_alloc(int size);
void mm_free (int size, double **matrix);
void mm_print(int size, double **matrix);
double **mm_read(char *filename, int *size);
double **mm_matrix_mult(int size, double **matrix, double **swap);
void mm_write(char *filename, int size, double **matrix);


double **mm_alloc(int size) 
{
  double **matrix = (double **)malloc(size * sizeof(double *));// New Matrix allocated in first array

  for (int i = 0; i < size; i++)                               // Allocating the inside
    matrix[i] = (double *)malloc(size * sizeof(double));

  for (int i = 0; i < size; i++)                               // Initializing to 0
    for (int j = 0; j < size; j++)
      matrix[i][j] = 0.0;

  return matrix;
}



void mm_free(int size, double **matrix)       // Freeing all the Manually Allocated Memory for no Memory Leaks
{
  for (int i = 0; i < size; i++)              // Looping through to deallocate the inner matrix
    if (matrix[i] != NULL) free(matrix[i]);


  free(matrix);                               // Freeing the main matrix
}



void mm_print(int size, double **matrix) 
{
  if (matrix == NULL) return;                            // Base Case for non-existing matrixes

  printf("%d\n", size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) printf("%10.2lf\t", matrix[i][j]);
    printf("\n");
  }

}



double **mm_read(char *filename, int *size)               // Reading Input File for Data
{
  FILE *inputFile = fopen(filename, "r");                // Opening File

  if (inputFile == NULL) {                               // Error Message
    fprintf(stderr, "Error while opening file %s\n", filename);
    exit(EXIT_FAILURE);
  }

  fscanf(inputFile, "%d", size);                         // Assigning Size

  double **matrix = mm_alloc(*size);                     // Reallocating memory for the matrix

  for (int i = 0; i < *size; i++)
    for (int j = 0; j < *size; j++)
      fscanf(inputFile, "%lf", &matrix[i][j]);           // Iterating through matrix and assigning the data

  fclose(inputFile);                                     // Closing File
  return matrix;                                         // Return Statement
}



double **mm_swap(int size, double **matrix)               // Swapping Columns
{
  if (size < 3) return matrix;                            // Matrix is too small to swap


  double **newMatrix = mm_alloc(size);                    // The Returning Swapped Matrix
  // Temporary Matrix for the first two column to be assigned after the rest is swapped
  double **tmpMatrix = mm_alloc(size);

  for (int i = 0; i < size; i++) {                        // Iterating through the Matrix
    for (int j = 0; j < size - 2; j++) {

      if (j == 0 && size % 2 == 0)                        // Storing condition for Even Matrix
        tmpMatrix[i][j] = matrix[i][j];
      else if (j == 1 && size % 2 == 0)                   // Storing condition for Even Matrix
        tmpMatrix[i][j] = matrix[i][j];
      else if (j == 0 && size % 2 == 1)                   // Storing condition for Odd Matrix
        tmpMatrix[i][1] = matrix[i][j];
      else if (j == 1 && size % 2 == 1)                   // Storing condition for Odd Matrix
        tmpMatrix[i][0] = matrix[i][j];

      newMatrix[i][j] = matrix[i][j+2];                   // Swap Statement for rest
    }
  }
  if (size == 3)                                          // Special Case for 3 Columns
    for (int i = 0; i < size; i++) {
      newMatrix[i][1] = matrix[i][1];
      newMatrix[i][2] = tmpMatrix[i][1];
    }
  else
    for (int i = 0; i < size; i++) {
      int k = 0;
      for (int j = 2; j > 0; j--, k++)
        newMatrix[i][size-j] = tmpMatrix[i][k];
    }
  
  mm_free(size, tmpMatrix);

  return newMatrix;
}



double **mm_matrix_mult(int size, double **matrix, double **swap)
{
  double **result = mm_alloc(size);                       // Initialzing return variable

  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) {
      double term = 0;                                    // Temporary Value to add the Multiplied Terms
      for (int k = 0; k < size; k++)
        term += matrix[i][k] * swap[k][j];                // I found the pattern to solve this
      result[i][j] = term;                                // Just needed a Pattern
    }
  }

  return result;
}



void mm_write(char *filename, int size, double **matrix)
{
  FILE *outputFile = fopen(filename, "w");                // Opening Output File

  if (outputFile == NULL) {                               // Error Message
    fprintf(stderr, "Error while opening output file.\n");
    exit(-1);
  }
  fprintf(outputFile, "%d\n", size);                      // Output Size
  
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      fprintf(outputFile, "%lf\n", matrix[i][j]);

  fclose(outputFile);                                     // Closing File
}




int main(int argc, char *argv[]) {
  if (argc<2) {
    printf("Please provide the file name for input.\n");
    return EXIT_FAILURE;
  }

  char input_f[256];
  char output_f[256];
  double **matrix = NULL;
  double **swap_matrix = NULL;
  double **result_matrix = NULL;
  int size = 0;

  strcpy(input_f, argv[1]);
  strcpy(output_f, "result.mat");

  matrix = mm_read(input_f, &size);
  swap_matrix = mm_swap(size, matrix);
  result_matrix = mm_matrix_mult(size, matrix, swap_matrix);

  mm_write(output_f, size, result_matrix);

  mm_print(size, result_matrix);
  mm_free(size, matrix);
  mm_free(size, swap_matrix);
  mm_free(size, result_matrix);
  

  return 0;
}