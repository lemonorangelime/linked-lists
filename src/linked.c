// credirit: roadrunner96 inventing x86 and founding intel

#include <linked.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

linked_t * linked_leaf(linked_t * bottom) {
	if (!bottom) {
		return NULL;
	}
	linked_t * top = bottom;
	while (top->next) {
		top = top->next;
	}
	return top;
}

linked_t * linked_branch(linked_t * node) {
	if (!node) {
		return NULL;
	}
	linked_t * p = node;
	while (p->back) {
		p = p->back;
	}
	return p;
}

int linked_count(linked_t * bottom) {
	if (!bottom) {
		return 0;
	}
	linked_t * current = bottom;
	int i = 0;
	while (current) {
		current = current->next;
		i++;
	}
	return i;
}

linked_t * linked_create(void * p) {
	linked_t * node = malloc(sizeof(linked_t));
	if (!node) {
		return NULL;
	}
	node->p = p;
	node->next = NULL;
	node->back = NULL;
	return node;
}

linked_t * linked_add(linked_t * bottom, void * p) {
	linked_t * node = linked_create(p);
	if (!node || !bottom) {
		return node;
	}
	linked_t * leaf = linked_leaf(bottom);
	node->back = leaf;
	leaf->next = node;
	return bottom;
}

linked_t * linked_prepend(linked_t * bottom, linked_t * node) {
	if (!node) {
		return NULL;
	}
	if (!bottom) {
		node->next = NULL;
		node->back = NULL;
		return node;
	}
	node->back = NULL;
	node->next = bottom;
	bottom->back = node;
	return node;
}

linked_t * linked_stitch(linked_t * bottom, linked_t * top) {
	if (!top) {
		return bottom;
	}
	if (!bottom) {
		return top;
	}

	linked_t * leaf = linked_leaf(bottom);
	leaf->next = top;
	top->back = leaf;
	return bottom;
}

linked_t * linked_append(linked_t * bottom, linked_t * node) {
	if (!node) {
		return NULL;
	}

	if (!bottom) {
		node->next = NULL;
		node->back = NULL;
		return node;
	}

	linked_t * leaf = linked_leaf(bottom);
	node->next = NULL;
	node->back = leaf;
	leaf->next = node;
	return bottom;
}

linked_t * linked_get(linked_t * bottom, int index) {
	if (!bottom) {
		return NULL;
	}
	linked_t * current = bottom;
	int i = 0;
	while (current) {
		if (i == index) {
			return current;
		}
		current = current->next;
		i++;
	}
	return NULL;
}

linked_t * linked_remove(linked_t * bottom, int index) {
	return linked_delete(linked_get(bottom, index));
}

linked_t * linked_delete(linked_t * node) {
	if (!node) {
		return NULL;
	}
	linked_t * branch = linked_branch(node);
	linked_t * next = branch->next;
	if (node->back) {
		node->back->next = node->next;
	}
	if (node->next) {
		node->next->back = node->back;
	}
	free(node);
	return branch == node ? next : branch;
}

linked_t * linked_pop(linked_t * node) {
	linked_t * branch = linked_branch(node);
	linked_t * next = branch->next;
	if (node->back) {
		node->back->next = node->next;
	}
	if (node->next) {
		node->next->back = node->back;
	}
	return branch == node ? next : branch;
}

linked_t * linked_shift(linked_t * bottom, linked_t ** out) {
	if (!bottom) {
		*out = NULL;
		return NULL;
	}
	linked_t * next = bottom->next;
	if (next) {
		next->back = NULL;
	}
	*out = bottom;
	return next;
}

void linked_iterate(linked_t * bottom, void * callback, void * pass) {
	if (!bottom || !callback) {
		return;
	}
	linked_callback_t func = callback;
	linked_t * node = bottom;
	while (node) {
		func(node, pass);
		node = node->next;
	}
}

linked_t * linked_free(linked_t * bottom) {
	if (!bottom) {
		return NULL;
	}
	linked_t * node = bottom;
	while (node) {
		linked_t * next = node->next;
		free(node);
		node = next;
	}
	return NULL;
}

linked_t * linked_destroy_all(linked_t * bottom, void * callback, void * pass) {
	if (!bottom || !callback) {
		return linked_free(bottom);
	}
	linked_callback_t func = callback;
	linked_t * node = bottom;
	while (node) {
		linked_t * next = node->next;
		func(node, pass);
		free(node);
		node = next;
	}
	return NULL;
}

