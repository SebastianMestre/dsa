#pragma once

#include<stdbool.h>
#include<stddef.h>

typedef bool Comparator(void*, void*);
typedef struct bst_head BST;
typedef struct bst_node Node;

struct bst_node {
	Node* L;
	Node* R;
	void* value;
	size_t count;
	size_t height;
};

struct bst_head {
	Node* root;
	size_t size;
	Comparator* comp;
};

BST* BST_new (Comparator* comp);
void BST_insert (BST* this, void* value);
void* BST_find (BST* this, void* value);
size_t BST_count (BST* this, void* value);
void BST_free (BST* this);
void BST_free_shared (BST* this);


