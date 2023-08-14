#include <stdio.h>
#include <stdlib.h>

//#include <random>
#define MAZE_SIZE 50

//출구가 있는 경우
int maze[12][15] = {{0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
                    {1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1},
                    {0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1},
                    {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0},
                    {1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
                    {0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1},
                    {0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1},
                    {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
                    {0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
                    {1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
                    {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0},
                    {0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0}};

//출구가 없는 경우
// int
/*
maze[12][15] = {{0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1},
                {1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1},
                {0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1},
                {1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 0},
                {1, 1, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
                {0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1},
                {0, 0, 1, 1, 0, 1, 1, 1, 0, 1, 0, 0, 1, 0, 1},
                {0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1},
                {0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1},
                {1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0, 0, 0},
                {0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0},
                {0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1}};
                */

typedef struct {
  int top;
  int *stack;
  int max;
} STACK;

STACK StackCreate(int);
int IsFull(STACK *, int);
void push(STACK *, int);
int IsEmpty(STACK *);
int pop(STACK *);
int top(STACK);

typedef struct {
  STACK node[2];      //지금껏 지나온 경로
  int search[12][15]; //탐색한 지점
} PATH;
void CreatePath(PATH *);
void prints(PATH *);
void printPath(PATH *);

void FindPath(PATH *);
int Out(int, int);          //움직일 곳이 미로 외부일 경우 1 반환
int move(PATH *, int, int); //더이상 움직일 곳이 없을 경우 0반환

int main(void) {
  PATH path;
  CreatePath(&path);
  FindPath(&path);
  printPath(&path);

  return 0;
}

void FindPath(PATH *p) {

  //출발점 지정
  push(&p->node[0], 0);
  push(&p->node[1], 0);
  p->search[0][0] = 1;

  printf("( %d, %d )\n", top(p->node[0]), top(p->node[1]));
  while (
      !((top(p->node[0]) == 11) && (top(p->node[1]) == 14))) { //도착점 도달까지
    prints(p);
    if (!move(p, top(p->node[0]), top(p->node[1]))) {
      //백 트래킹
      pop(&p->node[0]);
      pop(&p->node[1]);
    }
    printf("( %d, %d )\n", top(p->node[0]), top(p->node[1])); //현재 위치
    if ((top(p->node[0]) == 0) && (top(p->node[1]) == 0)) {
      printf("NO WAY");
      break;
    }
  }
}
int move(PATH *p, int x, int y) {
  int cnt = 0; //움직이지 못한 횟수
  for (int i = -1; i < 2; i++) {
    for (int j = -1; j < 2; j++) {

      if ((i == 0) && (j == 0)) { //이 경우 현재 위치이므로 넘긴다.
        continue;
      } else if (!Out(x + i, y + j)) {
        if ((maze[x + i][y + j] == 0) &&
            (p->search[x + i][y + j] == 0)) { //탐색하지 않은 길일 경우 move
          push(&p->node[0], x + i);           // move
          push(&p->node[1], y + j);
          p->search[x + i][y + j] = 1; //탐색완료
          return 1; // move했으므로 함수를 종료한다.

        } else {
          p->search[x + i][y + j] = 1; //탐색완료
        }
      }
      cnt++; // move하지 못했으므로 cnt++
    }
  }
  if (cnt == 8) { //주변이 모두 탐색된 경우
    return 0;     // move하지 못했으므로 back tracking을 위해 0 반환
  }
  return 1;
}

int Out(int x, int y) {
  if ((x < 0) || (x >= 12) || (y < 0) || (y >= 15)) { //외부일 조건
    return 1;
  }
  return 0;
}

void CreatePath(PATH *p) { // 그냥 PATH 초기화 함수
  p->node[0] = StackCreate(15 * 12); //가능한 길이가 긴 경로의 길이는 행렬 요소
                                     //수와 같으므로 15*12으로 걍 설정
  p->node[1] = StackCreate(15 * 12);
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 15; j++) {
      p->search[i][j] = 0; //탐색 행렬 초기화
    }
  }
}
void printPath(PATH *p) { //찾은 길 표시
  while (!IsEmpty(&p->node[0])) {
    maze[pop(&p->node[0])][pop(&p->node[1])] = 5;
  }
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 15; j++) {
      printf(" %d", maze[i][j]); // printf("%2d", p->search[i][j]);
    }
    printf("\n");
  }
}
void prints(PATH *p) { //탐색 행렬 print
  for (int i = 0; i < 12; i++) {
    for (int j = 0; j < 15; j++) {
      printf(" %d", p->search[i][j]); // printf("%2d", p->search[i][j]);
    }
    printf("\n");
  }
}

STACK StackCreate(int stacksize) {
  STACK s;
  s.stack = (int *)malloc(stacksize * sizeof(int));
  s.top = -1;
  s.max = stacksize;
  return s;
}
int IsFull(STACK *s, int stacksize) {
  if (s->top == stacksize) {
    return 1;
  } else {
    return 0;
  }
}
void push(STACK *s, int item) {
  if (IsFull(s, s->max)) {
    printf("stackfull");
  } else {
    s->stack[++(s->top)] = item;
  }
}
int IsEmpty(STACK *s) {
  if (s->top == -1) {
    return 1;
  } else {
    return 0;
  }
}
int pop(STACK *s) {
  if (IsEmpty(s)) {
    printf("stack empty");
    return -1;
  } else {
    int item = s->stack[s->top];
    s->stack[s->top + 1] = 0;
    s->top--;
    return item;
  }
}
int top(STACK s) {
  if (IsEmpty(&s)) {
    printf("stack empty");
    return -1;
  } else {
    return s.stack[s.top];
  }
}
