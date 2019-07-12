#include "linked.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct linked_t* linked_alloc (size_t size, hash_function_t hash, size_t seed) {
	struct linked_t* this = malloc(sizeof(*this));
	linked_init(this, size, hash, seed);
	return this;
}

void linked_init(struct linked_t *this, size_t size, hash_function_t hash,
                 size_t seed) {
	*this = (struct linked_t){
		.data = calloc(size, sizeof(*this->data)),
		.size = size,
		.hash = hash,
		.seed = seed,
	};
}

void linked_insert(struct linked_t *this, const char *key, void *value) {
	size_t hashValue = this->hash(key, this->seed);
	size_t hashIndex = hashValue % this->size;

	struct map_node_t *newNode = malloc(sizeof(*newNode));

	*newNode = (struct map_node_t){
		.next = this->data[hashIndex],
		.prev = NULL,
		.key = key,
		.value = value
	};

	if (this->data[hashIndex])
		this->data[hashIndex]->prev = newNode;

	this->data[hashIndex] = newNode;
}

void* linked_query(struct linked_t *this, const char *key) {
	size_t hashValue = this->hash(key, this->seed);
	size_t hashIndex = hashValue % this->size;

	struct map_node_t* it = this->data[hashIndex];
	for (; it; it = it->next)
		if (strcmp(key, it->key) == 0)
			break;

	return it ? it->value : NULL;
}

void* linked_remove(struct linked_t *this, const char *key) {
	size_t hashValue = this->hash(key, this->seed);
	size_t hashIndex = hashIndex % this->size;

	struct map_node_t* it = this->data[hashIndex];
	for (; it; it = it->next)
		if (strcmp(key, it->key) == 0)
			break;

	void* returnValue = NULL;

	if (it) {
		returnValue = it->value;

		if (it->prev)
			it->prev->next = it->next;
		
		if (it->next)
			it->next->prev = it->prev;

		free(it);
	}

	return returnValue;
}

