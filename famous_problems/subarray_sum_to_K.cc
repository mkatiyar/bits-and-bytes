/* Given a sum value 'K', print out the indexes of the
 * continuous subarray whose sum equals to K.
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */


#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

void print_vector(vector <int>& nums)
{
	printf("[");
	for (auto n : nums) {
		cout << n << " ";
	}
	printf("]\n");
}

/* This only works when the integers in the array are
 * non-negative. Keep a sliding window and print it once
 * we find the sum in the window is equal to the desired number.
 */
void find_non_negative_sum(vector <int>& nums, int k)
{
	int l = 0, sum = 0;
	bool found = false;

	for (int i = 0; i < nums.size(); i++) {
		sum += nums[i];
		if (sum >= k) {
			while (sum > k) sum -= nums[l++];
			if (sum == k) {
				found = true;
				printf("Indexes %d to %d sum to %d\n",
					l + 1, i + 1, k);
			}
		}
	}

	if (!found) {
		cout << "Sum doesn't exist in any subarray\n";
	}
	return;
}

/* Find the indexes which sum total to given K. The array can have
 * negative integers too. Previous algorithm doesn't work because just
 * checking that the sum > K to stop the window isn't sufficient. We could
 * get a negative number which can sum to K.
 *
 * What is required is indexes [i, j] such that (sum[j] - sum[i - 1] == K)
 * where sum[i] is the prefix sum of index i. So when we are at sum[i], we need
 * to know if there was an index before this index which had the value (sum[i] - K)
 * because of above equation. To efficiently find that index, we just store all
 * the prefix sums in a hash.
 */
int find_negative_sum(vector <int>& nums, int K)
{
	int sum = 0;
	unordered_map <int, int> map;
	bool found = false;

	map[0] = 1;

	for (int i = 0; i < nums.size(); i++) {
		sum += nums[i];
		if (map.find(sum - K) != map.end()) {
			found = true;
			printf("Indexes %d to %d sum to %d\n",
					map[sum - K] + 1, i + 1, K);
		}
		map[sum] = i + 1;
	}
	if (!found) {
		cout << "Sum doesn't exist in any subarray\n";
	}
}

int main()
{
	int nelements;
	cout << "Enter the number of elements in array :";
	cin >> nelements;

	vector <int> nums;

	srand(time(NULL));
	for (int i = 0; i < nelements; i++) {
		nums.emplace_back(rand() % 25);
	}

	print_vector(nums);

	int k;
	cout << "\nEnter the target sum : ";
	cin >> k;

	find_non_negative_sum(nums, k);

	cout << "\nTrying with negative numbers too.\n";
	for (int i = 0; i < nums.size(); i++) {
		nums[i] *= (rand() % 2 ? -1 : 1);
	}

	print_vector(nums);
	cout << "\nEnter the target sum : ";
	cin >> k;
	find_negative_sum(nums, k);
}
