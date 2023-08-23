#include <stdio.h>
#include <stdlib.h>

typedef struct MAX_QUEUE_NODE {
  int data;
  struct MAX_QUEUE_NODE *left_child;
  struct MAX_QUEUE_NODE *right_child;
} Q_node;
Q_node *create_Q_node(void);
int compare(Q_node *, int);

typedef struct MAX_QUEUE { // use tree
  int level;
  Q_node *root;
} Q_tree;
Q_tree *create_Q_tree(void);
int push_tree(Q_tree *, int);
int pop_tree(Q_tree *);
int is_tree_empty(Q_tree *);

void add_ancestor(Q_node *, int);
int add_child(Q_node *, int);
Q_node *find_insert_node(Q_node *, int);
Q_node *delete (Q_node *);

void free_node(Q_node *node) {
  if (node != NULL) {
    free_node(node->left_child);
    free(node);
    free_node(node->right_child);
  }
}
void free_tree(Q_tree *tree) {
  free_node(tree->root);
  free(tree);
}
void tree_traversal(Q_node *node) {
  // LVR
  // moving leftg
  if (node != NULL) {
    tree_traversal(node->left_child);
    printf("%d", node->data);
    tree_traversal(node->right_child);
  }
}

int main(void) {
  Q_tree *tree = create_Q_tree();
  push_tree(tree, 13);
  push_tree(tree, 14);
  push_tree(tree, 15);
  /*
  push_tree(tree, 1);
  push_tree(tree, 2);
  push_tree(tree, 3);
  push_tree(tree, 4);
  push_tree(tree, 5);
  push_tree(tree, 6);
  push_tree(tree, 7);
  push_tree(tree, 8);
  push_tree(tree, 9);
  push_tree(tree, 10);
  push_tree(tree, 11);
  push_tree(tree, 12);
  push_tree(tree, 13);
  */
  tree_traversal(tree->root);
  pop_tree(tree);
  free_tree(tree);
  return 1;
}

void add_tree(Q_tree *tree, Q_tree *new_tree) {
  if (tree->root->left_child == NULL) {
    tree->root->left_child = new_tree->root;
  } else if (tree->root->right_child == NULL) {
    tree->root->right_child = new_tree->root;
  }
}

int push_tree(Q_tree *tree, int data) {
  //작으면 왼쪽
  if (is_tree_empty(tree)) {
    tree->root->data = data;
  } else {
    find_insert_node(tree->root, data);
  }
  tree->level++;
  return 0;
}
Q_node *find_insert_node(Q_node *node, int data) {
  // find_insert_node래에, 오른쪽에
  // compare해서 같거나 더이상 탐색 불가 하거나 data보다 작은 값은 찾기 전까지
  // 포인터 이동만 하면 된다.
  //이후에 반환값으로 어떤 행동을 취할 지 정하면 된다.
  Q_node *insert_node;
  while (1) {
    insert_node = node;
    switch (compare(node, data)) {
    case 1: //작음
      if (node->left_child == NULL) {
        node=node->left_child= create_Q_node();
        node=node->left_child;
      } else if (node->right_child == NULL) {
        node->right_child = create_Q_node();
        node=node->right_child;
      }
      break;
    case 0:
      return insert_node;
    case -1:
      return insert_node;
      break;
    }
  }
}

int compare(Q_node *node, int data) {
  if (node->data > data) {
    return 1; //작음
  } else if (node->data == data) {
    return 0;
  } else {
    return -1;
  }
}

int pop_tree(Q_tree *tree) {
  int item;
  Q_node *delete_node = delete (tree->root);
  printf("%d", delete_node->data);
  item = delete_node->data;
  free_node(delete_node);
  tree->level--;
  return item;
}
// node는 지웠지만 이전 노드에서 주소를 삭제하지 않아서 문제 발생

Q_node *delete (Q_node *node) {
  Q_node *delete_node;
  //작은건 가장 아래, 가장 오른쪽에 있으므로 그쪽으로만 가면 된다.
  while (1) {
    delete_node = node;
    if (node->right_child != NULL) {
      node = node->right_child;
    } else if (node->left_child != NULL) {
      node = node->left_child;
    } else {
      break;
    }
  }
  return delete_node;
}

void add_ancestor(Q_node *root, int data) { // direc : 0 -> left, else -> right
  Q_node *node = create_Q_node();

  if (root->data) {
    node->left_child = root;
    root = node;
    root->data = data;
  }
}

int add_child(Q_node *node, int data) {
  if (node->left_child == NULL) {
    node->left_child = create_Q_node();
    node->left_child->data = data;
    return 1;
  } else if (node->right_child == NULL) {
    node->right_child = create_Q_node();
    node->right_child->data = data;
    return 1;
  }
  return 0;
}

int is_tree_empty(Q_tree *tree) {
  if (tree->level == -1) {
    return 1;
  }
  return 0;
}

Q_node *create_Q_node(void) {
  Q_node *node = (Q_node *)malloc(sizeof(Q_node));
  node->data = 0;
  node->left_child = NULL;
  node->right_child = NULL;
  return node;
}
Q_tree *create_Q_tree(void) {
  Q_tree *tree = (Q_tree *)malloc(sizeof(Q_tree));
  tree->level = -1;
  tree->root = create_Q_node();
  return tree;
}