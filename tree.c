#include <stdio.h>
#include <stdlib.h>
//계산은 정확히 하나 괄호 이외의 연산자 간의 우선 순위가 없다...ex)
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
t_Node *create_t_Node(void);

typedef struct Binary_Tree {
  t_Node *root;
  int level;
} b_tree;

b_tree *create_tree(void);
void add_ancestor(b_tree *, char, int);
void add_child(b_tree *, char);
void add_tree(b_tree *, b_tree *);
void tree_traversal(t_Node *);
int make_postfix(b_tree *, Lstack *);
int Isoper(char);
int calculator(t_Node *);
int operand(int, char, char, t_Node *);
int main(void) {
  char input[] = {"1-2*5+3"};
  Lstack express = create_Lstack();
  for (int i = 8; i >= 0; i--) {
    push(&express, input[i]);
  }
  print_Llist(&express.body);
  b_tree *tree = create_tree();
  make_postfix(tree, &express);
  tree_traversal(tree->root);
  printf("=%d", calculator(tree->root));
  return 1;
}

int calculator(t_Node *root) {
  int result = 0;
  int next = 0;
  t_Node *node = root;
  if (node->left_child != NULL) {
    result = calculator(node->left_child);
    if (Isoper(node->right_child->data) != 0) {
      next = calculator(node->right_child);
    } else {
      next = node->right_child->data - '0';
    }
    switch (Isoper(node->data)) {
    case 1:
      result = result + next;
      break;
    case 2:
      result = result - next;
      break;
    case 3:
      result = result * next;
      break;
    case 4:
      result = result / next;
    default:
      break;
    }
    return result;
  } else {
    return node->data - '0';
  }
}

int Isoper(char inp) {
  int temp = inp - '0';
  if (temp == '+' - '0') {
    return 1; // add
  } else if (temp == '-' - '0') {
    return 2;
  } else if (temp == '*' - '0') {
    return 3; // multiple
  } else if (temp == '/' - '0') {
    return 4;
  } else if (temp == '(' - '0') {
    return 5;
  } else if ((temp == ')' - '0') || (temp == '\0' - '0')) {
    return 6;
  }
  return 0;
}
int make_postfix(b_tree *tree, Lstack *express) {
  char c;
  int isoper;
  int size = express->body.size;
  for (int i = 0; i <= size; i++) {
    c = pop(express);
    isoper = Isoper(c);
    if (isoper == 0) {
      add_child(tree, c);
    } else if (isoper == 5) {
      b_tree *new_tree = create_tree();
      make_postfix(new_tree, express);
      add_tree(tree, new_tree);
    } else if (isoper == 6) {
      return 1;
    } else {
      add_ancestor(tree, c, 0);
    }
  }
  return 0;
}

void add_ancestor(b_tree *tree, char data,
                  int direc) { // direc : 0 -> left, else -> right
  t_Node *node = create_t_Node();

  if (tree->root->data != '\0') {
    if (direc == 0) {
      node->left_child = tree->root;
      tree->root = node;
    } else {
      node->right_child = tree->root;
      tree->root = node;
    }
  }
  tree->root->data = data;
}
void add_child(b_tree *tree, char data) {
  if (tree->root->left_child == NULL) {
    tree->root->left_child = create_t_Node();
    tree->root->left_child->data = data;
  } else if (tree->root->right_child == NULL) {
    tree->root->right_child = create_t_Node();
    tree->root->right_child->data = data;
  }
}
void add_tree(b_tree *tree, b_tree *new_tree) {
  if (tree->root->left_child == NULL) {
    tree->root->left_child = new_tree->root;
  } else if (tree->root->right_child == NULL) {
    tree->root->right_child = new_tree->root;
  }
}
t_Node *create_t_Node(void) {
  t_Node *node = (t_Node *)malloc(sizeof(t_Node));
  node->data = '\0';
  node->left_child = NULL;
  node->right_child = NULL;
  return node;
}

b_tree *create_tree(void) {
  b_tree *new_tree = (b_tree *)malloc(sizeof(b_tree));
  new_tree->level = 0;
  new_tree->root = create_t_Node();
  return new_tree;
}
void tree_traversal(t_Node *node) {
  // LVR
  // moving leftg
  if (node != NULL) {
    tree_traversal(node->left_child);
    printf("%c", node->data);
    tree_traversal(node->right_child);
  }
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