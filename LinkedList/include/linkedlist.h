#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

typedef unsigned int uint;
typedef enum { FALSE,
               TRUE } __BOOL;

typedef __BOOL (*iterator)(void *);
typedef void (*free_linkedlist)(void *);

typedef struct linkedlist_node
{
    struct linkedlist_node *next;
    struct linkedlist_node *previous;
    void *data;
} linkedlist_node_t;

typedef struct linkedlist
{
    linkedlist_node_t *first;
    linkedlist_node_t *last;
    uint length;
    size_t element_size;
    free_linkedlist free_func;
} linkedlist_t;

void linkedlist_create(linkedlist_t *, size_t, free_linkedlist);

void linkedlist_destroy(linkedlist_t *);

void linkedlist_foreach(linkedlist_t *, iterator);

uint linkedlist_length(linkedlist_t *);

size_t linkedlist_elementsize(linkedlist_t *);

void linkedlist_addfirst(linkedlist_t *, void *);

void linkedlist_addlast(linkedlist_t *, void *);

#endif // LINKEDLIST_H_INCLUDED
