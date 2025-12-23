#include <linked.h>
#include <stddef.h>
#include <stdint.h>

int main() {
	char array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	linked_t * list = linked_from_array(NULL, array, sizeof(char), 10);
	if (linked_validate(list, 10)) {
		return -1;
	}

	linked_t * list2 = linked_copy_list(list);
	if (linked_validate(list2, 10)) {
		return -1;
	}

	linked_t * node = list;
	linked_t * node2 = list2;
	while (node && node2) {
		if (node->p != node2->p) {
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
