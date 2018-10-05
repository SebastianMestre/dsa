#include "bloom-filter.h"

#include <stddef.h>
#include <stdbool.h>

#include "../bit-array/bit-array.h"
#include "../hashing/horner.h"

BloomFilter BloomFilter_make (size_t size, size_t hash_count) {
    return (BloomFilter){
        .data = BitArray_make(size),
        .hash_count = hash_count,
        .hash = &horner
    };
}

void BloomFilter_insert ( BloomFilter this, const char* val ) {
    for (int i = 0; i < this.hash_count; ++i) {
        size_t seed = 20 + i * 3;
        BitArray_set(this.data, (*this.hash)(val, seed, this.data.size), true);
    }
}

bool BloomFilter_query ( BloomFilter this, const char* val ) {
    for (int i = 0; i < this.hash_count; ++i) {
        size_t seed = 20 + i * 3;
        if (!BitArray_get(this.data, (*this.hash)(val, seed, this.data.size)))
            return false;
    }
    return true;
}
