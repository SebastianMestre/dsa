#pragma once

#include "hashing.h"

struct map_node_t {
	struct map_node_t* next;
	struct map_node_t* prev;
	const char* key;
	void* value;
};

struct linked_t {
	struct map_node_t** data;
	size_t size;
	hash_function_t hash;
	size_t seed;
};

struct linked_t* linked_alloc (size_t size, hash_function_t hash, size_t seed);
void linked_init (struct linked_t* this, size_t size, hash_function_t hash, size_t seed);
void linked_insert( struct linked_t *this, const char *key, void *value);
void* linked_query(struct linked_t *this, const char *key);
void* linked_remove(struct linked_t *this, const char *key);
