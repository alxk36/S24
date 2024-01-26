/*
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
  double **matrix = (double **)malloc(size * sizeof(double *)); // New Matrix allocated in first array

  for (int i = 0; i < size; i++)                       // Allocating the inside
    matrix[i] = (double *)malloc(size * sizeof(double));

  return matrix;
}



void mm_free(int size, double **matrix)       // Freeing all the Manually Allocated Memory for no Memory Leaks
{
  for (int i = 0; i < size; i++)              // Looping through to deallocate the inner matrix
    free(matrix[i]);

  free(matrix);                               // Freeing the main matrix
}



void mm_print(int size, double **matrix) 
{
  if (matrix == NULL) return;    // Base Case for non-existing matrixes

  printf("%d\n", size);
  for (int i = 0; i < size; i++) {
    for (int j = 0; j < size; j++) printf("%10.2lf\t", matrix[i][j]);
    printf("\n");
  }

}



double **mm_read(char *filename, int *size)                       // Reading Input File for Data
{
  FILE *inputFile = fopen(filename, "r");                         // Opening File

  if (inputFile == NULL) {                                        // Error Message
    fprintf(stderr, "Error opening file %s\n", filename);
    exit(EXIT_FAILURE);
  }

  fscanf(inputFile, "%d", size);                         // Assigning Size

  double **matrix = mm_alloc(*size);                     // Reallocating memory for the matrix

  for ( i = 0; i < *size; i++)
    for ( j = 0; j < *size; j++)
      fscanf(inputFile, "%lf", &matrix[i][j]);           // Iterating through matrix and assigning the data

  fclose(inputFile);                                     // Closing File
  return matrix;                                         // Return Statement
}



double **mm_swap(int size, double **matrix) {
    if (size < 3) return matrix; // Matrix is too small to swap

    double **newMatrix = mm_alloc(size);

    for (int i = 0; i < size; i++) {
        // Swap the last two columns
        newMatrix[i][size - 2] = matrix[i][size - 1];
        newMatrix[i][size - 1] = matrix[i][size - 2];
        
        // Copy the rest of the columns
        for (int j = 0; j < size - 2; j++) {
            newMatrix[i][j] = matrix[i][j];
        }
    }

    return newMatrix;
}



double **mm_matrix_mult(int size, double **matrix, double **swap)
{
/*
Notes:
  First construct a result matrix
  Then perform the multiplication
  Then return a pointer to your result matrix

  double **result = mm_alloc(size);

  for (int i = 0; i < size; i ++){

  }*/

  return matrix;
}



void mm_write(char *filename, int size, double **matrix)
{
  /*
  This function receives the name of the output file from the 
  main function, and writes the resulting matrix into that file.
  The size is written in the first line. Then function writes 
  each element of the matrix in one line just like the input file. 
  Please use fprintf() when you want to write the resulting matrix into
  the output file. Also remember to use "%lf\n" as the format 
  specifier to print each matrix element to the file. This makes sure that
  all the outputs are in the same format for autograding on Submitty. 
  */
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
  //result_matrix = mm_matrix_mult(size, matrix, swap_matrix);

  //mm_write(output_f, size, result_matrix);

  //mm_print(size, result_matrix);
  mm_free(size, matrix);
  mm_free(size, swap_matrix);
  //mm_free(size, result_matrix);
  
//mm_print(size, matrix);
  return 0;
}