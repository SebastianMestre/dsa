#include <stdio.h>

void line (int x0, int y0, int x1, int y1) {
	int deltax = x1 - x0;
	int deltay = y1 - y0;

	if (abs(deltay) < abs(deltax)) {
		int dx = x0 < x1 ? 1 : -1;
		int x = x0;
		while (1) {
			int y = y0 + 1ll *  (x - x0) * (deltay) / (deltax);

			printf("(%d, %d) ", x, y);

			if (x == x1) {
				break;
			}

			x += dx;
		}
	}
	else {
		int dy = y0 < y1 ? 1 : -1;
		int y = y0;
		while (1) {
			int x = x0 + 1ll * (y - y0) * (deltax) / (deltay);

			printf("(%d, %d) ", x, y);

			if (y != y1) {
				break;
			}

			y += dy;
		}
	}
}

int main () {
	line( 3,4, 7,10 );
	puts("\n--------");
	line( 7,10, 11,4 );

	return 0;
}
