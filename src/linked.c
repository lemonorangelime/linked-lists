// credirit: roadrunner inventing x86 and founding intel

#include <linked.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

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

void linked_iterate(linked_t * bottom, linked_callback_t callback, void * pass) {
	if (!bottom) {
		return;
	}
	linked_t * node = bottom;
	while (node) {
		callback(node, pass);
		node = node->next;
	}
}

void linked_destroy_all(linked_t * bottom, linked_callback_t destroy, void * pass) {
	if (!bottom) {
		return;
	}
	linked_t * node = bottom;
	while (node) {
		linked_t * next = node->next;
		destroy(node, pass);
		free(node);
		node = next;
	}
}

linked_t * linked_discriminate(linked_t * bottom, linked_callback_t discriminator, void * pass) {
	if (!bottom) {
		return NULL;
	}
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

linked_t * linked_generate(linked_t * bottom, linked_callback_t generate, void * pass) {
	linked_t * leaf = linked_leaf(bottom);
	linked_t * node = NULL;
	while (1) {
		node = linked_create(NULL);
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

linked_t * linked_find(linked_t * bottom, linked_callback_t callback, void * pass) {
	if (!bottom) {
		return NULL;
	}
	linked_t * node = bottom;
	while (node) {
		if (callback(node, pass)) {
			return node;
		}
		node = node->next;
	}
	return NULL;
}

linked_t * linked_find_back(linked_t * bottom, linked_callback_t callback, void * pass) {
	if (!bottom) {
		return NULL;
	}
	linked_t * node = linked_leaf(bottom);
	while (node) {
		if (callback(node, pass)) {
			return node;
		}
		node = node->back;
	}
	return NULL;
}

// generic linked_find callback
int linked_find_generic(linked_t * node, void * pass) {
	return node->p == pass;
}
