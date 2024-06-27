#include "tree23.h"

#include <stdlib.h>
#include <assert.h>

#define CENTINEL ((Tree23)1)

// 2-3 tree node
// 2-nodes have right=CENTINEL
struct tree23_node {
	int k1, k2;
	Tree23 left, middle, right;
};

Tree23 tree23_create() {
	return NULL;
}

// Returns the number of children of a node
static int node_type(Tree23 t) {
	assert(t != NULL);
	return t->right == CENTINEL ? 2 : 3;
}

// Creates a 2-node
static Tree23 create_2_node(int x, Tree23 l, Tree23 r) {
	Tree23 node = malloc(sizeof(*node));
	node->k1 = x;
	node->left = l;
	node->middle = r;
	node->right = CENTINEL;
	return node;
}

// Inserts x into t
// - If the root node overflows, it returns 1 and writes the pieces needed to
//   construct a 2-node for the root on out_x, out_l and out_r
// - If the root does not overflow, it returns 0 and writes NULL to out_l and out_r
// calling insert_impl on NULL is considered an overflow
static int insert_impl(Tree23 t, int x, int* out_x, Tree23* out_l, Tree23* out_r) {

	*out_l = NULL;
	*out_r = NULL;
	int overflow = 0;

	if (t == NULL) {
		*out_x = x;
		overflow = 1;
	} else if (node_type(t) == 2) {

		Tree23 l, r;
		if (x < t->k1) {
			if (insert_impl(t->left, x, &x, &l, &r)) {
				t->k2 = t->k1;
				t->k1 = x;
				t->right = t->middle;
				t->left = l;
				t->middle = r;
			}
		} else if (t->k1 < x) {
			if (insert_impl(t->middle, x, &x, &l, &r)) {
				t->k2 = x;
				t->middle = l;
				t->right = r;
			}
		}

	} else {

		Tree23 l, r;
		if (x < t->k1) {
			if (insert_impl(t->left, x, &x, &l, &r)) {
				*out_l = create_2_node(x, l, r);
				*out_x = t->k1;
				*out_r = create_2_node(t->k2, t->middle, t->right);
				free(t);
				overflow = 1;
			}
		} else if (t->k1 < x && x < t->k2) {
			if (insert_impl(t->middle, x, &x, &l, &r)) {
				*out_l = create_2_node(t->k1, t->left, l);
				*out_x = x;
				*out_r = create_2_node(t->k2, r, t->right);
				free(t);
				overflow = 1;
			}
		} else if (t->k2 < x) {
			if (insert_impl(t->right, x, &x, &l, &r)) {
				*out_l = create_2_node(t->k1, t->left, t->middle);
				*out_x = t->k2;
				*out_r = create_2_node(x, l, r);
				free(t);
				overflow = 1;
			}
		}
	}

	return overflow;
}

Tree23 tree23_insert(Tree23 t, int x) {
	Tree23 l, r;
	if (insert_impl(t, x, &x, &l, &r))
		t = create_2_node(x, l, r);
	return t;
}
