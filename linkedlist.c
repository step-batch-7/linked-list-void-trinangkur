#include <stdlib.h>
#include "linkedlist.h"

Node_ptr create_node(Element data) {
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->element = data;
  new_node->next = NULL;
  return new_node;
}

Node_ptr get_node(List_ptr list, int position) {
  Node_ptr p_walk = list->first;
  for(int i = 0; i < position; i++)
  {
    p_walk = p_walk->next;
  }
  return p_walk;
}

List_ptr create_list(void) {
  List_ptr new_list = malloc(sizeof(LinkedList));
  new_list->first = NULL;
  new_list->last = NULL;
  new_list->length = 0;
  return new_list;
}

Status add_to_list(List_ptr list, Element data) {
  Node_ptr new_node = create_node(data);
  if (new_node == NULL) {
    return Failure;
  }
  if (list->first == NULL) {
    list->first = new_node;
  }else {
    list->last->next = new_node;
  }
  list->length += 1;
  list->last = new_node;
  return Success;
}

Status add_to_start(List_ptr list, Element element) {
  Node_ptr new_node = create_node(element);
  if (new_node == NULL) {
    return Failure;
  }
  Node_ptr temp = list->first;
  list->first = new_node;
  if (temp == NULL) {
    list->last = new_node;
  }else{
    list->first->next = temp;
  }
  list->length += 1;
  return Success;
}

Status insert_at(List_ptr list, Element element, int position) {
  if(position > list->length || position < 0) {
    return Failure;
  }
  if(position == 0) {
    return add_to_start(list, element);
  }
  if (position == list->length)
  {
    return add_to_list(list,element);
  }
  
  Node_ptr above_node = get_node(list, position - 1);
  Node_ptr new_node = create_node(element);
  Node_ptr temp = above_node->next;
  new_node->next = temp;
  above_node->next = new_node;
  list->length++;
  return Success;
}

List_ptr reverse(List_ptr list) {
  List_ptr new_list = create_list();
  Node_ptr p_walk = list->first;
  while (p_walk != NULL) {
    add_to_start(new_list, p_walk->element);
    p_walk = p_walk->next;
  }
  return new_list;
}