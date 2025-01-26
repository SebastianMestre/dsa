
#define MODE 1

#if MODE == 1

// The typical recursive definition of exponentiation
int pot(int b, int n) {
	if (n == 0) return 1;
	else return b * pot(b, n-1);
}

#elif MODE == 2

// A simple optimization was added for even exponents
// It is based on the following identity:
// b^(2*m) = (b^2)^m
int pot(int b, int n) {
	if (n == 0) return 1;
	else if (n%2 == 0) return pot(b*b, n/2);
	else return b * pot(n-1);
}

#elif MODE == 2

// An accumulator is added to get tail recursion
static int pot_impl(int b, int n, int a) {
	if (n == 0) return a;
	else if (n%2 == 0) return pot_impl(b*b, n/2, a);
	else return pot_impl(b, n-1, a*b);
}
int pot(int b, int n) {
	return pot_impl(b, n, 1);
}

#elif MODE == 3

// C compilers do not reliably optimize tail calls, so it is
// done manually
int pot(int b, int n) {
	int a = 1;
	while (true) {
		if (n == 0) return a;
		else if (n%2 == 0) { b = b*b; n = n/2; }
		else { n = n-1; a = a*b; }
	}
}

#elif MODE == 4

// Here the implementation is simplified and optimized by
// the observation that an iteration where `n%2!=0` is
// always followed by an iteration where `n%2==0`
int pot(int b, int n) {
	int a = 1;
	while (n != 0) {
		if (n%2 == 1) a = a*b;
		b = b*b; n = n/2;
	}
	return a;
}

#endif
