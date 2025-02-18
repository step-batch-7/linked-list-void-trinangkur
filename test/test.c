#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../linkedlist.h"

void *increment (void *a) {
  int *b = malloc(sizeof(int));
  *b = *((int *)a) + 1;
  return b;
}

Status is_less_than_5 (void *a) {
  return *(int *)a < 5;
}

void * sum_using_ref(void *a, void *b) {
  int *c = malloc(sizeof(int));
  *c = *(int *) a + *(int *)b;
  return c;
}

Status compare_int(void *a, void *b) {
  return *(int *) a == *(int *) b;
}

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

  printf("\t should have last element as value 6\n");
  assert(*(int *) another->first->element == 6);
  printf("passed...\n");
}

void test_map(void) {
  printf("\ntesting map\n");
  List_ptr list = create_list();
  int a = 5;
  int b = 3;
  add_to_list(list, &a);
  add_to_list(list, &b);
  List_ptr another_list = map(list,increment);
  printf("\t should get an linkedlist with all values incremented by one\n");
  Node_ptr p_walk = list->first;
  Node_ptr another_p_walk = another_list->first;
  while (p_walk != NULL) {
    assert((*(int *)p_walk->element) + 1 == (*(int *) another_p_walk->element));
    p_walk = p_walk->next;
    another_p_walk = another_p_walk->next;
  }
  printf("passed...\n");
}

void test_filter(void) {
  printf("\ntesting filter\n");
  List_ptr list = create_list();
  int a = 5;
  int b = 3;
  add_to_list(list, &a);
  add_to_list(list, &b);
  List_ptr another_list = filter(list,is_less_than_5);
  printf("\t should filter elements which are less than 5\n");
  Node_ptr p_walk = another_list->first;
  while (p_walk != NULL) {
    assert(*(int *)p_walk->element < 5);
    p_walk = p_walk->next;
  }
  assert(another_list->length == 1);
  printf("passed...\n");
}

void test_reduce(void) {
  printf("\ntesting reducer\n");
  List_ptr list = create_list();
  int d = 0;
  printf("\t should return the initial context for an empty linkedlist\n");
  Element sum = reduce(list, &d, sum_using_ref);
  assert(*(int *) sum == 0);
  printf("passed...\n");
  int a = 5;
  int b = 3;
  add_to_list(list, &a);
  add_to_list(list, &b);
  int c = 0;
  printf("\t should reduce for given list and a reducer\n");
  sum = reduce(list, &c, sum_using_ref);
  assert(*(int *) sum == 8);
  printf("passed...\n");
}

void test_remove_from_start(void) {
  printf("\ntesting remove_from_start\n");
  List_ptr list = create_list();
  printf("\t should not be able to remove anything while list is empty\n");
  assert(remove_from_start(list) == NULL);
  printf("passed...\n");
  int a = 5;
  int b = 3;
  add_to_start(list,&a);
  add_to_start(list,&b);

  printf("\t should be able to remove one value from start while list is not empty\n");
  assert(*(int *) remove_from_start(list) == 3);
  assert(list->length == 1);
  assert(* (int *) list->first->element == 5);
  printf("passed...\n");
}

void test_remove_from_end(void) {
  printf("\ntesting remove_from_end\n");
  List_ptr list = create_list();
  printf("\t should not be able to remove anything while list is empty\n");
  assert(remove_from_end(list) == NULL);
  printf("passed...\n");

  int a = 5;
  int b = 3;
  add_to_start(list,&a);
  add_to_start(list,&b);

  printf("\t should be able to remove one value from end while list is not empty\n");
  assert(*(int *) remove_from_end(list)== 5);
  assert(list->length == 1);
  assert(*(int *) list->first->element == 3);
  printf("passed...\n");
}

