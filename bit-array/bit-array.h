#include <stdbool.h>
#include <stdint.h>

typedef struct BitArray {
    size_t size;
    char* arr;
} BitArray;

BitArray BitArray_make ( size_t size );

void BitArray_set ( BitArray A, size_t index, bool value );

bool BitArray_get ( BitArray A, size_t index );
