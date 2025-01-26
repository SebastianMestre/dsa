
#define BITS_PER_STEP 4

typedef struct htrie *htrie;
struct htrie {
	void *children[1 << BITS_PER_STEP];
};

htrie create() {
	return calloc(1, sizeof(struct trie));
}

htrie *walk(htrie t, uint64_t key, int create_missing) {
	assert(t != NULL);

	htrie *p = &t;

	int const steps = (64 + BITS_PER_STEP - 1) / BITS_PER_STEP;
	for (int i = 0; i < steps; ++i) {
		uint64_t idx = key >> (64 - BITS_PER_STEP);

		if (*p == NULL) {
			if (create_missing) {
				*p = create();
			} else {
				return NULL;
			}
		}

		p = &(*p)->children[idx];
	}

	return p;
}

int insert(htrie t, uint64_t key, void* value) {
	htrie* p = walk(t, key, 1);
	if (*p == NULL) {
		*p = value;
		return 1;
	} else {
		return 0;
	}
}

void* query(htrie t, uint64_t key) {
	htrie* p = walk(t, key, 0);
	if (p == NULL) {
		return NULL;
	}
}
