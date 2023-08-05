#include <stdlib.h>
#include <stdio.h>


typedef struct SparseMatrix{
    int row, col;
    int** room;
}SM;

SM Create(int,int);
SM Transpose(SM);
SM Add(SM,SM);
SM Multiply(SM,SM);
void Remove(SM);
void printM(SM);