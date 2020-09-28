#include <vector>

#include <cassert>

template<typename T>
struct FreeList {
	struct Node {
		T val;
		int next;
		bool free;
	};

	int first_free = -1;
	std::vector<Node> m_data;

	int alloc() {
		if (first_free == -1) {
			int result = m_data.size();
			m_data.resize(m_data.size() + 1);
			m_data[result].free = false;
			m_data[result].next = -1;
			return result;
		} else {
			int result = first_free;
			first_free = m_data[first_free].next;
			m_data[result].free = false;
			return result;
		}
	}

	void free(int i) {
		assert(i >= 0);
		assert(i < m_data.size());
		assert(!m_data[i].free);

		m_data[i].free = true;
		m_data[i].next = first_free;
		first_free = i;
	}
};
