#pragma once

#include<stdbool.h>
#include<stddef.h>

typedef struct bst_head* BST;
typedef struct bst_node* Node;

struct bst_node {
	Node L;
	Node R;
	void* value;
	size_t count;
	size_t height;
};

struct bst_head {
	Node root;
	size_t size;
	bool (*comp)(void*, void*);
};

BST BST_new (bool (*comp)(void*,void*) );
void BST_insert (BST this, void* value);
void* BST_find (BST this, void* value);
size_t BST_count (BST this, void* value);
void BST_free (BST this);
void BST_free_shared (BST this);


Node Node_new (void* value);
Node Node_insert (Node this, void* value, bool(*comp)(void*,void*));
void* Node_find (Node this, void* value, bool (*comp)(void*, void*));
size_t Node_count (Node this, void* value, bool (*comp)(void*, void*));
void Node_free (Node this);
void Node_free_shared (Node this);
