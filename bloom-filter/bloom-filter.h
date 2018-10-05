#include <stdint.h>
#include <stdbool.h>

#include "../bit-array/bit-array.h"


typedef struct BloomFilter{
    BitArray data;
    size_t hash_count;
    size_t (*hash)(const char*, size_t, size_t);
} BloomFilter;

BloomFilter BloomFilter_make (size_t size, size_t hash_count);

void BloomFilter_insert ( BloomFilter this, const char* val );

bool BloomFilter_query ( BloomFilter this, const char* val );