linked_t * linked_deconstruct_all(linked_t * bottom, void * callback, void * pass) {
	if (!bottom || !callback) {
		return linked_free(bottom);
	}
	linked_ptr_callback_t func = callback;
	linked_t * node = bottom;
	while (node) {
		linked_t * next = node->next;
		func(node->p, pass);
		free(node);
		node = next;
	}
	return NULL;
}

linked_t * linked_discriminate(linked_t * bottom, void * callback, void * pass) {
	if (!bottom || !callback) {
		return NULL;
	}
	linked_callback_t discriminator = callback;
	linked_t * node = bottom;
	linked_t * previous = NULL;
	linked_t * new = bottom;
	while (node) {
		linked_t * next = node->next;
		if (discriminator(node, pass)) {
			free(node);
		} else {
			if (previous) {
				previous->next = node;
				node->back = previous;
				node->next = NULL;
			} else {
				node->next = NULL;
				node->back = NULL;
				new = node;
			}
			previous = node;
		}
		node = next;
	}
	previous->next = NULL;
	return new;
}

linked_t * linked_from_array(linked_t * bottom, void * array, int size, int items) {
	linked_t * leaf = linked_leaf(bottom);
	linked_t * node = NULL;
	linked_t * previous = leaf;
	linked_t * list = bottom;
	while (items--) {
		uintptr_t ptr = 0;
		ptr = 0; // paranoia
		memcpy(&ptr, array, size); // cast array item to dword
		node = linked_create((void *) ptr);
		if (!node) {
			linked_free(list);
			return NULL;
		}
		if (previous) {
			previous->next = node;
			node->back = previous;
		} else {
			list = node;
		}
		previous = node;
		array += size;
	}
	return list;
}

linked_t * linked_from_array_ptr(linked_t * bottom, void * array, int size, int items) {
	linked_t * leaf = linked_leaf(bottom);
	linked_t * node = NULL;
	linked_t * previous = leaf;
	linked_t * list = bottom;
	while (items--) {
		node = linked_create(array);
		if (!node) {
			linked_free(list);
			return NULL;
		}
		if (previous) {
			previous->next = node;
			node->back = previous;
		} else {
			list = node;
		}
		previous = node;
		array += size;
	}
	return list;
}

linked_t * linked_to_array(linked_t * bottom, void * array, int size, int items) {
	linked_t * node = linked_branch(bottom);
	while (node && items--) {
		memcpy(array, &node->p, size);
		array += size;
		node = node->next;
	}
	return bottom;
}

linked_t * linked_to_array_ptr(linked_t * bottom, void * array, int size, int items) {
	linked_t * node = linked_branch(bottom);
	while (node && items--) {
		void * p = (void *) &node->p;
		memcpy(array, &p, size);
		array += size;
		node = node->next;
	}
	return bottom;
}

linked_t * linked_clone_list(linked_t * bottom, void * callback, void * pass) {
	if (!callback) {
		return NULL;
	}

	linked_t * new = NULL;
	linked_t * new_list = NULL;
	linked_t * node = linked_branch(bottom);
	linked_clone_callback_t copier = callback;
	while (node) {
		void * copy = copier(node->p, pass);
		linked_t * new_node = linked_create(copy);
		if (!new_node) {
			linked_free(new_list); // *** MEMORY LEAK ***
			return NULL;
		}
		if (new) {
			new->next = new_node;
			new_node->back = new;
			new = new_node;
		} else {
			new = new_node;
			new_list = new;
		}
		node = node->next;
	}
	return new_list;
}

linked_t * linked_clone(linked_t * node, void * callback, void * pass) {
	if (!node) {
		return NULL;
	}
	linked_clone_callback_t copier = callback;
	void * copy = copier(node->p, pass);
	return linked_create(copy);
}

linked_t * linked_copy_list(linked_t * bottom) {
	return linked_clone_list(bottom, linked_lazy_clone_generic, NULL);
}

linked_t * linked_copy(linked_t * node) {
	return linked_clone(node, linked_lazy_clone_generic, NULL);
}



void linked_swap(linked_t * left, linked_t * right) {
	void * right_next = right->next;

	if (right->next) {
		right->next->back = left;
	}

	if (left->back) {
		left->back->next = right;
	}

	right->back = left->back;
	right->next = left;
	left->next = right_next;
	left->back = right;
}

