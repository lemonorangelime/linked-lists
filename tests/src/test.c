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

int main() {
	char array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	linked_t * list = linked_from_array(NULL, array, 1, 10);

	linked_iterate(list, dump, NULL);
	printf("\nRemoving odd nodes\n\n");
	list = linked_discriminate(list, discriminator, NULL);
	linked_iterate(list, dump, NULL);
}
