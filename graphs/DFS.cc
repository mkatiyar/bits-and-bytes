/*
 * Traversing a graph in DFS style. This program traverses
 * each node of a matrix to find the longest increasing value path
 * using DFS. Each index of the matrix is considered to be a graph
 * node, and the up, down, left, right are the nodes which are connected
 * to it. We can jump to neighboring node if its value is greater than the
 * current node's value.
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */

#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/* Node of the graph */
class Node {
public:
	int x, y;
	Node(int i, int j) {
		x = i;
		y = j;
	}
};

/* Return true if its ok to jump to the i, jth index given the value ie..
 * if there is an edge.
 */
bool valid_path(vector <vector <int>>& matrix, int i, int j, int value)
{
	return (i >= 0 && j >= 0 &&
		i < matrix.size() && j < matrix[0].size() &&
		value < matrix[i][j]);
}

/* Helper to print 2D array */
void print_vector(vector <vector <int>>& V)
{
	for (auto v : V) {
		printf("[");
		for (auto vv : v) {
			printf("%2d  ", vv);
		}
		printf("]\n");
	}
}

#define PUSH_TO_STACK(a, b, val)				\
{								\
	if (valid_path(matrix, a, b, val)) {			\
		if (path[a][b] != 0) {				\
			maxpath = max(maxpath, 1 + path[a][b]);	\
		} else {					\
			S.push(Node(a, b));			\
			continue;				\
		}						\
	}							\
}

/* Traverse the graph. Note that it is possible to optimize the
 * below DFS traversal by reusing the computed "path" variable (ie..
 * using memoization, but then this program only focuses on DFS.
 */
void longest_DFS_path(vector <vector <int>> matrix)
{
	stack <Node> S;

	vector <vector <int>> path(matrix.size(),
			      vector <int>(matrix[0].size(), 0));

	int maxlen = 0, maxi, maxj;

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {

			/* Start DFS */
			S.push(Node(i, j));

			while (!S.empty()) {
				int x = S.top().x;
				int y = S.top().y;
				int val = matrix[x][y];
				int maxpath = 1;

				PUSH_TO_STACK(x - 1, y, val);
				PUSH_TO_STACK(x + 1, y, val);
				PUSH_TO_STACK(x , y + 1, val);
				PUSH_TO_STACK(x , y - 1, val);

				path[x][y] = maxpath;

				S.pop();
			}

			if (path[i][j] > maxlen) {
				maxlen = path[i][j];
				maxi = i;
				maxj = j;
			}
		}
	}

	printf("\nMax path is %d at [%d, %d]\n", maxlen, maxi, maxj);
	printf("\nOriginal matrix :\n");
	print_vector(matrix);
	printf("\nPath matrix :\n");
	print_vector(path);
}

int main()
{
	int rows, cols;
	cout << "Enter matrix size : ";
	cin >> rows >> cols;

	vector <vector <int>> matrix(rows, vector <int>(cols, 0));

	srand(time(NULL));

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			matrix[i][j] = rand() % 100;
		}
	}

	longest_DFS_path(matrix);
}
