#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../linkedlist.h"

void test_add_to_list(void) {
  printf("\ntesting add_to_end\n");
  List_ptr list = create_list();
  int a = 5;
  printf("\t should have one element while list is empty and have the value inserted\n");
  assert(add_to_list(list, &a));
  assert(list->length == 1);
  assert(*(int *)list->first->element == 5);
  printf("passed...\n");

  printf("\t next of head element should be NULL while having one element\n");
  assert(list->first->next== NULL);
  printf("passed...\n");

  printf("\t last element of list and head should be same while having one element\n");
  assert(list->first == list->last);
  printf("passed...\n");

  printf("\t should have two element after inserting another element to the same list\n");
  int b = 6;
  assert(add_to_list(list, &b));
  assert(list->length == 2);
  assert(*(int *) list->first->next->element == 6);
  assert(*(int *) list->last->element == 6);
  printf("passed...\n");
}

void test_add_to_start(void) {
  printf("\ntesting add_to_start\n");
  List_ptr list = create_list();
  int a = 5;
  printf("\t should have one element while list is empty and have the value inserted\n");
  assert(add_to_start(list, &a));
  assert(list->length == 1);
  assert(*(int *) list->first->element == 5);
  printf("passed...\n");

  printf("\t next of head element should be NULL while having one element\n");
  assert(list->first->next == NULL);
  printf("passed...\n");

  printf("\t last element of list and head should be same while having one element\n");
  assert(list->last == list->first);
  printf("passed...\n");

  printf("\t should have two element after inserting another element to the same list\n");

  int b = 3;
  assert(add_to_start(list, &b));
  assert(list->length == 2);
  printf("\t head should pointing to the new value\n");
  assert(*(int *) list->first->element == 3);
  assert(*(int *) list->last->element == 5);
  printf("passed...\n");
}

void test_insert_at(void){
  printf("\ntesting insert_at\n");
  List_ptr list = create_list();
  int a = 5;
  printf("\t should have one element while list is empty and the value is inserted in 0th position\n");
  assert(insert_at(list, &a, 0));
  assert(list->length == 1);
  assert(*(int *) list->first->element == 5);
  printf("passed...\n");

  int b = 3;
  printf("\t should not be able to insert value in a invalid position\n");
  assert(insert_at(list, &b ,11) == 0);
  printf("passed...\n");
}

void test_reverse(void) {
  printf("\ntesting reverse\n");
  List_ptr list = create_list();
  int a = 5;
  add_to_list(list, &a);
  int b = 6;
  add_to_list(list, &b);
  printf("\t should have first element as value 6 and count as 2\n");
  List_ptr another = reverse(list);
  assert(*(int *) another->first->element == 6);
  assert(another->length == 2);
  printf("passed...\n");

  printf("\t should have last element as value 6");
  assert(*(int *) another->first->element == 6);
  printf("passed...\n");
}

int main(void)
{
  test_add_to_list();
  test_add_to_start();
  test_insert_at();
  test_reverse();
  return 0;
}
