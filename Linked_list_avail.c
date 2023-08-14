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

Llist avail;
Node* get_node(void);
void  ret_node(Node*);

int main(void) {
  Llist li = create_llist();
  avail=create_llist();
  add_node(&li, 1, 1);
  print_Llist(&li);

  add_node(&li, 2, 1);
  print_Llist(&li);

  add_node(&li, 3, li.size+1);

  print_Llist(&li);
  add_node(&li, 1, li.size+1);
  add_node(&li, 2, li.size+1);
  add_node(&li, 6, 10);

  delete_node(&li, 10);

  delete_node(&li, 0);

  delete_node(&li, 10);

  delete_node(&li, 10);

  delete_node(&li, 10);

  delete_node(&li, 10);



  add_node(&li, 1, 1);
  add_node(&li, 2, 1);
  add_node(&li, 3, li.size+1);
  add_node(&li, 1, li.size+1);
  add_node(&li, 2, li.size+1);
  add_node(&li, 6, 10);

  return 1;
}

//avail을 이용한 가용 공간 활용시 필요한 연산
Node* get_node(void){
    if(is_empty(&avail)){
        Node* new_node=(Node*)malloc(sizeof(Node));
        printf("use new memory");
        return new_node;
    }
    else{
        Node* avail_node;
        printf("\nuse avail ");
        //print_Llist(&avail);
        avail_node = avail.head;
        avail.head=avail.head->next;
        avail.size--;
        //print_Llist(&avail);
        printf("%p\n",avail_node);
        //printf("%d",avail_node->data);
        return avail_node;
    }

}
void  ret_node(Node* node){
    node->next=avail.head;
    avail.head=node;
    avail.size++;
    printf("avail : ");
    printf("%p\n",node);
}



//기본적인 List 연산
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
    //Node *new_node = (Node *)malloc(sizeof(Node));//원래
    Node *new_node = get_node(); //use avail
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
    } else {
      Node *node = find_location(li, location + 1);
      remove_node = node;
      node = node->next;
    }
    //free(remove_node);//원래
    ret_node(remove_node);
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