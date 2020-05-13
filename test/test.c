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

int main(void)
{
  test_add_to_list();
  return 0;
}
