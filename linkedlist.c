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

List_ptr map(List_ptr list, Mapper mapper) {
  List_ptr new_list = create_list();
  Node_ptr p_walk = list->first;
  while (p_walk != NULL) {
    add_to_list(new_list, mapper(p_walk->element));
    p_walk = p_walk->next;
  }
  return new_list;
}

List_ptr filter(List_ptr list, Predicate predicate) {
  List_ptr new_list = create_list();
  Node_ptr p_walk = list->first;
  while (p_walk != NULL) {
    if (predicate(p_walk->element)) {
      add_to_list(new_list, p_walk->element);
    }
    p_walk = p_walk->next;
  }
  return new_list;
}

Element reduce(List_ptr list, Element context, Reducer reducer) {
  Node_ptr p_walk = list->first;
  while(p_walk != NULL) {
    context = reducer(context, p_walk->element);
    p_walk = p_walk->next;
  }
  return context;
}

void forEach(List_ptr list, ElementProcessor processor) {
  Node_ptr p_walk = list->first;
  while(p_walk != NULL) {
    processor(p_walk->element);
    p_walk = p_walk->next;
  }
}

Element remove_from_start(List_ptr list) {
  if(list->length == 0) {
    return NULL;
  }
  Node_ptr temp = list->first;
  list->first = temp->next;
  list->length--;

  if(list->length == 0) {
    list->last = NULL;
  }
  return temp->element;
}

Element remove_from_end(List_ptr list) {
  if(list->length == 0) {
    return NULL;
  }

  list->length--;
  Node_ptr last = list->last;
  if(list->length == 0) {
    list->first = NULL;
    list->last = NULL;
  } else {
    list->last = get_node(list, list->length - 1);
    list->last->next = NULL;
  }
  return last->element;
}

Element remove_at(List_ptr list, int position) {
  if(position >= list->length || position < 0) {
    return NULL;
  }
  if(position == 0) {
    return remove_from_start(list);
  }
  if (position == list->length - 1) {
    return remove_from_end(list);
  }

  Node_ptr above_node = get_node(list,position - 1);
  Node_ptr temp = above_node->next;
  above_node->next = temp->next;
  list->length--;
  return temp;
}

Element remove_first_occurrence(List_ptr list, Element element, Matcher matcher) {
  if (list->length == 0) {
    return NULL;
  }
  if (matcher(list->first->element, element)) {
    return remove_from_start(list);
  }

  Node_ptr p_walk = list->first;
  for (int i = 1; i < list->length - 1; i++) {
    if (matcher(p_walk->next->element, element)) {
      Node_ptr temp = p_walk->next;
      p_walk->next = temp->next;
      list->length--;
      return temp;
    }
    p_walk = p_walk->next;
  }

  if (matcher(list->last->element, element)) {
    return remove_from_end(list);
  }
  return NULL;
}

List_ptr remove_all_occurrences(List_ptr list, Element element, Matcher matcher) {
  List_ptr new_list = create_list();
  Node_ptr p_walk = list->first;
  while (p_walk != NULL) {
    if (!matcher(p_walk->element, element)) {
      add_to_list(new_list, p_walk->element);
    }
    p_walk = p_walk->next;
  }
  return new_list;
}

Status add_unique(List_ptr list, Element element, Matcher matcher) {
  Node_ptr p_walk = list->first;
  while (p_walk != NULL) {
    if (matcher(p_walk->element, element)) {
      return Failure;
    }
  }
  return add_to_list(list,element);
}