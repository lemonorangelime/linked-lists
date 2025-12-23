#include <linked.h>
#include <stddef.h>
#include <stdint.h>

int main() {
	char array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	char array2[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
	linked_t * list = linked_from_array(NULL, array, sizeof(char), 10);

	if (linked_validate(list, 10)) {
		return -1;
	}

	linked_t * list2 = linked_from_array(list2, array2, sizeof(char), 10);

	if (linked_validate(list2, 10)) {
		return -1;
	}

	list = linked_stitch(list, list2);
	linked_dump(list);
	return linked_validate(list, 20) ? -1 : 0;
}
