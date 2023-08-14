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
void delete_node(Llist *, int);
Node *find_location(Llist *, int);
int is_full(Llist *);
int is_empty(Llist *);
void print_Llist(Llist *);

int main(void) {
  Llist li = create_llist();
  add_node(&li, 1, 1);
  print_Llist(&li);

  add_node(&li, 2, 1);
  print_Llist(&li);

  add_node(&li, 3, li.size+1);

  print_Llist(&li);
  add_node(&li, 1, li.size+1);
  add_node(&li, 2, li.size+1);
  add_node(&li, 6, 10);
  print_Llist(&li);
  delete_node(&li, 10);
  print_Llist(&li);
  delete_node(&li, 10);
  print_Llist(&li);
  delete_node(&li, 10);
  print_Llist(&li);
  delete_node(&li, 10);
  print_Llist(&li);
  delete_node(&li, 10);
  print_Llist(&li);
  delete_node(&li, 10);
  print_Llist(&li);

  return 1;
}

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
  else if(location<0){
    location = 0;
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
void delete_node(Llist *li, int location) {

  if (location > li->size) {
    location = li->size;
  } 
  else if(location<0){
    location = 0;
  }

  if (is_empty(li)) {
    printf("This linked list is already empty.");
  } else {
    Node *remove_node;
    if (location == 0) {
      remove_node = li->head;
      li->head = li->head->next;
      free(remove_node);
    } else {
      Node *node = find_location(li, location + 1);
      remove_node = node;
      node = node->next;
    }
    free(remove_node);
  }
  li->size--;
}
int is_full(Llist *li) { return 0; }
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

}