/* Program to draw a circle given the radius using
 * midpoint circle algorithm.
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */
#include <iostream>
#include <utility>
#include <set>

using namespace std;

void circle(int radius)
{
	int x = 0, y = radius;

	int h = 1 - radius;

	set <pair <int, int>> result;

	while (y > x) {
		result.insert(make_pair(x, y));
		result.insert(make_pair(y, x));
		result.insert(make_pair(-x, y));
		result.insert(make_pair(x, -y));
		result.insert(make_pair(-x, -y));
		result.insert(make_pair(y, -x));
		result.insert(make_pair(-y, -x));
		if (h < 0) {
			h = h + 2 * x + 3;
		} else {
			h = h + 2*(x - y) + 5;
			y = y - 1;
		}
		x = x + 1;
	}

	for (auto s : result) {
		printf("[%d, %d]\n", s.first, s.second);
	}
}

int main()
{
	int radius;

	cout << "Enter the radius of circle : ";
	cin >> radius;
	circle (radius);
}
