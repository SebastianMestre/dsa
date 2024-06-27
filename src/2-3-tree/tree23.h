#pragma once

typedef struct tree23_node *Tree23;

// Creates an empty 2-3 tree
Tree23 tree23_create();

// Inserts x into t
Tree23 tree23_insert(Tree23 t, int x);
