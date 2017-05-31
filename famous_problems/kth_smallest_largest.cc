/* Given an unsorted array, find the Kth smallest/largest element
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */
#include <vector>
#include <iostream>

using namespace std;

enum rank {
	LARGEST,
	SMALLEST
};

/* Compare function based on whether we want kth largest or smallest */
bool compare(int x, int y, int operation)
{
	if (operation == LARGEST) {
		return x > y;
	} else {
		return x < y;
	}
}

/* Do a quickselect partition of the array based on a random pivot point */
int partition(vector <int>& nums, int begin, int end, int operation)
{
	/* Get a random pivot */
	int pidx = begin + random() % (end - begin + 1);
	int pivot = nums[pidx];

	swap(nums[pidx], nums[end]);

	int j = begin;

	for (int i = begin; i < end; i++) {
		if (compare(nums[i], pivot, operation)) {
			swap(nums[i], nums[j]);
			j++;
		}
	}

	swap(nums[j], nums[end]);

	return j;
}

/* Main function to find the rank */
int find_ranking(vector <int> &nums, int k, int begin, int end, int operation)
{
	int part = partition(nums, begin, end, operation);

	int distance = part - begin + 1;

	if (distance == k) {
		return nums[part];
	} else if (distance > k) {
		return find_ranking(nums, k, begin, part - 1, operation);
	} else {
		return find_ranking(nums, k - distance, part + 1, end, operation);
	}
}

int find_kth_largest(vector <int>& nums, int k)
{
	return find_ranking(nums, k, 0, nums.size() - 1, LARGEST);
}

int find_kth_smallest(vector <int>& nums, int k)
{
	return find_ranking(nums, k, 0, nums.size() - 1, SMALLEST);
}

vector <int> read_input()
{
	int n, num;
	vector <int> numbers;

	cout << "Enter number of elements in the array ? ";
	cin >> n;

	while (n--) {
		cout << "Enter number : ";
		cin >> num;
		numbers.emplace_back(num);
	}

	return numbers;
}

int main()
{
	vector <int> nums;
	int n;
	nums = read_input();

	char choice;
	cout << "Enter the choice ? (Smallest = s / Largest = l ) ? ";
	cin >> choice;

	int k;
	cout << "Enter value of K :";
	cin >> k;

	if (k < 0 || k > nums.size()) {
		cout << "K is invalid\n";
		exit(-1);
	}

	int result;
	if (choice == 's') {
		result = find_kth_smallest(nums, k);
	} else if (choice == 'l') {
		result = find_kth_largest(nums, k);
	} else {
		cout << "Bad choice ...\n";
		exit(-1);
	}

	printf("\n[ ");
	for (auto n : nums)
	{
		cout << n << " ";
	}
	printf("]: Result = %d\n", result);

	return 0;
}
