/* Implementation of Fenwick Trees. This code creates a
 * fenwick tree, and performs some range queries.
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */

#include <iostream>
#include <vector>

using namespace std;

/* Get the next node, by adding 1 to the
 * last set bit in the given node.
 */
int get_next(int node)
{
	return node + (node & -node);
}

/* Get the next node, by clearing 1 from the
 * last set bit in the given node.
 */
int get_parent(int node)
{
	return node - (node & -node);
}

/* Helper routine to print a vector */
void print_vector(vector <int>& nums)
{
	printf("[ ");
	for (auto n : nums) {
		printf("%d   ", n);
	}
	printf("]\n");
}

/* Add delta to the given index. Index is 1 based here instead
 * of 0.
 */
void update_tree(vector <int>& fenwick, int idx, int delta)
{
	while (idx < fenwick.size()) {
		fenwick[idx] += delta;
		idx = get_next(idx);
	}
}

/* Compute prefix sum  upto the given index. Index is 1 based here instead
 * of 0.
 */
int query_tree(vector <int>& fenwick, int idx)
{
	int sum = 0;

	while (idx) {
		sum += fenwick[idx];
		idx = get_parent(idx);
	}

	return sum;
}

/* Compute the prefix sum by iteration from s till e index */
int iterate_query(vector <int>&nums, int s, int e)
{
	int sum = 0;
	for (int i = s; i <= e; i++) {
		sum += nums[i];
	}

	return sum;
}

/* Create the fenwick tree. We initialize the tree with zero
 * and simply use the update function to add deltas.
 */
void create_fenwick_tree(vector <int>&fenwick, vector <int>&nums)
{
	for (int i = 0; i < nums.size(); i++) {
		update_tree(fenwick, i + 1, nums[i]);
	}
}

int main()
{
	int nelements;
	cout << "Enter the number of elements in the array :";
	cin >> nelements;

	vector <int> nums(nelements);
	vector <int> fenwick(nelements + 1, 0);

	/* Generate some random data */
	while(nelements--) {
		nums[nelements] = (rand() % 50) * (rand() % 2 ? -1 : 1);
	}

	cout << "Input array : ";
	print_vector(nums);

	create_fenwick_tree(fenwick, nums);

	int n = nums.size();

	while (1) {
		char choice;
		cout << "Query / Update / Exit (q / u / x ) ? :";
		cin >> choice;

		if (choice == 'q') {
			int s, e;
			cout << "Enter query range : ";
			cin >> s >> e;
			s = max(s, 0);
			e = min(e, n - 1);

			printf("Sum of ranges between index ");
			printf("[%d (%d) -  %d (%d)] :\n", s, nums[s],
					e, nums[e]);
			printf("\tIterative : %d\n",
					iterate_query(nums, s, e));

			/* Increment by one, since fenwick tree is based of
			 * index 1
			 */
			e++;
			printf("\tFenwick tree : %d - %d = %d\n",
					query_tree(fenwick, e),
					query_tree(fenwick, s),
					query_tree(fenwick, e) -
					query_tree(fenwick, s));
		} else if (choice == 'u') {
			int idx, val;
			cout << "Enter update index and new value :";
			cin >> idx >> val;
			idx = min(max(0, idx), n - 1);
			update_tree(fenwick, idx + 1, val - nums[idx]);
			nums[idx] = val;
			print_vector(nums);
		} else if (choice == 'x') {
			break;
		}
	}
}
