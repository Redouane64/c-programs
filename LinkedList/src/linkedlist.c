#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdbool.h>

#if DEBUG
#include <stdio.h>
#endif

#include "../include/linkedlist.h"

void linkedlist_create(linkedlist_t *list, size_t element_size, free_linkedlist freeFn)
{
    assert(list != NULL);
    list->element_size = element_size;
	list->length = 0;
    list->free_func = freeFn;
    list->first = list->last = NULL;
}

void linkedlist_destroy(linkedlist_t*  list) {
	linkedlist_node_t* current = NULL;
#if DEBUG
	uint freed_count = 0;
#endif
	while(list->first != NULL) {
		current = list->first;
		list->first = current->next;
		if(list->free_func != NULL) 
		{ 
#if DEBUG
			++freed_count;
#endif
			list->free_func(current->data);
		}
		free(current);
	}
#if DEBUG
	assert(list->length == freed_count);
#endif
	list->last = list->first = NULL;
	list->length = 0;
	list->element_size = 0;
}

void linkedlist_foreach(linkedlist_t* list, iterator itr) {
	assert(list != NULL);
	linkedlist_node_t* current = list->first;
	__BOOL result = TRUE;
	while(current != NULL && result) 
	{
		result = itr(current->data);
		current = current->next;
	}
}

uint linkedlist_length(linkedlist_t *list)
{
    assert(list != NULL);
    return list->length;
}

size_t linkedlist_elementsize(linkedlist_t *list)
{
    assert(list != NULL);
    return list->element_size;
}

void linkedlist_addfirst(linkedlist_t* list, void* data) {
	assert(list != NULL && data != NULL);
	linkedlist_node_t* node = malloc(sizeof(linkedlist_node_t));
	node->data = malloc(list->element_size);
	node->previous = node->next = NULL;
	memcpy(node->data, data, list->element_size);
	if(linkedlist_length(list) == 0) 
	{
		list->first = list->last = node;
	}
	else 
	{
		node->next = list->first;
		list->first->previous = node;
		list->first = node;
	}
	list->length++;
}

void linkedlist_addlast(linkedlist_t* list, void* data) {
	assert(list != NULL && data != NULL);
	linkedlist_node_t* node = malloc(sizeof(linkedlist_node_t));
	node->data = malloc(list->element_size);
	node->next = node->previous = NULL;
	memcpy(node->data, data, list->element_size);
	if(linkedlist_length(list) == 0)
	{
		list->first = list->last = node;
	}
	else 
	{
		node->previous = list->last;
		list->last->next = node;
		list->last = node;
	}
	list->length++;
}
