#include <linked.h>
#include <stddef.h>
#include <stdint.h>

int main() {
	char array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	char array2[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	linked_t * list = linked_from_array_ptr(NULL, array, sizeof(char), 10);

	if (linked_validate(list, 10)) {
		return -1;
	}

	list = linked_from_array_ptr(list, array2, sizeof(char), 10);
	linked_dump(list);

	char * ptrs[20];
	linked_to_array(list, ptrs, sizeof(char *), 20);
	for (int i = 0; i < 10; i++) {
		if (*ptrs[i] != array[i]) {
			return -1;
		}
	}
	for (int i = 0; i < 10; i++) {
		if (*ptrs[10 + i] != array2[i]) {
			return -1;
		}
	}

	return linked_validate(list, 20) ? -1 : 0;
}
