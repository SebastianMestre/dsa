#pragma once

#include <stddef.h>

// This is the signature of a valid hash function
typedef size_t (*hash_function_t)(char const*, size_t);
