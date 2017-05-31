/* Given the co-ordinates of the buildings and the height
 * draw the skyline of the view.
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <set>

using namespace std;

vector <vector <int>> read_input(void)
{
	int nbldgs;

	cout << "Number of buildings ? : ";
	cin >> nbldgs;

	vector <vector <int>> buildings;

	int x1, x2, h;

	while (nbldgs--) {
		cout << "Enter the dimensions of building : [x1, x2, h] ? ";
		cin >> x1 >> x2 >> h;
		buildings.emplace_back(vector <int>{x1, x2, h});
	}

	return buildings;
}

bool compare(pair <int, int>&a, pair <int, int>&b) {
	if (a.first == b.first) {
		return a.second > b.second;
	}
	return a.first < b.first;
}

void print_skyline(vector <pair <int, int>>& result)
{
	/* Final results */
	cout << "\nSkyline co-ordinates are [x, h] :\n";
	for (auto r : result) {
		printf("{%d, %d} ", r.first, r.second);
	}
	cout << endl;
}

void draw_skyline(vector <vector <int>>& buildings)
{
	vector <pair <int, int>> result;
	vector <pair <int, int>> endpoints;

	/* Gather the endpoints as pairs of x-axis and height
	 * Negative height means its an end of a building.
	 */
	for (auto b : buildings) {
		endpoints.emplace_back(make_pair(b[0], b[2]));
		endpoints.emplace_back(make_pair(b[1], -b[2]));
	}

	/* Sort them based on x-axis. If same x values, then positive height
	 * gets preference.
	 */
	sort(endpoints.begin(), endpoints.end(), compare);

	/* Need a sorted list based on heights */
	multiset<int, std::greater<int>> heights;

	/* Now iterate the endpoints and keep recording the maximum height */
	for (auto e : endpoints) {
		if (e.second > 0) {
			/* Start of a building */
			if (heights.empty() || (*heights.begin()) < e.second) {
				result.emplace_back(e);
			}
			heights.insert(e.second);
		} else {
			/* End of a building, remove our building's height */
			heights.erase(heights.find(-e.second));

			if (heights.empty()) {
				result.emplace_back(make_pair(e.first, 0));
			} else if ((*heights.begin()) < -e.second) {
				result.emplace_back(make_pair(e.first, -e.second));
			}
		}
	}

	print_skyline(result);
}

int main()
{
	vector <vector <int>> buildings;

	buildings = read_input();
	draw_skyline(buildings);
}
