#include "skiplist.h"

#include <stdlib.h>

/*

A singly linked list augmented with some 'skip' pointers to
speed up searches.

During cons(l, x), two consecutive skips of the same size
are combined into a skip of double the size, so the new
node's skip pointer will be l->skip->skip. Otherwise, a skip
of size 1 is used, so the new node will just point to l.

Skip pointers on a list with 8 elements:

 ________________________________
/ ____________   ____________    \
|/            \ /            \    \
0 <- A <- B    C <- D <- E    F    G <- H

The data structure is fully immutable, so it can also be
implemented in pure functional languages.

*/

struct skiplist_node {
	int value;
	int skip_size;
	skiplist next;
	skiplist skip;
};

skiplist skiplist_create() {
	return NULL;
}

skiplist skiplist_tail(skiplist list) {
	return list->next;
}

int skiplist_value(skiplist list) {
	return list->value;
}

skiplist skiplist_cons(int value, skiplist next) {
	skiplist result = malloc(sizeof(*result));
	result->value = value;
	result->next = next;

	if (next == NULL || next->skip == NULL || next->skip_size != next->skip->skip_size) {
		result->skip_size = 1;
		result->skip = next;
	} else {
		result->skip = next->skip->skip;
		result->skip_size = 1 + next->skip_size + next->skip->skip_size;
	}

	return result;
}

int skiplist_at(skiplist list, int index) {
	while (index != 0) {
		if (index >= list->skip_size) {
			index -= list->skip_size;
			list = list->skip;
		} else {
			index -= 1;
			list = list->next;
		}
	}
	return list->value;
}

int skiplist_length(skiplist list) {
	int acc = 0;
	while (list != NULL) {
		acc += list->skip_size;
		list = list->skip;
	}
	return acc;
}

int skiplist_contains(skiplist list, int value) {
	skiplist end = NULL;
	while (list != end) {
		if (value == list->value) {
			return 1;
		} else if (list->skip && list->skip->value <= value) {
			list = list->skip;
		} else {
			end = list->skip;
			list = list->next;
		}
	}
	return 0;
}
