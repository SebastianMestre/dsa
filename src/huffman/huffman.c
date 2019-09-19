#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char v;
	int c;
	struct node* l;
	struct node* r;
} node;

void heap_push (node** arr, int n, node* new_node) {
	arr[n] = new_node;
	while (n) {
		if (arr[n/2]->c > new_node->c) {
			arr[n] = arr[n/2];
			arr[n/2] = new_node;
			n /= 2;
		} else {
			break;
		}
	}
}

void heap_pop (node** arr, int n) {
	arr[0] = arr[n-1];
	int i = 0;
	while ((i * 2 + 2) < (n-1)) {
		int small_child = (arr[i*2+1]->c < arr[i*2+2]->c)
			? i*2+1
			: i*2+2;
		
		if (arr[small_child]->c < arr[i]->c) {
			arr[i] = arr[small_child];
			arr[small_child] = arr[n-1];
			i = small_child;
		} else {
			return;
		}
	}
	
	if ((i * 2 + 1) < (n-1)) {
		int small_child = i*2+1;
		
		if (arr[small_child]->c < arr[i]->c) {
			arr[i] = arr[small_child];
			arr[small_child] = arr[n-1];
		}
	}
}

node* make_huffman_tree ( char const* str ) {
	int freq [256] = {};
	
	for (char const* it = str; *it; ++it)
		freq[*it]++;

	
	node* pq [256] = {};
	int node_count = 0;
	
	for (int i = 0; i < 256; ++i) {
		if (freq[i]) {
			node* new_node = (node*)calloc(1, sizeof(node));
			*new_node = (node){
				.v = (char)i,
				.c = freq[i]
			};
			
			heap_push(pq, node_count, new_node);
			node_count++;
		}
	}

	while (node_count > 1) {
		node* l = pq[0];
		
		heap_pop(pq, node_count);
		node_count--;
		
		node* r = pq[0];
		
		heap_pop(pq, node_count);
		node_count--;
		
		node* new_node = (node*)calloc(1, sizeof(node));
		*new_node = (node){
			.c = l->c + r->c,
			.l = l,
			.r = r
		};
		
		heap_push(pq, node_count, new_node);
		node_count++;

	}

	return pq[0];
}

void print (node* t, int d) {
	if (!t) return;
	for(int i = 0; i < d; ++i) putchar('+');
	printf("[Node | c = %d, v = %c]\n", t->c, t->v ? t->v : '*');
	print(t->l, d+1);
	print(t->r, d+1);
}

int main () {
	char buffer[1024];

	scanf("%[^\n]", buffer);

	node* t = make_huffman_tree(buffer);

	print(t, 0);
}
