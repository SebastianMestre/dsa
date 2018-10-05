#include "bloom-filter.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    size_t size;
    char* arr;
} BitArray;

BitArray BitArray_make ( size_t size ) {
    int n_bytes = ( size / 8 ) + 1;
    if( size % 8 == 0 ) n_bytes--;
    printf( "%d %d\n", size, n_bytes );
    BitArray ret = { size, malloc(n_bytes) };
    memset( ret.arr, 0, n_bytes );
    return ret;
}



void BitArray_set ( BitArray A, size_t index, bool value ) {
    if ( value == true ) A.arr[index/8] |=  ( 1 << (index%8) );
    else                 A.arr[index/8] &= ~( 1 << (index%8) );
}

bool BitArray_get ( BitArray A, size_t index ) {
    return A.arr[index/8] & (1<<(index % 8));
}

// Bloom filter

size_t horner ( const char* val, size_t seed, size_t size ) {
    size_t result = 0;
    for (size_t i = 0; val[i]; ++i)
        result = (result * seed + val[i]) % size;
    return result;
}

typedef struct {
    BitArray data;
    size_t hash_count;
    size_t (*hash)(const char*, size_t, size_t);
} BloomFilter;

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

int main ( void ) {

    BloomFilter pepe = BloomFilter_make(10, 6);

    BloomFilter_insert(pepe, "hola");
    BloomFilter_insert(pepe, "antonelli");
    BloomFilter_insert(pepe, "mestre");

    printf("%d\n", BloomFilter_query(pepe, "hola"));
    printf("%d\n", BloomFilter_query(pepe, "antonelli"));
    printf("%d\n", BloomFilter_query(pepe, "mestre"));
    printf("%d\n", BloomFilter_query(pepe, "nam"));
    printf("%d\n", BloomFilter_query(pepe, "pennice"));
    printf("%d\n", BloomFilter_query(pepe, "cori"));



    return 0;
}
