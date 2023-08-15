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
  char inf[] = {"a*(b+c)*d"};
  STACK result=StackCreate(10);
  STACK s = StackCreate(10);
  char oper;
  for (int i = 0; i < 11; i++) {
    switch (Isoper(inf[i])) {
    case 0:
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
    return '\0';
  }


/*
#include <stdio.h>
#include <stdlib.h>

 
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
void make_postfix(b_tree *);
void make_postfix_stack(Lstack *, char *);
int Isoper(char);
Lstack make_post(char*);
int calculator(Lstack);
int operand(int,int,char);

int main(void) {
  char inf[] = {"1*(2+3)*4"};
  Lstack exp=make_post(inf);
  printf("%d",calculator(exp));
  return 1;
}

int calculator(Lstack ls){
    Node *node;
    Lstack num=create_Lstack();
    int result;
    node = ls.body.head;
    if (!is_empty(&ls.body)) {
    for (int i = 1; i <= ls.body.size; i++) {
      if(Isoper(node->data)){
        char c;
        push(&num,_itoa_s(operand(pop(&num),pop(&num),node->data), &c,10,10));
        }
      else{
        push(&num,node->data);
      }
      node = node->next;
    }
    return 1;
    }
}
int operand(int a,int b,char c){
    switch(Isoper(c)){
        case 1 :
            return a+b;
        case 2 :
            return a*b;
        case 3 :
            return a/b;
        default :
            return 0;
    }

}

Lstack make_post(char* inf) {
  Lstack result = create_Lstack();
  Lstack s = create_Lstack();
  char oper;
  for (int i = 0; i < 11; i++) {
    switch (Isoper(inf[i])) {
    case 0:
      push(&result, inf[i]);
      break;
    case 4:
      break;
    case 5:
      while (!is_empty(&s.body)) {
        push(&result, pop(&s));
      }
      break;

    default:
      push(&s, inf[i]);
      break;
    }
  }
  return result;
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
  while (node->left_child != NULL) {
    node = node->left_child;
    tree_traversal(node);
  }
  while (node->right_child != NULL) {
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
*/