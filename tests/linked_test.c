#include <stdio.h>
#include <assert.h>

#include "../src/hashing/linked.h"
#include "../src/hashing/horner.h"

int main () {
	struct linked_t* hashTable = linked_alloc(2, &horner, 357);

	linked_insert(hashTable, "hello", (void*)0x10);
	linked_insert(hashTable, "gamer", (void*)0x30);
	linked_insert(hashTable, "world", (void*)0x20);

	assert(linked_query(hashTable, "gamer") == (void*)0x30);
	assert(linked_query(hashTable, "hello") == (void*)0x10);
	assert(linked_query(hashTable, "world") == (void*)0x20);
}
