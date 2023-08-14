#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int top;
  char *stack;
  int max;
} STACK;

STACK StackCreate(int);
int IsFull(STACK *, int);
void push(STACK *, char);
int IsEmpty(STACK *);
char pop(STACK *);

void make_post(void);
int Isoper(char);

int main() {
  char inf[] = {"a*(b+c)*d"};
  make_post();
  return 1;
}

void make_post(void){
  char inf[] = {" a*(b+c)*d"};
  STACK result=StackCreate(10);
  STACK s = StackCreate(5);
  char oper;
  for (int i = 0; i < 11; i++) {
    switch (Isoper(inf[i])) {
    case 0:
      printf("%c",inf[i]);
      push(&result,inf[i]);
      break;

    case 5:
      while (!IsEmpty(&s)) {
        push(&result,pop(&s));
      }
      break;
    case 4:
      break;
    default:
      push(&s, inf[i]);
      break;
    }

  }
  for(int i=0;i<=result.top;i++){
    printf("%c",result.stack[i]);
  }
}




  int Isoper(char inp) {
    int temp = inp - '0';
    if (temp == '+' - '0') {
      return 1; // add
    } else if (temp == '*' - '0') {
      return 2; // multiple
    } else if (temp == '/' - '0') {
      return 3;
    } else if (temp == '(' - '0') {
      return 4;
    } else if ((temp == ')' - '0') || (temp == '\0' - '0')) {
      return 5;
    }
    return 0;
  }

  STACK StackCreate(int stacksize) {
    STACK s;
    s.stack = (char *)malloc(stacksize * sizeof(char));
    s.top = -1;
    s.max = stacksize;
    return s;
  }
  int IsFull(STACK * s, int stacksize) {
    if (s->top == stacksize) {
      return 1;
    } else {
      return 0;
    }
  }
  void push(STACK * s, char item) {
    if (IsFull(s, s->max)) {
      printf("stackfull");
    } else {
      s->stack[++(s->top)] = item;
    }
  }
  int IsEmpty(STACK * s) {
    if (s->top == -1) {
      return 1;
    } else {
      return 0;
    }
  }
  char pop(STACK * s) {
    if (IsEmpty(s)) {
      printf("stack empty");
    } else {
      char item = s->stack[s->top];
      s->top--;
      return item;
    }
  }
