#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int top;
    int* stack;
    int max;
}STACK;

STACK StackCreate(int);
int IsFull(STACK*, int);
void push(STACK*,int);
int IsEmpty(STACK*);
void pop(STACK*);

void main(){
    STACK s=StackCreate(5);
    push(&s,5);
    push(&s,4);
    push(&s,4);
    push(&s,3);
    push(&s,5);
    pop(&s);
    pop(&s);
    pop(&s);
    pop(&s);
    pop(&s);
    pop(&s);
}



STACK StackCreate(int stacksize){
    STACK s;
    s.stack=(int*)malloc(stacksize*sizeof(int));
    s.top=-1;
    s.max=stacksize;
    return s;
}
int IsFull(STACK *s , int stacksize){
    if(s->top==stacksize){
        return 1;
    }
    else{
        return 0;
    }
}
void push(STACK *s, int item){
    if(IsFull(s,s->max)){
        printf("stackfull");
    }
    else{
        s->stack[++(s->top)]=item;
    }
}
int IsEmpty(STACK*s){
    if (s->top==-1){
        return 1;
    }
    else{
        return 0;
    }
}
void pop(STACK *s){
    if(IsEmpty(s)){
        printf("stack empty");
    }
    else{
        int item =s->stack[s->top];
        s->stack[s->top+1]=0;
        s->top--;
        printf("item : %d\n",item);
    }
}
