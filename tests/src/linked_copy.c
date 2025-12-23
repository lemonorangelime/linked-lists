#include <linked.h>
#include <stddef.h>

int __test(linked_t * node) {
	if (!node) {
		return -1;
	}
	if (node->p != (void *) 0x7e40abcdef) {
		return -1;
	}
	if (node->back != NULL || node->next != NULL) {
		return -1;
	}
	return 0;
}

int main() {
	linked_t * node = linked_create((void *) 0x7e40abcdef);
	if (__test(node) == -1) {
		return -1;
	}
	linked_t * node2 = linked_copy(node);
	if (__test(node2) != 0) {
		return -1;
	}
	return 0;
}
