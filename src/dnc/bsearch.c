int* lower_bound(int *a, int n, int x) {
	while (n != 0) {
		int m = n/2;
		if (a[m] < x) {
			a += m+1;
			n -= m+1;
		} else {
			n = m;
		}
	}
	return a;
}
