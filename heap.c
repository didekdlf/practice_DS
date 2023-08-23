#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 200
#include <math.h>
typedef struct heap {
  int *body;
  int level;
  int location_of_last_data;
} heap;

heap *create_heap(void);
void push_heap(heap *, int);
int pop_heap(heap *);

heap *create_heap(void) {
  heap *new_heap = (heap *)malloc(sizeof(heap));
  new_heap->level = -1;
  new_heap->body = (int *)malloc(MAX_HEAP_SIZE * sizeof(int));
  new_heap->location_of_last_data = 0;
  return new_heap;
}

void push_heap(heap *hp, int data) {
  hp->body[++hp->location_of_last_data] = data;
  //자리 찾기 위한 교환 시작
  int location_of_parent =
      hp->location_of_last_data / 2 -
      (int)(pow(2, hp->level)); // parent의 자리 = child 자리/2 - 2^이전 레벨

  while (hp->body[location_of_parent] > hp->body[hp->location_of_last_data]) {
    //교체
  }
}

int pop_heap(heap *hp) { return hp->body[hp->location_of_last_data--]; }

int main(void) { return 0; }