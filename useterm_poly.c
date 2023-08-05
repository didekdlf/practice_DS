#include<stdlib.h>
#include<stdio.h>

#define MAX_DEGREE 101
#define MAX_TERMS 100
#define MALLOC(x,size) if (!(x)=malloc(size)) { fprintf(stderr,"Insufficient memory"); exit(EXIT_FAILURE); }
#define COMPARE(x,y) (((x)<(y)) ? -1 : ((x) ==(y)) ? 0 : 1))
typedef struct {
    int expon;
    float coef;
}term;

term terms[MAX_TERMS];
int avail = 0;

void Zero();
int IsZero(int);
int Coef(int);
int LeadExp(int);
void Attach(int,int);
void Remove(int,int);
void SingleMult(int,int,int);
void Add(int,int);
void Mult(int,int);
void printpoly(int);



void Zero(){
    
}
int IsZero(int){

}
int Coef(int){

}
int LeadExp(int){

}
void Attach(int,int){

}
void Remove(int,int){

}
void SingleMult(int,int,int){

}
void Add(int,int){

}
void Mult(int,int){

}
void printpoly(int){

}