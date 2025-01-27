#include <linked.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>

typedef struct {
	int i;
	int max;
} generator_state_t;

int dump(linked_t * node, void * pass) {
	printf("- %p <= %p(%p) => %p\n", node->back, node, node->p, node->next);
}

int generate(linked_t * node, void * pass) {
	generator_state_t * state = pass;
	node->p = (void *) ++state->i;
	return state->i == state->max + 1; // stop at last node + 1
}

int main() {
	generator_state_t state = {0, 10}; // generate 10 nodes
	linked_t * list = linked_generate(NULL, generate, &state);
	linked_iterate(list, dump, NULL);
}
