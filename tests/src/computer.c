#include <linked.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

int dump(linked_t * node, void * pass) {
	printf("- %p <= %p(%p) => %p\n", node->back, node, node->p, node->next);
}

// filter out odd nodes
int discriminator(linked_t * node, void * pass) {
	uintptr_t address = (uintptr_t) node->p;
	return (address & 1) != 0;
}

// generate 10 nodes
int i = 0;
int computer(linked_t * node, void * pass) {
	node->p = (void *) ++i;
	return i == 11; // stop at node 11
}

int main() {
	linked_t * list = linked_compute(NULL, computer, NULL);
	linked_iterate(list, dump, NULL);

	printf("\nRemoving odd nodes\n\n");

	list = linked_discriminate(list, discriminator, NULL);
	linked_iterate(list, dump, NULL);
}
