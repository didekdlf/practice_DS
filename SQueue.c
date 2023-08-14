#include <stdlib.h>
#include <stdio.h>

typedef struct SeQueue{
    int front;
    int rear;
    int size;
    int* q;
}SQu;

//ADT
SQu CreateSQ(int);
void AddSQ(SQu*,int);
int IsFullSQ(SQu*);

int IsEmptySQ(SQu*);
void DeleteSQ(SQu*);

void printQ(SQu);


void main(){
    int i=0;
    for(i=0;i<=10;i++){
        printf("%d",i);
    }
    printf("\n%d\n\n\n",i);
    SQu sq=CreateSQ(10);
    AddSQ(&sq,1);
    AddSQ(&sq,2);
    AddSQ(&sq,3);
    AddSQ(&sq,4);
    AddSQ(&sq,5);
    AddSQ(&sq,6);
    AddSQ(&sq,7);
    AddSQ(&sq,6);
    AddSQ(&sq,8);
    AddSQ(&sq,9);
    AddSQ(&sq,10);
    AddSQ(&sq,11);
    printQ(sq);
    for(int i=1;i<=sq.size;i++){
        DeleteSQ(&sq);
        //printf("%d\n",sq.rear);
    }
    printQ(sq);
    AddSQ(&sq,8);
    AddSQ(&sq,9);
    printQ(sq);
    for(int i=1;i<=sq.size;i++){
        DeleteSQ(&sq);
        //printf("%d\n",sq.rear);
    }
    printQ(sq);
}
void printQ(SQu sq){
    printf("\nfront : %d\n",sq.front);
    printf("rear : %d\n", sq.rear);
    for(int i=sq.front;i<sq.rear;i++){
        printf(" %d ",sq.q[i]);
    }
    printf("\n");
}
SQu CreateSQ(int size){
    SQu sq;
    sq.front=0;
    sq.rear=0;
    sq.size=size;
    sq.q=(int*)malloc(size*sizeof(int));
    return sq;
}
void AddSQ(SQu* sq, int item){
    if(IsFullSQ(sq)){
        printf("SQ is full\n");
    }
    else{
        if(sq->rear==sq->size){
            printf("array shift");//array shift
            int i;
            for(i=sq->front;i<=sq->rear;i++){
                sq->q[i-sq->front]=sq->q[i];
            }
            sq->rear=sq->rear-sq->front;
            sq->front=0;
        }
        sq->q[sq->rear]=item;
        sq->rear++;
        //printf("%3d",sq->rear);
    }
}
void DeleteSQ(SQu* sq){
    if(IsEmptySQ(sq)){
        printf("delete impossible\n");
    }
    else{
        printf("%d delete\n",sq->q[sq->front]);
        (sq->front)++;
    }
}
int IsFullSQ(SQu* sq){
    if((sq->rear-sq->front)==sq->size){
        return 1;
    }
    else{
        return 0;
    }
}
int IsEmptySQ(SQu* sq){
    if(sq->rear==sq->front){
        return 1;
    }
    else{
        return 0;
    }
}


typedef struct CirQueue{
    int front;
    int rear;
    int size;
    int* q;
}CQu;

