#pragma once

typedef struct linked {
	void * p;
	struct linked * next;
	struct linked * back;
} linked_t;

typedef struct slinked {
	void * p;
	struct slinked * next;
} slinked_t;

// generic callback
typedef int (* linked_callback_t)(linked_t * node, void * pass);

linked_t * linked_leaf(linked_t * bottom); // grab the leaf node
linked_t * linked_branch(linked_t * node); // grab the branch node
int linked_count(linked_t * bottom); // count nodes
linked_t * linked_add(linked_t * bottom, void * p); // create a new node and add it
linked_t * linked_prepend(linked_t * bottom, linked_t * node); // prepend an existing node to start
linked_t * linked_stitch(linked_t * bottom, linked_t * top); // stitch two lists together
linked_t * linked_append(linked_t * bottom, linked_t * node); // append an existing node to end
linked_t * linked_get(linked_t * bottom, int index); // get a node at index
linked_t * linked_remove(linked_t * bottom, int index); // remove a node at index
linked_t * linked_delete(linked_t * node); // remove this node from it's list (AND FREE)
linked_t * linked_pop(linked_t * node); // remove this node from it's list (no free)
linked_t * linked_shift(linked_t * bottom, linked_t ** out); // shift one out of the list
void linked_iterate(linked_t * bottom, linked_callback_t callback, void * pass); // call callback() for every node
void linked_destroy_all(linked_t * bottom, linked_callback_t destroy, void * pass); // call destory() for every node, then delete it, leaving an empty list
linked_t * linked_discriminate(linked_t * bottom, linked_callback_t discriminator, void * pass);
linked_t * linked_from_array(linked_t * bottom, void * array, int size, int items);
linked_t * linked_from_array_ptr(linked_t * bottom, void * array, int size, int items);
linked_t * linked_compute(linked_t * bottom, linked_callback_t compute, void * pass);
linked_t * linked_find(linked_t * bottom, linked_callback_t callback, void * pass); // search for a node
linked_t * linked_find_back(linked_t * bottom, linked_callback_t callback, void * pass); // search for a node (backwards)

// generic linked_find callback to just do (node->p == pass)
int linked_find_generic(linked_t * node, void * pass);
