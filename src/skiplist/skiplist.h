#pragma once

// A deterministic append-only skiplist
//
// Internally it's a singly linked list with an extra 'skip'
// pointer which can be used to speed up searches.
//
// Internally it is an immutable data structure, so the same
// list can be safely cons'd multiple times

typedef struct skiplist_node *skiplist;

// Creates an empty skiplist -- O(1)
skiplist skiplist_create();

// New list with an extra value at the start -- O(1)
skiplist skiplist_cons(int value, skiplist next);

// List without the first value -- O(1)
skiplist skiplist_tail(skiplist list);

// The first value of the list -- O(1)
int skiplist_value(skiplist list);

// The amount of values in the list -- O(log N)
int skiplist_length(skiplist list);

// The index-th value of the list -- O(log N)
// Where N = skiplist_length(list)
// index must be a valid index.
int skiplist_at(skiplist list, int index);

// Returns 0 iff value is not in the list -- O(log N)
// Where N = skiplist_length(list)
int skiplist_contains(skiplist list, int value);
