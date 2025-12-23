#include <linked.h>
#include <stddef.h>

int generate(linked_t * node, int * i) {
	node->int32 = ++*i;
	return *i > 10; // stop at last node
}

int main() {
	linked_t * list = linked_generate(NULL, generate, (int[]) {0});
	return linked_validate(list, 10) ? -1 : 0;
}
