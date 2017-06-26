/* 3-way partitioning or the dutch national flag problem
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */

#include <iostream>
#include <vector>

using namespace std;

enum values {
	LOW,
	MID,
	HIGH
};

void three_way_partition(vector <int>&nums, int midvalue)
{
	int i = 0, j = 0, end = nums.size() - 1;

	while (j <= end) {
		if (nums[j] < midvalue) {
			swap(nums[i], nums[j]);
			i++;
			j++;
		} else if (nums[j] > midvalue) {
			swap(nums[j], nums[end]);
			end--;
		} else {
			j++;
		}
	}
}

/* Create the initial array with random 0,1,2 values */
void populate_array(vector <int>&nums, int size)
{
	int i = 0;

	while (size--) {
		nums.emplace_back(rand() % (HIGH + 1));
	}
}

/* Print the array */
void print_array(vector <int>&nums)
{
	printf("[");
	for (auto n : nums) {
		cout << n << " ";
	}
	printf("]\n");
}


int main()
{
	vector <int> nums;
	int n;

	cout << "Enter the size of array :";
	cin >> n;

	srand(time(NULL));
	populate_array(nums, n);

	cout << "Initial array : ";
	print_array(nums);

	cout << "After partitioning : ";
	three_way_partition(nums, MID);
	print_array(nums);
}
