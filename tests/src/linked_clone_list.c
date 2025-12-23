#include <linked.h>
#include <stddef.h>
#include <stdint.h>

int main() {
	char array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	linked_t * list = linked_from_array_ptr(NULL, array, sizeof(char), 10);
	if (linked_validate(list, 10)) {
		return -1;
	}

	linked_t * list2 = linked_clone_list(list, linked_clone_generic, (void *) 1);
	if (linked_validate(list2, 10)) {
		return -1;
	}

	linked_t * node = list;
	linked_t * node2 = list2;
	while (node && node2) {
		char * p = node->p;
		char * p2 = node2->p;
		if (*p != *p2) {
			return -1;
		}
		node = node->next;
		node2 = node2->next;
	}

	if (node || node2) {
		return -1;
	}

	return (linked_validate(list, 10) | linked_validate(list2, 10)) ? -1 : 0;
}
