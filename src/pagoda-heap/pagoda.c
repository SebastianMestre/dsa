#include "pagoda.h"

#include <stdlib.h>
#include <assert.h>

/*

The pagoda data structure is a simple way to implement
priority queues with O(height) merge operation.

A pagoda is similar to a heap, but each node is augmented
with two additional pointers: D and G.

On any node that is a left child, G points to its parent. On
nodes that are not left children, G points to the leftmost
node on the subtree. Thus, G forms circular linked lists
over the nodes on the leftmost path of each subtree.

D follows a similar structure, but on the right side of the
each subtree.

Interestingly the D and G pointers are enough to encode the
tree structure (e.g. we can find the left child of a node by
traversing the circular list formed by G), so it is possible
to implement a pagoda without storing the left and right
pointers explicitly. The file `pagoda_childless.c` shows
this approach.

*/

struct node {
	int value;
	unsigned priority;
	struct node* l;
	struct node* r;
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
		parent->l = NULL;
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
		parent->r = NULL;
		rightmost->d = rightmost;
	}
}

static tree make_node(int value, unsigned priority) {
	tree t = malloc(sizeof(*t));
	t->value = value;
	t->priority = priority;
	t->l = t->r = NULL;
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
			p1->r = c;
			if (c == NULL) {
				p1->d = p1;
			} else {
				p1->d = c->d;
				c->d = p1;
			}
			c = p1;
		} else {
			remove_leftmost(&b);
			p2->l = c;
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
			p1->r = c;
			a->d = c->d;
			c->d = p1;
		}
		c = a;
	}
	if (b) {
		if (c) {
			tree p2 = get_leftmost(b);
			p2->l = c;
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

static void remove_children(tree t) {
	assert(t);
	tree l = t->l;
	tree r = t->r;
	if (l) l->g = t->g;
	if (r) r->d = t->d;
	t->l = t->r = NULL;
	t->d = t->g = t;
}

tree pop(tree t) {
	tree l = t->l;
	tree r = t->r;
	remove_children(t);
	free(t);
	return merge(l, r);
}
