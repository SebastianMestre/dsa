
#define MOD 1000000007

static int add(int x, int y) {
	int z = x + y;
	return z - MOD * (z >= MOD);
}

static int mul(int x, int y) {
	return (int)((long long)x * y % MOD);
}

static void go(int b, int n, int *out_p, int *out_s) {
	if (n == 0) {
		*out_p = 1;
		*out_s = 0;
	} else {
		int p, s;
		if (n%2 == 1) {
			go(b, n-1, &p, &s);
			*out_p = mul(b, p);
			*out_s = add(1, mul(b, s));
		} else {
			go(b, n/2, &p, &s);
			*out_p = mul(p, p);
			*out_s = add(s, mul(p, s));
		}
	}
}

int geom(int b, int n) {
	int p, s;
	go(b, n, &p, &s);
	return s;
}
