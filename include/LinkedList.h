#ifndef LINKED_LIST_H
#define LINKED_LIST_H
#include <stdio.h>
#include <stdlib.h>

template <typename T>
class LinkedList {

  struct node {
    T data;
    node* prev;
    node* next;
  };

  size_t listSize;

  node* first;
  node* last;
public:
  //Constructor
  LinkedList<T>(void);
  //Destructor
  ~LinkedList<T>(void);

  void push_back(T data);
  void push_front(T data);

  bool empty(void);
  
  size_t size(void);

  node* remove(node* n);

  T pop_back(void);
  T pop_front(void);

};

#endif
