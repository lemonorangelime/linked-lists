#include <linked.h>
#include <stddef.h>

int main() {
	linked_t * node = linked_create((void *) 0x7e40abcdef);
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
