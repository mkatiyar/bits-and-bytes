#include <iostream>
#include <algorithm>
#include <utility>

using namespace std;
void circle(int radius, int npoints)
{
	int each = npoints / 4;

	int x = 0, y = radius;
	int val = radius * radius;

	while (each--) {
		int a = (x + 1) * (x + 1) + y * y;
		int b = (x + 1) * (x + 1) + (y - 1) * (y - 1);
		int c = (x) * (x) + (y - 1) * (y - 1);

		int val1 = abs(val - a);
		int val2 = abs(val - b);
		int val3 = abs(val - c);

		int z = min(val1, min(val2, val3));

		if (z == val1) {
			x = x + 1;
			y = y;
		} else if (z == val2) {
			x = x + 1;
			y = y - 1;
		} else {
			x = x;
			y = y - 1;
		}
		printf("[%d, %d]\n", x, y);
	}
}

int main()
{
	circle (2, 32);
}
