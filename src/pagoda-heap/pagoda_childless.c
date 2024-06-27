#include "pagoda.h"

#include <stdlib.h>
#include <assert.h>

/*

This file implements a variant of the pagoda data structure
without left and right child pointers.

The implementation is mostly the same but without the lines
that manipulate the child pointers.

The only big difference is pop(), where we access the two
subtrees looping from the bottom by using the D and G.

*/

struct node {
	int value;
	unsigned priority;
	struct node* d;
	struct node* g;
};

static tree get_leftmost(tree t) {
	assert(t);
	return t->g;
}

static tree get_rightmost(tree t) {
	assert(t);
	return t->d;
}

static void remove_leftmost(tree* t) {
	assert(t);
	assert(*t);
	tree root = *t;
	tree leftmost = root->g;
	if (leftmost == root) {
		*t = NULL;
	} else {
		tree parent = leftmost->g;
		root->g = parent;
		leftmost->g = leftmost;
	}
}

static void remove_rightmost(tree* t) {
	assert(t);
	assert(*t);
	tree root = *t;
	tree rightmost = root->d;
	if (rightmost == root) {
		*t = NULL;
	} else {
		tree parent = rightmost->d;
		root->d = parent;
		rightmost->d = rightmost;
	}
}

static tree make_node(int value, unsigned priority) {
	tree t = malloc(sizeof(*t));
	t->value = value;
	t->priority = priority;
	t->d = t->g = t;
	return t;
}

tree merge(tree a, tree b) {
	tree c = NULL;
	while (a && b) {
		tree p1 = get_rightmost(a);
		tree p2 = get_leftmost(b);
		if (p1->priority <= p2->priority) {
			remove_rightmost(&a);
			if (c == NULL) {
				p1->d = p1;
			} else {
				p1->d = c->d;
				c->d = p1;
			}
			c = p1;
		} else {
			remove_leftmost(&b);
			if (c == NULL) {
				p2->g = p2;
			} else {
				p2->g = c->g;
				c->g = p2;
			}
			c = p2;
		}
	}
	if (a) {
		if (c) {
			tree p1 = get_rightmost(a);
			a->d = c->d;
			c->d = p1;
		}
		c = a;
	}
	if (b) {
		if (c) {
			tree p2 = get_leftmost(b);
			b->g = c->g;
			c->g = p2;
		}
		c = b;
	}
	return c;
}

tree insert(tree t, int value, unsigned priority) {
	return merge(make_node(value, priority), t);
}

int top(tree t) {
	return t->value;
}

tree pop(tree t) {

	tree r = NULL;
	if (t->d != t) {
		tree d = t->d;
		while (d->d != t) d = d->d;
		r = d;
		r->d = t->d;
	}

	tree l = NULL;
	if (t->g != t) {
		tree g = t->g;
		while (g->g != t) g = g->g;
		l = g;
		l->g = t->g;
	}

	free(t);

	return merge(l, r);
}