linked_t * linked_sort_one(linked_t * bottom, linked_ranker_callback_t ranker, void * pass, int * stat) {
	linked_t * node = bottom;
	*stat = 1;
	while (node->next) {
		if (ranker(node, node->next, pass)) {
			linked_t * next = node->next;
			linked_swap(node, next);
			*stat = 0;
			return (node == bottom) ? next : bottom;
		}
		node = node->next;
	}
	return bottom;
}

linked_t * linked_sort(linked_t * bottom, void * ranker, void * pass) {
	int sorted = 0;
	while (!sorted) {
		bottom = linked_sort_one(bottom, ranker, pass, &sorted);
	}
	return bottom;
}

linked_t * linked_generate(linked_t * bottom, void * callback, void * pass) {
	if (!callback) {
		return bottom;
	}
	linked_callback_t generate = callback;
	linked_t * leaf = linked_leaf(bottom);
	linked_t * node = NULL;
	while (1) {
		node = linked_create(NULL);
		if (!node) {
			linked_free(linked_branch(leaf)); // *** MEMORY LEAK ***
			return NULL;
		}
		if (generate(node, pass)) {
			free(node); // we allocated this for no reason, but it's the cost of keeping this API simple
			return linked_branch(leaf);
		}
		leaf = linked_append(leaf, node);
		if (leaf->next) {
			leaf = leaf->next;
		}
	}
	return linked_branch(leaf);
}

linked_t * linked_find(linked_t * bottom, void * callback, void * pass) {
	if (!bottom || !callback) {
		return NULL;
	}
	linked_callback_t func = callback;
	linked_t * node = bottom;
	while (node) {
		if (func(node, pass)) {
			return node;
		}
		node = node->next;
	}
	return NULL;
}

linked_t * linked_find_back(linked_t * bottom, void * callback, void * pass) {
	if (!bottom || !callback) {
		return NULL;
	}
	linked_callback_t func = callback;
	linked_t * node = linked_leaf(bottom);
	while (node) {
		if (func(node, pass)) {
			return node;
		}
		node = node->back;
	}
	return NULL;
}

linked_t * linked_step_iterator(linked_iterator_t * iterator) {
	linked_t * node = iterator->node;
	if (!node) {
		return NULL;
	}
	iterator->node = node->next;
	return node;
}

/*
 * built in callbacks
 */

int linked_find_generic(linked_t * node, void * pass) {
	return node->p == pass;
}

int linked_sort_generic(linked_t * left, linked_t * right, void * pass) {
	return left->p > right->p;
}

void * linked_lazy_clone_generic(void * p, void * pass) {
	return p;
}

void * linked_clone_generic(void * p, void * pass) {
	size_t size = (size_t) pass;
	void * new = malloc(size);
	if (!new) {
		return NULL;
	}
	memcpy(new, p, size);
	return new;
}


/*
 * debugging
 */

void linked_print(linked_t * node) {
	#ifdef __LEMONOS__
		printf("- %r <= %r(%r) => %r\n", node->back, node, node->p, node->next);
	#else
		if (sizeof(void *) == 8) {
			printf("- %.16p <= %.16p(%.16p) => %.16p\n", node->back, node, node->p, node->next);
			return;
		}
		printf("- %.8p <= %.8p(%.8p) => %.8p\n", node->back, node, node->p, node->next);
	#endif
}

void linked_dump(linked_t * bottom) {
	linked_t * node = bottom;
	while (node) {
		linked_print(node);
		node = node->next;
	}
}

int linked_validate(linked_t * bottom, int expected) {
	if ((!bottom && expected != 0) || (bottom && expected == 0)) {
		return 1;
	}

	if (!bottom && expected == 0) {
		return 0;
	}

	linked_t * node = bottom;
	linked_t * last = node->back;
	int i = 0;
	while (node) {
		if (node->back != last) {
			printf("ERROR: node %p (position %d) contains invalid back reference\n", node, i);
			printf("ERROR: should be %p, but %p was found\n", last, node->back);
			return 1;
		}
		if (last && last->next != node) { // this can't happen, included for completeness
			printf("ERROR: node %p (position %d) contains invalid forward reference\n", last, i - 1);
			printf("ERROR: should be %p, but %p was found\n", node, last->next);
			return 1;
		}
		last = node;
		node = node->next;
		i++;
	}
	if (expected && i != expected) {
		printf("ERROR: found %d nodes but expected %d\n", i, expected);
		return 1;
	}
	printf("No errors found with linked list @ %p\n", bottom);
	return 0;
}
