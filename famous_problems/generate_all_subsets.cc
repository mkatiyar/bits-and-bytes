/* Given an array of integers, generate all possible distinct subsets.
 *
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */
#include <iostream>
#include <vector>
using namespace std;

void print_vector(vector <int>& nums)
{
	printf("[");
	for (auto n : nums) {
		printf("%d, ", n);
	}
	printf("]\n");
}

int main()
{
	vector <int> input;
	int nelements;

	cout << "Enter the size of input array : ";
	cin >> nelements;

	for (int i = 0; i < nelements; i++) {
		int tmp;
		cin >> tmp;
		input.emplace_back(tmp);
	}


	/* Generate all distinct subsets */
	vector <vector <int>> result = {{}};
	int size = 0;

	sort(input.begin(), input.end());

	for (int i = 0; i < nelements; i++) {
		int start = (i > 0 && input[i] == input[i - 1]) ? size : 0;
		size = result.size();
		for (int j = start; j < size; j++) {
			auto tmp = result[j];
			tmp.emplace_back(input[i]);
			result.emplace_back(tmp);
		}
	}


	/* Print the output */
	cout << "All unique subsets are :\n";
	for (auto r : result) {
		print_vector(r);
	}
}
