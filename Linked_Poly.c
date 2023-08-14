#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
  int expon;
  int coef;
  struct Node *next;
} Node;
Node create_node(void);

typedef struct Linked_Poly {
  int size;
  struct Node *head;
} Llist;

Llist create_llist(void);
void add_node(Llist *, int, int, int);
void delete_node(Llist *, int);
Node *find_location(Llist *, int);
int is_full(Llist *);
int is_empty(Llist *);
void print_Llist(Llist *);

int is_expon(Llist *, int);
int find_expon(Llist *, int);
int attatch(Node *, int);
int single_multiply(Llist *, Node *);
void add_single_Poly(Llist *, int, int);
void delete_Poly(Llist *, int);

int main(void) {

  Llist poly_a; // 3x^14 + 2 x^8 +1
  Llist poly_b; // 8 x^14 -3 x^10 + 10 x^6
  int a[3][2] = {{3, 14}, {2, 8}, {1, 0}};
  int b[3][2] = {{8, 14}, {-3, 10}, {10, 6}};
  poly_a = create_llist();
  poly_b = create_llist();
  for (int i = 0; i < 3; i++) {
    add_single_Poly(&poly_a, a[i][0], a[i][1]);
    add_single_Poly(&poly_b, b[i][0], b[i][1]);
    
  }
  print_Llist(&poly_a);
  print_Llist(&poly_b);
  return 1;
}


int attatch(Node *n, int coef) {
  n->coef += coef;
  if(n->coef ==0){
    return 0 ;
  }
  return 1;
}
void add_single_Poly(Llist *li, int coef, int expon) { // location 0~
  if (is_expon(li, expon)) {
    int location = find_expon(li, expon) + 1;
    if(attatch(find_location(li, location), coef)){
      delete_node(li,location);
    } // singleadd
    
  } else {
    //추가
    add_node(li, coef, expon, find_expon(li, expon));
  }
}


void delete_Poly(Llist *li, int expon) {
  if (is_expon(li, expon)) {
    delete_node(li, find_expon(li, find_expon(li, expon)));
  }
}
int is_expon(Llist *li, int expon) {
  printf("4");
  Node *node;
  node = li->head;
  for (int i = 0; i <= li->size; i++) {
    printf("5");
    if (node->expon == expon) {
      printf("\nO\n");
      return 1;
    }
    node = node->next;
  }

  return 0;
}

int find_expon(Llist *li, int expon) {
  Node *node;
  int location = 0;
  node = li->head;
  for (int i = 0; i <= li->size; i++) {
    if (node->expon == expon) {
      return location;
    } else if (node->expon < expon) {

      return location - 1;
    }
    location++;
    node = node->next;
  }
  return li->size + 1;
}




// Linked_list 함수
Llist create_llist(void) {
  Llist li;
  li.size = -1;
  li.head = (Node *)malloc(sizeof(Node));
  li.head->next = NULL;
  return li;
}

void add_node(Llist *li, int coef, int expon, int location) { // location 0~

  if (location > li->size) {
    location = li->size + 1;
  } else if (location < 0) {
    location = 0;
  }

  if (is_empty(li)) {
    li->head->coef = coef;
    li->head->expon = expon;
  } else {
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (location == 0) {
      new_node->next = li->head;
      li->head = new_node;
      li->head->coef = coef;
      new_node->expon = expon;
    } else {
      Node *pre_node;
      new_node->coef = coef;
      new_node->expon = expon;
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
  } else if (location < 0) {
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
      printf("%d X^%d ", node->coef, node->expon);
      node = node->next;
    }
    printf("%d X^%d ", node->coef, node->expon);
    printf("\n size : %d\n", li->size);
  }
}