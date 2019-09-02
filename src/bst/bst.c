#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "bst.h"


Node Node_rotate_L (Node this);
Node Node_rotate_R (Node this);


BST BST_new (bool (*comp)(void*,void*) ) {
	BST this = malloc(sizeof(*this));

	this->root = NULL;
	this->size = 0;
	this->comp = comp;

	return this;
}

void BST_insert (BST this, void* value) {
	this->size++;
	this->root = Node_insert(this->root, value, this->comp);
}

void* BST_find (BST this, void* value) {
	return Node_find(this->root, value, this->comp);
}

size_t BST_count (BST this, void* value) {
	return Node_count(this->root, value, this->comp);
}

void BST_free (BST this) {
	Node_free(this->root);
	free(this);
}

void BST_free_shared (BST this) {
	Node_free_shared(this->root);
	free(this);
}



Node Node_new (void* value) {
	Node this = malloc(sizeof(*this));

	this->value = value;
	this->L = NULL;
	this->R = NULL;
	this->count = 0;
	this->height = 1;

	return this;
}

Node Node_insert (Node this, void* value, bool(*comp)(void*,void*)) {
	if (this == NULL)
		return Node_new(value);

	if (!(*comp)(this->value, value) && !(*comp)(value, this->value)) {
		this->count++;
		return this;
	}

	if ((*comp)(value, this->value)) {
		this->L = Node_insert(this->L, value, comp);
	} else {
		this->R = Node_insert(this->R, value, comp);
	}


	size_t height_l = this->L ? this->L->height : 0;
	size_t height_r = this->R ? this->R->height : 0;

	this->height = (height_l < height_r ? height_r : height_l) + 1;

	if (abs(height_l - height_r) > 1) {
		if (height_l < height_r) {
			return Node_rotate_L(this);
		} else {
			return Node_rotate_R(this);
		}
	} else {
		return this;
	}
}

Node Node_search(Node this, void* value, bool (*comp)(void*, void*)) {
	if(this == NULL) return NULL;

	if(!(*comp)(this->value, value) && !(*comp)(value, this->value))
		return this;

	if((*comp)(value, this->value))
		return Node_search(this->L, value, comp);
	else
		return Node_search(this->R, value, comp);
}

void* Node_find (Node this, void* value, bool (*comp)(void*, void*)) {
	Node result = Node_search(this, value, comp);

	return result ? result->value : NULL;
}

size_t Node_count (Node this, void* value, bool (*comp)(void*, void*)) {
	Node result = Node_search(this, value, comp);

	return result ? result->count : 0;
}

void Node_free (Node this) {
	if(!this) return;

	free(this->value);
	Node_free(this->L);
	Node_free(this->R);

	free(this);
}

void Node_free_shared (Node this) {
	if(!this) return;

	Node_free_shared(this->L);
	Node_free_shared(this->R);

	free(this);
}



Node Node_rotate_L (Node this) {
	Node move_up = this->R;

	Node temp = move_up->L;
	move_up->L = this;
	this->R = temp;

	size_t height_l = this->L ? this->L->height : 0;
	size_t height_r = this->R ? this->R->height : 0;

	this->height = (height_l < height_r ? height_r : height_l) + 1;

	height_l = move_up->L ? move_up->L->height : 0;
	height_r = move_up->R ? move_up->R->height : 0;

	move_up->height = (height_l < height_r ? height_r : height_l) + 1;

	return move_up;
}

Node Node_rotate_R (Node this) {
	Node move_up = this->L;

	Node temp = move_up->R;
	move_up->R = this;
	this->L = temp;

	size_t height_l = this->L ? this->L->height : 0;
	size_t height_r = this->R ? this->R->height : 0;

	this->height = (height_l < height_r ? height_r : height_l) + 1;

	height_l = move_up->L ? move_up->L->height : 0;
	height_r = move_up->R ? move_up->R->height : 0;

	move_up->height = (height_l < height_r ? height_r : height_l) + 1;

	return move_up;
}
