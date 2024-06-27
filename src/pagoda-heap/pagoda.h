#pragma once

typedef struct node* tree;

tree merge(tree a, tree b);

tree insert(tree t, int value, unsigned priority);

tree pop(tree t);

int top(tree t);
