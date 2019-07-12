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

void BloomFilter_insert ( BloomFilter *this, const char* val ) {
    for (int i = 0; i < this->hash_count; ++i) {
        size_t seed = 20 + i * 3;
		size_t hashValue = this->hash(val, seed);
		size_t hashIndex = hashValue % this->data.size;
        BitArray_set(this->data, hashIndex, true);
    }
}

bool BloomFilter_query ( BloomFilter *this, const char* val ) {
    for (int i = 0; i < this->hash_count; ++i) {
        size_t seed = 20 + i * 3;
		size_t hashValue = this->hash(val, seed);
		size_t hashIndex = hashValue % this->data.size;
        if (!BitArray_get(this->data, hashIndex))
            return false;
    }
    return true;
}
