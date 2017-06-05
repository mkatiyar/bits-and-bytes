/* Given an array and a target number, return
 * whether that number exists or not.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool bsearch(vector <int>& nums, int start, int end, int target)
{
	int mid;

	while (start <= end) {
		mid = start + (end - start) / 2;

		if (nums[mid] == target) return true;

		if (nums[mid] > target) {
			end = mid - 1;
		} else {
			start = mid + 1;
		}
	}

	return false;
}

int main()
{
	int n;
	cout << "Enter size of array : ";
	cin >> n;

	vector <int> nums(n);
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	int target;
	cout << "Enter target number : ";
	cin >> target;

	sort(nums.begin(), nums.end());

	printf("Target number does %sexist\n",
		bsearch(nums, 0, n - 1, target) ?  "" : "not ");

	return 0;
}
