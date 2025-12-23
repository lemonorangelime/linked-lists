#include <linked.h>
#include <stdlib.h>

int generate(linked_t * node, int * i) {
	node->p = malloc(64);
	return ++*i > 10; // stop at last node
}

int main() {
	linked_t * list = linked_generate(NULL, generate, (int[]) {0});
	list = linked_deconstruct_list(list, free, NULL);
	return linked_validate(list, 0) ? -1 : 0;
}
