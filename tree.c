#include <stdio.h>
#include <stdlib.h>

 void itoa(int n, char s[]){
     int i, sign;
 
     if ((sign = n) < 0)  /* record sign */
         n = -n;          /* make n positive */
     i = 0;
     do {       /* generate digits in reverse order */
         s[i++] = n % 10 + '0';   /* get next digit */
     } while ((n /= 10) > 0);     /* delete it */
     if (sign < 0)
         s[i++] = '-';
     s[i] = '\0';
     reverse(s);
 }

 
typedef struct Node {
  char data;
  struct Node *next;
} Node;
Node create_node(void);

typedef struct Linked_list {
  int size;
  struct Node *head;
} Llist;

Llist create_llist(void);
void add_node(Llist *, char, int);
char delete_node(Llist *, int);
Node *find_location(Llist *, int);
int is_empty(Llist *);
void print_Llist(Llist *);

typedef struct Linked_Stack {
  Llist body;
} Lstack;
Lstack create_Lstack(void);
void push(Lstack *, char);
char pop(Lstack *);

typedef struct Tree_Node {
  char data;
  struct Tree_Node *left_child;
  struct Tree_Node *right_child;
} t_Node;
t_Node *create_Node(void);

typedef struct Edge {
  int *child;
} Edge;

typedef struct Binary_Tree {
  t_Node *root;
  int level;
} b_tree;

b_tree create_tree(void);
void tree_traversal(t_Node *);


int main(void) {

  return 1;
}



t_Node *create_Node(void) {
  t_Node *node = (t_Node *)malloc(sizeof(t_Node));
  node->data = 0;
  node->left_child = NULL;
  node->right_child = NULL;
  return node;
}

b_tree create_tree(void) {
  b_tree new_tree;
  new_tree.level = 0;
  new_tree.root = create_Node();
  return new_tree;
}
void tree_traversal(t_Node *root) {
  // LVR
  t_Node *node = root;
  // moving left
  if (node->left_child != NULL) {
    node = node->left_child;
    tree_traversal(node);
  }
  else if(node->right_child != NULL) {
    node = node->right_child;
    tree_traversal(node);
  }
  printf("%d", node->data);
  
}
// Lincked_list 연산
Lstack create_Lstack(void) {
  Lstack ls;
  ls.body = create_llist();
  return ls;
}

void push(Lstack *ls, char data) { add_node(&ls->body, data, 0); }

char pop(Lstack *ls) { return delete_node(&ls->body, 0); }

//이 밑은 그냥 Linked_List 사용해서 만든거랑 같음.
Llist create_llist(void) {
  Llist li;
  li.size = -1;
  return li;
}
void add_node(Llist *li, char data, int location) { // location 0~

  if (location > li->size) {
    location = li->size + 1;
  }

  if (is_empty(li)) {
    li->head = (Node *)malloc(sizeof(Node));
    li->head->next = NULL;
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
char delete_node(Llist *li, int location) {
  char item;
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
      printf("%c ", node->data);
      node = node->next;
    }
    printf("%c ", node->data);
    printf("\n size : %d\n", li->size);
  }
}