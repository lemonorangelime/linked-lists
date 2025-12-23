#include <linked.h>
#include <stddef.h>

int __test(linked_t * node) {
	if (!node) {
		return -1;
	}
	if ((*(uint64_t *) node->p) != 0x7e40abcdef) {
		return -1;
	}
	if (node->back != NULL || node->next != NULL) {
		return -1;
	}
	return 0;
}

int main() {
	uint64_t p = 0x7e40abcdef;
	linked_t * node = linked_create(&p);
	if (__test(node) == -1) {
		return -1;
	}

	linked_t * node2 = linked_clone(node, linked_clone_generic, (void *) 8);
	if (__test(node2) != 0) {
		return -1;
	}
	return 0;
}
