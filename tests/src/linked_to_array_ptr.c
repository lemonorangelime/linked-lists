#include <linked.h>
#include <stddef.h>
#include <stdint.h>

int main() {
	char array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	linked_t * list = linked_from_array(NULL, array, sizeof(char), 10);

	if (linked_validate(list, 10)) {
		return -1;
	}

	char * ptrs[10];
	list = linked_to_array_ptr(list, ptrs, sizeof(char *), 10);

	for (int i = 0; i < 10; i++) {
		if (array[i] != *ptrs[i]) {
			return -1;
		}
	}

	return linked_validate(list, 10) ? -1 : 0;
}
