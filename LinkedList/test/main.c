#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "../include/linkedlist.h"

__BOOL helper_print(void*);
void helper_free(void*);
void linkedlist_create_test(linkedlist_t*);
void linkedlist_addfirst_test(linkedlist_t*);
void linkedlist_addlast_test(linkedlist_t*);
void linkedlist_foreach_test(linkedlist_t*);
void linkedlist_destroy_test(linkedlist_t*);

int main(int argc, char** args)
{  
	linkedlist_t linkedlist;

	puts("Creating linked list...");
	linkedlist_create_test(&linkedlist);
	printf("SUCCEEDED!\n");
	puts("Add items to linked list...");	
	linkedlist_addfirst_test(&linkedlist);
	linkedlist_addlast_test(&linkedlist);
	printf("SUCCEEDED!\n");
	
	puts("Iterating throough linked list...");	
	linkedlist_foreach_test(&linkedlist);
	printf("SUCCEEDED!\n");

	puts("Destroying linked list...");		
	linkedlist_destroy_test(&linkedlist);
	printf("SUCCEEDED!\n");
	
	return 0;
}

__BOOL helper_print(void* p_value) 
{
	assert(p_value != NULL);
	int value = *((int*)p_value);
	printf("%d ", value);
	return TRUE;
}

void helper_free(void* p_value) 
{
	assert(p_value != NULL);	
	free(p_value);	
}

void linkedlist_create_test(linkedlist_t* list)
{
	linkedlist_create(list, sizeof(int), helper_free);
	assert(list != NULL);
	assert(list->element_size == sizeof(int));
}

void linkedlist_addfirst_test(linkedlist_t* list)
{
	void* mem = calloc(1, sizeof(int));
	assert(mem != NULL);
	int test_value = 99;
	memcpy(mem, &test_value, sizeof(int));
	
	linkedlist_addfirst(list, mem);
	int expected_length = 1;
	assert(list->length == expected_length);
	assert(list->first != NULL);
	assert(list->first->data != NULL);
	assert(*((int*)list->first->data) == *((int*)mem));
}

void linkedlist_addlast_test(linkedlist_t* list)
{
	void* mem = calloc(1, sizeof(int));
	int test_value = 100;
	memcpy(mem, &test_value, sizeof(int));
	assert(mem != NULL);
	
	linkedlist_addlast(list, mem);
	int expected_length = 2;
	assert(list->length == expected_length);
	assert(list->last != NULL);
	assert(list->last->data != NULL);
	assert(*((int*)list->last->data) == *((int*)mem));
}

void linkedlist_foreach_test(linkedlist_t* list)
{
	linkedlist_foreach(list, helper_print);
}

void linkedlist_destroy_test(linkedlist_t* list)
{
	linkedlist_destroy(list);
	assert(list->length == 0);
	assert(list->element_size == 0);
	assert(list->first == NULL);
	assert(list->last == NULL);
}