#define _CRT_SECURE_NO_WARNINGS 
#include<stdlib.h>
#include<stdio.h>

typedef struct list {
    int n;
    int *body;
}list;
void makelist(int);



void main(){
    list s;
    int n=10;
    printf("list length : ");
    scanf("%d",&n);
    s.body = (int*)malloc(n*sizeof(int));
    for (int i=0; i<n;i++){
        s.body[i]=i;
    }
    for (int i=0;i<n;i++){
        printf("%d",s.body[i]);
    }
    
}

void makelist(int n){
    
}