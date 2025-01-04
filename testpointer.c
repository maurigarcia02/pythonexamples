
#include <stdio.h>
#include <stdlib.h>

struct Matrix
{
    int rows;     // number of rows
    int cols;     // number of columns
    double *data; // <- note that this is a pointer to one dim array
};

typedef struct Matrix Matrix; // Crear tipo de data que sea struc Matrix llamado Matrix

Matrix *make_matrix(int n_rows, int n_cols) // Funcion para hacer matriz
{
    struct Matrix *pmatrix = malloc(sizeof(struct Matrix));
    pmatrix->rows = n_rows;
    pmatrix->cols = n_cols;
    pmatrix->data = malloc(sizeof(double) * n_rows * n_cols);
    return pmatrix;
}

int main (){
	
	int m = 2;
	int n = 3;

	int * pointer;
	int var =3;

	pointer = &var;

	Matrix * A = make_matrix (m,n);

	A->data[0] = 1;


	/*
	printf("%x",pointer);
	printf("\n");
	printf("%d",*pointer);
	*/
	
}