void test_remove_at(void) {
  printf("\ntesting remove_at\n");
  List_ptr list = create_list();
  printf("\t should not be able to remove anything while list is empty\n");
  assert(remove_at(list,0) == NULL);
  printf("passed...\n");

  int a = 5;
  int b = 3;
  int c = 2;
  add_to_start(list,&a);
  add_to_start(list,&c);
  add_to_start(list,&b);

  printf("\t should be able to remove one value from middle\n");
  assert(*(int *) remove_at(list,1) == 2);
  assert(list->length == 2);
  assert(*(int *) list->first->element == 3);
  printf("passed...\n");

  printf("\t should be able to remove one value from a given valid position\n");
  assert(*(int *) remove_at(list,1) == 5);
  assert(list->length == 1);
  assert(*(int *) list->first->element == 3);
  printf("passed...\n");

  printf("\t should not be able to remove elment for a invalid position\n");
  assert(remove_at(list,1) == NULL);
  printf("passed...\n");
}

void test_remove_first_occurrence(void) {
  printf("\ntesting remove_first_occurrence\n");
  List_ptr list = create_list();
  int a = 5;
  int b = 5;
  add_to_list(list, &a);
  add_to_list(list, &b);
  printf("\tShould remove first match only\n");
  int c = 5;
  assert(*(int *) remove_first_occurrence(list, &c, compare_int) == 5);
  assert(list->length== 1);
  assert(*(int *) list->first->element == 5);
  assert(*(int *) list->last->element == 5);
  printf("passed...\n");

  printf("\tShould not able to remove if no matches exist\n");
  int d = 1;
  assert(remove_first_occurrence(list, &d, compare_int) == NULL);
  assert(list->length == 1);
  assert(*(int *) list->first->element == 5);
  assert(*(int *) list->last->element == 5);
  printf("passed...\n");

  printf("\tShould remove all elements while matching with only element in list\n");
  int e = 5;
  assert(*(int *) remove_first_occurrence(list, &e, compare_int) == 5);
  assert(list->length == 0);
  assert(list->first == NULL);
  assert(list->last == NULL);
  printf("passed...\n");
}

void test_remove_all_occurrence(void) {
  printf("\ntesting remove_all_occurrences\n");
  List_ptr list = create_list();
  int x = 5;
  int y = 3;
  int z = 3;
  add_to_list(list, &x);
  add_to_list(list, &y);
  add_to_list(list, &z);

  printf("\tShould get empty list if nothing matches\n");

  int a = 0;

  List_ptr new_list = remove_all_occurrences(list, &a, compare_int);
  assert(list->length == 3);
  assert(* (int *) list->first->element == 5);
  assert(* (int *) list->last->element == 3);
  assert(new_list->length == 0);
  assert(new_list->first == NULL);
  assert(new_list->last == NULL);
  printf("passed...\n");

  int b = 3;
  printf("\tShould remove all mathces in list\n");
  new_list = remove_all_occurrences(list, &b, compare_int);
  printf("-->%d\n", list->length);
  assert(list->length == 1);
  assert(* (int *) list->first->element == 5);
  assert(* (int *) list->last->element == 5);
  assert(new_list->length == 2);
  assert(* (int *) new_list->first->element == 3);
  assert(* (int *) new_list->last->element == 3);
  printf("passed...\n");
}

void test_add_unique(void) {
  printf("\ntesting add_unique\n");
  List_ptr list = create_list();
  printf("\t should have one element while list is empty and value is inserted\n");
  int a = 5;
  assert(add_unique(list,&a,compare_int));
  assert(list->length == 1);
  assert(* (int *) list->first->element == 5);
  printf("passed...\n");

  printf("\t should not add the same value which has been inserted\n");
  int b = 5;
  assert(add_unique(list,&b,compare_int) == 0);
  assert(list->length == 1);
  printf("passed...\n");
}

int main(void)
{
  test_add_to_list();
  test_add_to_start();
  test_insert_at();
  test_reverse();
  test_map();
  test_filter();
  test_reduce();
  test_remove_from_start();
  test_remove_from_end();
  test_remove_at();
  test_remove_first_occurrence();
  test_remove_all_occurrence();
  test_add_unique();
  return 0;
}
