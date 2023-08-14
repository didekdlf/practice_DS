#include <stdlib.h>
#include <stdio.h>

typedef struct CirQueue{
    int front;
    int rear;
    int size;
    int state;//1 내용물이 있다. 0
    int* q;
}CQu;

CQu CreateCQ(int);
void AddCQ(CQu*,int);
int IsEmptyCQ(CQu*);
void DeleteCQ(CQu*);
int IsFullCQ(CQu*);
void printQ(CQu);
void queueFull(CQu);
void copy(CQu,CQu*,int);


void main(){
    CQu cq=CreateCQ(10);
    AddCQ(&cq,1);
    AddCQ(&cq,2);
    AddCQ(&cq,3);
    AddCQ(&cq,4);
    printQ(cq);
    AddCQ(&cq,5);
    AddCQ(&cq,6);
    AddCQ(&cq,7);
    AddCQ(&cq,6);
    AddCQ(&cq,8);
    AddCQ(&cq,9);
    AddCQ(&cq,10);
    AddCQ(&cq,11);
    printQ(cq);
    for(int i=1;i<=cq.size;i++){
        DeleteCQ(&cq);
        //printf("%d\n",sq.rear);
    }
    printQ(cq);
    AddCQ(&cq,8);
    AddCQ(&cq,9);
    printQ(cq);
    for(int i=1;i<=cq.size;i++){
        DeleteCQ(&cq);
        //printf("%d\n",sq.rear);
    }
    printQ(cq);
}

void queueFull(CQu cq){
    int start=(cq.front+1)%cq.size;
    //double
    CQu newq=CreateCQ(2*cq.size+1);
    //copy
    if(start>cq.rear){
        copy(cq, &newq, start);
    }
    else{
        copy(cq, &newq, start);
    }

}

void copy(CQu cq, CQu* newq , int start){
    
}


void printQ(CQu cq){
    printf("\nfront : %d\n",cq.front);
    printf("rear : %d\n", cq.rear);
    printf("state : %d\n", cq.state);
    if(!(IsEmptyCQ(&cq))){
        
        for(int i=cq.front+1;i<=cq.size;i++){
            printf("%d ",cq.q[i]);
            if(i%cq.size==cq.rear){
                break;
            }
        }
 
        printf("\n");
    }

}

CQu CreateCQ(int size){
    CQu cq;
    cq.front = 0;
    cq.rear = 0;
    cq.size = size;
    cq.state = 0;
    cq.q = (int*)malloc(cq.size*sizeof(int));
    return cq;
}
void AddCQ(CQu* cq, int item){
    if(!(IsFullCQ(cq))){
        cq->rear++;
        cq->q[cq->rear] = item;
        cq->rear = (cq->rear)%cq->size;
        //printf("%d\n",cq->rear);
        cq->state = 1;
    }
}

void DeleteCQ(CQu* cq){
    if(!(IsEmptyCQ(cq))){
        printf("%d delete\n",cq->q[++cq->front]);
        cq->front=(cq->front)%cq->size;
        if(cq->front==cq->rear){
            cq->state=0;
        }
    }
}
int IsFullCQ(CQu* cq){
    if((cq->state==1) && (cq->front==cq->rear)){
        printf("this stack is full\n");
        return 1;
    }
    else{
        return 0;
    }

}
int IsEmptyCQ(CQu* cq){
    if((cq->state==0) && (cq->front==cq->rear)){
        printf("this stack is empthy\n");
        return 1;
    }
    else{
        return 0;
    }
}
