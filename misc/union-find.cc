/* Union find alogrithm. Used to detect if two elements
 * belong to the same set. This program inserts random elements
 * to different sets and then prints out disjoint sets
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


int find_set(vector <int>& Set, int element)
{
	if (Set[element] == -1) return element;

	return find_set(Set, Set[element]);
}

/* Add two elements to the same set */
void Union(vector <int>&Set, int elem1, int elem2)
{
	int x = find_set(Set, elem1);
	int y = find_set(Set, elem2);

	/* Not already in the same set */
	if (x != y) {
		Set[x] = y;
	}
}

int main()
{
	int n;
	cout << "Enter the number of set elements :";
	cin >> n;

	vector <int> Sets(n, -1);
	srand(time(NULL));

	cout << "Inserting elements in set randomly :\n";
	int tests = random() % (n / 2);
	while (tests--) {
		int x = random() % n;
		int y = random() % n;
		printf("Adding %d to set of %d\n", x, y);
		Union(Sets, x, y);
	}

	cout << "Total disjoint sets :\n";
	unordered_map <int, vector <int>> M;
	for (int i = 0; i < n; i++) {
		int s = find_set(Sets, i);
		M[s].emplace_back(i);
	}
	for (auto m : M) {
		printf("[");
		for (auto x : m.second) {
			cout << x << " ";
			if (m.first == -1) {
				cout << "]\n [";
			}
		}
		printf("]\n");
	}
}
