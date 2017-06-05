/* Segment tree for efficient
 *          -> total sum between given two indexes of array
 *          -> Updation of an array value at given index.
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */
#include <iostream>
#include <vector>

using namespace std;

#define lchild(node) (2 * (node) + 1)
#define rchild(node) (lchild(node) + 1)

/* Construct the segment tree. The segment tree length
 * is 4 times the given input array.
 */
void build_tree(vector <int>&segtree, vector <int>&nums,
		int low, int high, int node)
{
	if (low == high) {
		segtree[node] = nums[low];
		return;
	}

	int mid = low + (high - low) / 2;

	build_tree(segtree, nums, low, mid, lchild(node));
	build_tree(segtree, nums, mid + 1, high, rchild(node));

	segtree[node] = segtree[lchild(node)] + segtree[rchild(node)];
}

/* Query the tree to compute sum from array index [qstart - qend] */
int query_tree(vector <int>& segtree, int qstart, int qend,
	       int tree_start, int tree_end, int node)
{
	if (tree_start >= qstart && tree_end <= qend) {
		/* Node fits completely in the query range */
		return segtree[node];
	}

	/* Out of range */
	if (tree_end < qstart || tree_start > qend) { return 0; }

	int mid = tree_start + (tree_end - tree_start) /  2;

	int left = query_tree(segtree, qstart, qend, tree_start,
			      mid, lchild(node));

	int right = query_tree(segtree, qstart, qend,
			       mid + 1, tree_end, rchild(node));

	return left + right;
}

/* Update the array and the segment tree with a new value */
void update_tree(vector <int>& segtree, int start, int end,
		 int dist, int node, int delta)
{
	segtree[node] += delta;

	if (start == end) {
		return;
	}

	int mid = start + (end - start) / 2;

	if ((mid - start + 1) > dist) {
		update_tree(segtree, start, mid, dist, lchild(node), delta);
	} else {
		update_tree(segtree, mid + 1, end,
			    dist - (mid - start + 1), rchild(node), delta);
	}
}

void print_segtree(vector <int>& segtree)
{
	cout << "Segment tree :\n";
	cout <<"[ ";
	for (auto s : segtree) {
		cout << s << " ";
	}
	cout << " ]\n";
}

/* Double check the answer with simple iteration sum */
int iterate_query(vector <int>& nums, int start, int end)
{
	int sum = 0;
	for (int i = start; i <= end; i++) {
		sum += nums[i];
	}
	return sum;
}

int main(void)
{
	int n;
	cout << "Enter the number of array elements : ";
	cin >> n;

	vector <int> nums(n);
	vector <int> segtree(4 * n , 0);

	printf("Enter array elements : ");
	for (int i = 0; i < n; i++) {
		cin >> nums[i];
	}

	build_tree(segtree, nums, 0, n - 1, 0);

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
			printf("\tSegment tree : %d\n",
					query_tree(segtree, s, e,
						   0, n - 1, 0));
			printf("\tIterative : %d\n",
					iterate_query(nums, s, e));
			print_segtree(segtree);

		} else if (choice == 'u') {
			int idx, val;
			cout << "Enter update index and value :";
			cin >> idx >> val;
			idx = min(max(0, idx), n - 1);
			update_tree(segtree, 0, n - 1, idx, 0, val - nums[idx]);
			nums[idx] = val;
			print_segtree(segtree);
		} else if (choice == 'x') {
			break;
		}
	}

	return 0;
}
