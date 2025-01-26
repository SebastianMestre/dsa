#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

struct list {
	int value;
	struct list *next;
};

struct list *merge(struct list *a, struct list *b) {
	if (a == NULL) return b;
	if (b == NULL) return a;
	return b->value < a->value
		? (b->next = merge(a, b->next), b)
		: (a->next = merge(a->next, b), a);
}

struct list *bisect(struct list *a, struct list *b) {
	assert(a); assert(b);
	if (!a->next || !a->next->next) {
		struct list *c = b->next;
		b->next = NULL;
		return c;
	}
	return bisect(a->next->next, b->next);

}

struct list *msort(struct list *a) {
	if (!a || !a->next) return a;
	struct list *b = bisect(a, a);
	a = msort(a);
	b = msort(b);
	return merge(a, b);
}


struct list *const nil = NULL;
struct list *cons(int value, struct list *next) {
	struct list *result = malloc(sizeof(*result));
	result->value = value;
	result->next = next;
	return result;
}

int main() {

	struct list *l = nil;

	for (int i = 0; i < 100000; ++i) {
		l = cons(rand() % 1000000, l);
	}

	clock_t start = clock();

	l = msort(l);

	clock_t finish = clock();

	printf("Time to sort: %.2fms\n", (finish - start) * (1000.0f / CLOCKS_PER_SEC));

	int cnt = 0;
	for (struct list *it = l; it != nil; it = it->next) {
		printf("%6d", it->value);
		cnt++;
		if (cnt == 24 || it->next == nil) {
			cnt = 0;
			printf("\n");
		} else {
			printf(" ");
		}
	}

}
