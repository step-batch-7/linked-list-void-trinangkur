#include <stdlib.h>
#include "linkedlist.h"

Node_ptr create_node(Element data) {
  Node_ptr new_node = malloc(sizeof(Node));
  new_node->element = data;
  new_node->next = NULL;
  return new_node;
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
