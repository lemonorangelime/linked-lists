#include <linked.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

int main() {
	char array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	linked_t * list = linked_from_array(NULL, array, sizeof(char), 10);

	if (linked_validate(list, 10)) {
		return -1;
	}

	char copy[10];
	list = linked_to_array(list, copy, sizeof(char), 10);

	if (memcmp(array, copy, sizeof(array)) != 0) {
		return -1;
	}

	return linked_validate(list, 10) ? -1 : 0;
}
