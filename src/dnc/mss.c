
#if 0

// O(N log N)
int mss(int* a, int n) {
	assert(n > 0);
	if (n == 1) {
		return a[0];
	} else {
		int m = n/2;

		int max_l_suf = INT_MIN;
		for (int i = 0, s = 0; i < m; ++i)
			max_l_suf = max2(max_l_suf, s += a[m-i-1]);

		int max_r_pre = INT_MIN;
		for (int i = 0, s = 0; i < n-m; ++i)
			max_r_pre = max2(max_r_pre, s += a[m+i]);

		int m_ans = max_l_suf + max_r_pre;
		int l_ans = mss(a, m);
		int r_ans = mss(a+m, n-m);
		return max3(l_ans, m_ans, r_ans);
	}
}

#else

static int max2(int a, int b) {
	return a < b ? b : a;
}
static int max3(int a, int b, int c) {
	return max2(max2(a, b), c);
}

static void go(int *a, int n, int *out_pre, int *out_suf, int *out_sum, int *out_ans) {
	assert(n > 0);
	if (n == 1) {
		*out_pre = *out_suf = *out_sum = *out_ans = a[0];
	} else {
		int m = n/2;

		int l_pre, l_suf, l_sum, l_ans;
		go(a, m, &l_pre, &l_suf, &l_sum, &l_ans);

		int r_pre, r_suf, r_sum, r_ans;
		go(a, m, &r_pre, &r_suf, &r_sum, &r_ans);

		*out_pre = max2(l_pre, l_sum + r_pre);
		*out_suf = max2(l_suf + r_sum, r_suf);
		*out_sum = l_sum + r_sum;
		*out_ans = max3(l_ans, l_suf + r_pre, r_ans);
	}
}

// O(N)
int mss(int* a, int n) {
	int pre, suf, sum, ans;
	go(a, n, &pre, &suf, &sum, &ans);
	return ans;
}

#endif
