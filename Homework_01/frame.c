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
void mm_print(int size, double **matrix)
double **mm_read(char *filename, int *size)
double **mm_matrix_mult(int size, double **matrix, double **swap);
void mm_write(char *filename, int size, double **matrix);


double **mm_alloc(int size)
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
}

void mm_free(int size, double **matrix)
{
  /*
  Notes:
    Reverse the allocation process, but you'll be calling free() instead
  */
}

void mm_print(int size, double **matrix) {
  /*
  Notes:
    Print all the data values in your matrix
    Go row by row
    At the end of each row, print a newline
    Between each data value, insert a tab
    Use 2 digits of precision after the decimal (use "%10.2lf\t" as format string)
  */
}

double **mm_read(char* filename, int *size)
{
/*
Notes:
  Use fopen to open the matrix file, then use fgets or getline to read lines
  The first line of the matrix contains the integer for number of rows (columns) N.
  - Use this to allocate your arrays for matrix data
  Each subsequent line contains a single data value
  - You can use sscanf to parse each matrix entry
  - First value is data[0][0], next is data[0][1] ... data[N-1][N-1]
*/
}

double **mm_swap(int size, double **matrix) {
/*
  This function is used to perform the swap operation required 
  to generate the second operand (matrix). 
*/
}

double **mm_matrix_mult(int size, double **matrix, double **swap) {
/*
Notes:
  First construct a result matrix
  Then perform the multiplication
  Then return a pointer to your result matrix
*/
}

void mm_write(char *filename, int size, double **matrix) {
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

int main(int argc, char *argv[])
{
  /*
  * you must keep this function AS IS.
  * you cannot modify it!
  */

  if (argc<2) {
    printf("Please provide the file name for input.\n");
    return EXIT_FAILURE;
  }

  char input_f[256];
  char output_f[256];
  double **matrix = NULL;
  double **swap_matrix = NULL;
  double **result_matrix = NULL;
  int size=0;

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