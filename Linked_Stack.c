#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;
Node create_node(void);

typedef struct Linked_list {
  int size;
  struct Node *head;
} Llist;

Llist create_llist(void);
void add_node(Llist *, int, int);
int delete_node(Llist *, int);
Node *find_location(Llist *, int);
int is_empty(Llist *);
void print_Llist(Llist *);

typedef struct Linked_Stack {
  Llist body;
} Lstack;
Lstack create_Lstack(void);
void push(Lstack *, int);
int pop(Lstack *);

int main(void) { return 1; }
Lstack create_Lstack(void) {
  Lstack ls;
  ls.body = create_llist();
  return ls;
}
void push(Lstack *ls, int data) { add_node(&ls->body, data, 0); }

int pop(Lstack *ls) { return delete_node(&ls->body, 0); }

//이 밑은 그냥 Linked_List 사용해서 만든거랑 같음.
Llist create_llist(void) {
  Llist li;
  li.size = -1;
  li.head = (Node *)malloc(sizeof(Node));
  li.head->next = NULL;
  return li;
}
void add_node(Llist *li, int data, int location) { // location 0~

  if (location > li->size) {
    location = li->size + 1;
  }

  if (is_empty(li)) {
    li->head->data = data;
  } else {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (location == 0) {
      new_node->next = li->head;
      li->head = new_node;
      li->head->data = data;
    } else {
      Node *pre_node;
      new_node->data = data;
      pre_node = find_location(li, location);
      new_node->next = pre_node->next;
      pre_node->next = new_node;
    }
  }

  li->size++;
}
int delete_node(Llist *li, int location) {
  int item = 0;
  if (location > li->size) {
    location = li->size;
  }

  if (is_empty(li)) {
    printf("This linked list is already empty.");
  } else {
    Node *remove_node;
    if (location == 0) {
      remove_node = li->head;
      li->head = li->head->next;
    } else {
      Node *node = find_location(li, location + 1);
      remove_node = node;
      node = node->next;
    }
    item = remove_node->data;
    free(remove_node);
    li->size--;
  }

  return item;
}

int is_empty(Llist *li) {
  if (li->size == -1) {
    return 1;
  } else {
    return 0;
  }
}

Node *find_location(Llist *li, int location) {
  Node *node;
  node = li->head;
  for (int i = 1; i < location; i++) {
    node = node->next;
  }
  return node; //찾는 위치 바로 앞 노드를 반환한다.
}

void print_Llist(Llist *li) {
  Node *node;
  node = li->head;
  if (!is_empty(li)) {
    for (int i = 1; i <= li->size; i++) {
      printf("%d ", node->data);
      node = node->next;
    }
    printf("%d ", node->data);
    printf("\n size : %d\n", li->size);
  }
  printf("THis list is empthy");
}