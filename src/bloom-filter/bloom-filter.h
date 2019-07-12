#pragma once

#include <stddef.h>
#include <stdbool.h>

#include "../bit-array/bit-array.h"

#include "../hashing/horner.h"

typedef struct BloomFilter{
    BitArray data;
    size_t hash_count;
    hash_function_t hash;
} BloomFilter;

BloomFilter BloomFilter_make (size_t size, size_t hash_count);

void BloomFilter_insert ( BloomFilter *this, const char* val );

bool BloomFilter_query ( BloomFilter *this, const char* val );
