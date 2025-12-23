#include <linked.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

// filter out odd nodes
int discriminator(linked_t * node, void * pass) {
	return node->uint32 & 1;
}

int main() {
	char array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	linked_t * list = linked_from_array(NULL, array, sizeof(char), 10);

	if (linked_validate(list, 10)) {
		return -1;
	}

	printf("Removing odd nodes...\n");

	list = linked_discriminate(list, discriminator, NULL);
	return linked_validate(list, 5) ? -1 : 0;
}
