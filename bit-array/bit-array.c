#include "bit-array.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

BitArray BitArray_make ( size_t size ) {
    size_t n_bytes = ( size / 8 );
    if( size % 8 ) n_bytes++;
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
