/* $Id: LinkedList.c,v 1.6 2009/06/03 01:10:54 ellson Exp $ $Revision: 1.6 $ */
/* vim:set shiftwidth=4 ts=8: */

/**********************************************************
*      This software is part of the graphviz package      *
*                http://www.graphviz.org/                 *
*                                                         *
*            Copyright (c) 1994-2004 AT&T Corp.           *
*                and is licensed under the                *
*            Common Public License, Version 1.0           *
*                      by AT&T Corp.                      *
*                                                         *
*        Information and Software Systems Research        *
*              AT&T Research, Florham Park NJ             *
**********************************************************/

#include "LinkedList.h"
#include "memory.h"
#define MALLOC gmalloc
#define REALLOC grealloc
#define FREE free
#define MEMCPY memcpy



SingleLinkedList SingleLinkedList_new(void *data){
  SingleLinkedList head;
  head = N_GNEW(1,struct SingleLinkedList_struct);
  head->data = data;
  head->next = NULL;
  return head;
}

void SingleLinkedList_delete(SingleLinkedList head,  void (*linklist_deallocator)(void*)){
  SingleLinkedList next;

  if (!head) return;
  do {
    next = head->next;
    if (head->data) linklist_deallocator(head->data);
    if (head) FREE(head);
    head = next;
  } while (head);

}


SingleLinkedList SingleLinkedList_prepend(SingleLinkedList l, void *data){
  SingleLinkedList head = SingleLinkedList_new(data);
  head->next = l;
  return head;
}

void* SingleLinkedList_get_data(SingleLinkedList l){
  return l->data;
}

SingleLinkedList SingleLinkedList_get_next(SingleLinkedList l){
  return l->next;
}
void SingleLinkedList_print(SingleLinkedList head, void (*linkedlist_print)(void*)){

  if (!head) return;
  do {
    if (head->data) linkedlist_print(head->data);
    head = head->next;
  } while (head);
 
}


DoubleLinkedList DoubleLinkedList_new(void *data){
  DoubleLinkedList head;
  head = N_GNEW(1,struct DoubleLinkedList_struct);
  head->data = data;
  head->next = NULL;
  head->prev = NULL;
  return head;
}

void DoubleLinkedList_delete(DoubleLinkedList head,  void (*linklist_deallocator)(void*)){
  DoubleLinkedList next;

  if (!head) return;
  do {
    next = head->next;
    if (head->data) linklist_deallocator(head->data);
    if (head) FREE(head);
    head = next;
  } while (head);

}


DoubleLinkedList DoubleLinkedList_prepend(DoubleLinkedList l, void *data){
  DoubleLinkedList head = DoubleLinkedList_new(data);
  if (l){
    head->next = l;
    l->prev = head;
  }
  return head;
}

void* DoubleLinkedList_get_data(DoubleLinkedList l){
  return l->data;
}

DoubleLinkedList DoubleLinkedList_get_next(DoubleLinkedList l){
  return l->next;
}

void DoubleLinkedList_print(DoubleLinkedList head, void (*linkedlist_print)(void*)){

  if (!head) return;
  do {
    if (head->data) linkedlist_print(head->data);
    head = head->next;
  } while (head);
 
}

void DoubleLinkedList_delete_element(DoubleLinkedList l, void (*linklist_deallocator)(void*), DoubleLinkedList *head){
  /* delete an entry in the chain of linked list. If the head changes due to this (if l is the first element in the list), update */
  DoubleLinkedList next, prev;

  if (l){
    next = l->next;
    prev = l->prev;
    
    if (l->data) linklist_deallocator(l->data);
    FREE(l);
    l = NULL;

    if (next) next->prev = prev;
    if (prev) prev->next = next;
    if (!prev) *head = next;
  }
}


/*
static void print_int(void *d){
  int *i = (int*) d;
  printf("%d\n",*i);
}

main(){
  DoubleLinkedList l, ll;

  int i, *j;

  for (;;){
  j = malloc(sizeof(int));
  j[0] = -1;
  l = DoubleLinkedList_new((void*) j);

  for (i = 0; i < 10; i++){
    j = malloc(sizeof(int));
    j[0] = i;
    l = DoubleLinkedList_prepend(l, (void*) j);
    
  }
  DoubleLinkedList_print(l, print_int);

  ll = DoubleLinkedList_get_next(l);
  DoubleLinkedList_delete_element(ll, free, &l);
  printf("after delete 8\n");
  DoubleLinkedList_print(l, print_int);

  DoubleLinkedList_delete_element(l, free, &l);
  printf("after delete first elemnt\n");
  DoubleLinkedList_print(l, print_int);

  DoubleLinkedList_delete(l, free);
  }
}

*/
