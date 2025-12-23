#pragma once

#include <stdint.h>

#define LINKED_DATA \
	union { \
		void * p; \
		int64_t s64; \
		int64_t i64; \
		int64_t int64; \
		uint64_t u64; \
		uint64_t uint64; \
		int64_t s32; \
		int64_t i32; \
		int64_t int32; \
		uint64_t uint32; \
		uint64_t u32; \
	};

typedef struct linked {
	LINKED_DATA;
	struct linked * next;
	struct linked * back;
} __attribute__((aligned(64))) linked_t;

// who even uses slinked_t ??

typedef struct slinked {
	LINKED_DATA;
	struct slinked * next;
} __attribute__((aligned(64))) slinked_t;

typedef struct {
	linked_t * node;
} linked_iterator_t;

// generic callback
typedef int (* linked_callback_t)(linked_t * node, void * pass);
typedef int (* linked_ranker_callback_t)(linked_t * left, linked_t * right, void * pass);
typedef int (* linked_ptr_callback_t)(void * p, void * pass);
typedef void * (* linked_clone_callback_t)(void * p, void * pass);

/*
 * general stuff
 */

linked_t * linked_leaf(linked_t * bottom); // grab the leaf node
linked_t * linked_branch(linked_t * node); // grab the branch node
int linked_count(linked_t * bottom); // count nodes
linked_t * linked_add(linked_t * bottom, void * p); // create a new node and add it
linked_t * linked_create(void * p);
linked_t * linked_prepend(linked_t * bottom, linked_t * node); // prepend an existing node to start
linked_t * linked_stitch(linked_t * bottom, linked_t * top); // stitch two lists together
linked_t * linked_append(linked_t * bottom, linked_t * node); // append an existing node to end
linked_t * linked_get(linked_t * bottom, int index); // get a node at index
linked_t * linked_remove(linked_t * bottom, int index); // remove a node at index
linked_t * linked_delete(linked_t * node); // remove this node from it's list (AND FREE)
linked_t * linked_pop(linked_t * node); // remove this node from it's list (no free)
linked_t * linked_shift(linked_t * bottom, linked_t ** out); // shift one out of the list
void linked_iterate(linked_t * bottom, void * callback, void * pass); // call callback() for every node
linked_t * linked_destroy_list(linked_t * bottom, void * destroy, void * pass); // call destory() for every node, then delete it, leaving an empty list
linked_t * linked_deconstruct_list(linked_t * bottom, void * deconstruct, void * pass); // call deconstruct() for every pointer, then delete the node, leaving an empty list
linked_t * linked_free(linked_t * bottom);
linked_t * linked_copy_list(linked_t * bottom); // creates a list copy with the same pointers (refernce)
linked_t * linked_clone_list(linked_t * bottom, void * copier, void * pass); // creates a list copy with the same data (we have no type info so copy yourself) (copy)
linked_t * linked_copy(linked_t * node); // creates a node copy with the same pointers (reference)
linked_t * linked_clone(linked_t * node, void * copier, void * pass); // creates a node copy with the same data (we have no type info so copy yourself) (copy)
void linked_swap(linked_t * left, linked_t * right); // swap node references
linked_t * linked_sort(linked_t * bottom, void * ranker, void * pass); // sorts a list according to ranker results
linked_t * linked_discriminate(linked_t * bottom, void * discriminator, void * pass); // racism function basically
linked_t * linked_from_array(linked_t * bottom, void * array, int size, int items);
linked_t * linked_from_array_ptr(linked_t * bottom, void * array, int size, int items);
linked_t * linked_to_array(linked_t * bottom, void * array, int size, int items);
linked_t * linked_to_array_ptr(linked_t * bottom, void * array, int size, int items);
linked_t * linked_generate(linked_t * bottom, void * generate, void * pass);
linked_t * linked_find(linked_t * bottom, void * callback, void * pass); // search for a node
linked_t * linked_find_back(linked_t * bottom, void * callback, void * pass); // search for a node (backwards)
linked_t * linked_step_iterator(linked_iterator_t * iterator);

/*
 * aliases; for backwards compatibility mostly
 */

#define linked_destroy_all linked_destroy_list
#define linked_deconstruct_all linked_deconstruct_list

/*
 * built in callbacks
 */

int linked_find_generic(linked_t * node, void * pass); // return node->p == pass;
int linked_sort_generic(linked_t * left, linked_t * right, void * pass); // return left->p > right->p;
void * linked_lazy_clone_generic(void * p, void * pass); // return p;
void * linked_clone_generic(void * p, void * pass); // return memcpy(malloc((size_t) pass), p, (size_t) pass);

/*
 * debugging
 */

void linked_print(linked_t * node);
void linked_dump(linked_t * bottom);
int linked_validate(linked_t * bottom, int expected);
