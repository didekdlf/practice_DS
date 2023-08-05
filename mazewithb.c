#include<stdlib.h>
#include<stdio.h>
//#include <random>
#define MAZE_SIZE 50

//출구가 있는 경우
int maze_border_x[12][15]={{0,1,0,0,0,1,1,0,0,0,1,1,1,1,1},{1,0,0,0,1,1,0,1,1,1,0,0,1,1,1},{0,1,1,0,0,0,0,1,1,1,1,0,0,1,1},{1,1,0,1,1,1,1,0,1,1,0,1,1,0,0},{1,1,0,1,0,0,1,0,1,1,1,1,1,1,1},{0,0,1,1,0,1,1,1,0,1,0,0,1,0,1},{0,0,1,1,0,1,1,1,0,1,0,0,1,0,1},{0,1,1,1,1,0,0,1,1,1,1,1,1,1,1},{0,0,1,1,0,1,1,0,1,1,1,1,1,0,1},{1,1,0,0,0,1,1,0,1,1,0,0,0,0,0},{0,0,1,1,1,1,1,0,0,0,1,1,1,1,0},{0,1,0,0,1,1,1,1,1,0,1,1,1,1,0}};

//출구가 없는 경우
//int maze_border_x[12][15]={{0,1,0,0,0,1,1,0,0,0,1,1,1,1,1},{1,0,0,0,1,1,0,1,1,1,0,0,1,1,1},{0,1,1,0,0,0,0,1,1,1,1,0,0,1,1},{1,1,0,1,1,1,1,0,1,1,0,1,1,0,0},{1,1,0,1,0,0,1,0,1,1,1,1,1,1,1},{0,0,1,1,0,1,1,1,0,1,0,0,1,0,1},{0,0,1,1,0,1,1,1,0,1,0,0,1,0,1},{0,1,1,1,1,0,0,1,1,1,1,1,1,1,1},{0,0,1,1,0,1,1,0,1,1,1,1,1,0,1},{1,1,0,0,0,1,1,0,1,1,0,0,0,0,0},{0,0,1,1,1,1,1,0,0,0,1,1,1,1,0},{0,1,0,0,1,1,1,1,1,0,1,1,1,1,1}};

int maze[14][17];
void Border(void){//미로 외부에 1로 벽 세우기
    int i;
    for(i=0;i<17;i++){
        maze[0][i]=1;
        maze[13][i]=1;
        
    }
    for(i=0;i<14;i++){
        maze[i][0]=1;
        maze[i][16]=1;
        
    }
    
    for(i=0;i<12;i++){
        for(int j=0;j<15;j++){
            maze[i+1][j+1]=maze_border_x[i][j];
        }
    }
}


typedef struct{
    short int row;
    short int col;
    short int dir;
}element;

element CreateEle(int,int,int);
typedef struct{
    int top;
    element* ele;
    int max;
}STACK;

STACK StackCreate(int);
int IsFull(STACK*, int);
void push(STACK*,element);
int IsEmpty(STACK*);
element pop(STACK*);
element top(STACK);



typedef struct{
    STACK node;//지금껏 지나온 경로
    int** mark[14][17];
}PATH;
void CreatePath(PATH*);

void printPath(PATH*);
void printMark(PATH*);


void FindPath(PATH*);
int Out(int,int);//움직일 곳이 미로 외부일 경우 1 반환
int move(PATH*,element);//더이상 움직일 곳이 없을 경우 0반환


void main(){
    PATH path;
    Border();
    for(int i=0;i<14;i++){
        for(int j=0;j<17;j++){
            printf("%2d", maze[i][j]);
        }
        printf("\n");
    }
    CreatePath(&path);
    FindPath( &path);
    printf("\n\n");
    printPath(&path);
    printf("\n\n");

}
element CreateEle(int row,int col,int dir){
    element ele;
    ele.row=row;
    ele.col=col;
    ele.dir=dir;
    return ele;
}


void FindPath(PATH* p){

    //출발점 지정
    element start=CreateEle(1,1,0);
    element end=CreateEle(12,15,0);
    push(&p->node,start);
    p->mark[1][1]=1;
    int i=0;
    while(!((top(p->node).row==end.row)&&(top(p->node).col==end.col))){//도착점 도달까지 move
        if(!move(p,top(p->node))){
            //백 트래킹
            printf("back");
            pop(&p->node);
            //printMark(p);
        }
        
        
        if((top(p->node).row==start.row)&&(top(p->node).col==start.col)){
            printf("NO WAY");
            break;
        }
        i++;
    }
    printf("find path");
    //
}
int move(PATH* p ,element ele){
    int cnt =0;//움직이지 못한 횟수
    int ca[8][2]={{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}}; //move 방향
    int x,y;

    for(int i=ele.dir;i<8;i++){//이전에 확인하지 않았던 방향만 확인
        x=ca[i][0];
        y=ca[i][1];
        if((maze[ele.row+x][ele.col+y]==0)&&(p->mark[ele.row+x][ele.col+y]==0)){//move 조건
            element next=CreateEle(ele.row+x,ele.col+y,0);
            ele.dir=i+1;//지금까지 확인한 방향+1
            pop(&p->node);//현재 node의 dir 바꾸기
            push(&p->node,ele);
            push(&p->node,next);//다음 노드 추가
            p->mark[next.row][next.col]=1;//mark
            return 1;
        }
    }
    return 0;
}


void CreatePath(PATH* p){// 그냥 PATH 초기화 함수
    p->node=StackCreate(15*12);//가능한 길이가 긴 경로의 길이는 행렬 요소 수와 같으므로 15*12으로 걍 설정
    for(int i=0;i<14;i++){
        for(int j=0;j<17;j++){
            p->mark[i][j]=0;
            
        }
    }
}


void printPath(PATH* p){//찾은 길 표시
    element e;
    while(!IsEmpty(&p->node)){
        e=pop(&p->node);
        maze[e.row][e.col]=5;
         printf("(%d, %d)<-", e.row,e.col);
    }
    printf("\n");
    for(int i=0;i<14;i++){
        for(int j=0;j<17;j++){
                printf(" %2d",maze[i][j]);//printf("%2d", p->search[i][j]);
            }
            printf("\n");
    }
}

void printMark(PATH* p){
        for(int i=0;i<14;i++){
        for(int j=0;j<17;j++){
            printf("%2d",p->mark[i][j]);
            
        }
        printf("\n");
    }
   
}



STACK StackCreate(int stacksize){
    STACK s;
    s.ele=(element*)malloc(stacksize*sizeof(element));
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
void push(STACK *s, element item){
    if(IsFull(s,s->max)){
        printf("stackfull");
    }
    else{
        s->ele[++(s->top)]=item;
    }
}
int IsEmpty(STACK* s){
    if (s->top==-1){
        return 1;
    }
    else{
        return 0;
    }
}
element pop(STACK *s){
    if(IsEmpty(s)){
        printf("stack empty");
    }
    else{
        element item =s->ele[s->top];
        
        s->top--;
        return item;
    }
}
element top(STACK s){
    if(IsEmpty(&s)){
        printf("stack empty");
    }
    else{
        return s.ele[s.top];
    }
}
