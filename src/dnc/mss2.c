
// O(N)
int mss(int* a, int n, int* pre, int* suf, int* sum) {
	assert(n > 0);
	if (n == 1) {
		return *pre = *suf = *sum = a[0];
	} else {
		int m = n/2;

		int l_pre, l_suf, l_sum;
		int l_ans = mss(a, m, &l_pre, &l_suf, &l_sum);

		int r_pre, r_suf, r_sum;
		int r_ans = mss(a+m, n-m, &r_pre, &r_suf, &r_sum);

		*pre = max(l_pre, l_sum + r_pre);
		*suf = max(l_suf + r_sum, r_suf);
		*sum = l_sum + r_sum;
		return max3(l_ans, l_suf + r_pre, r_ans);
	}
}

