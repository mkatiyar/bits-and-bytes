/*
 * Traversing a graph in BFS style. This program traverses
 * each node of a matrix to find the number of islands in the
 * given matrix. Each 1 is supposed to represent land
 * Each index of the matrix is considered to be a graph
 * node, and the up, down, left, right are the nodes which are connected
 * to it.
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */

#include <iostream>
#include <queue>
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
		value);
}

/* Helper to print 2D array */
void print_matrix(vector <vector <int>>& V)
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
		Q.push(Node(a, b));				\
	}							\
}

/* Traverse the graph to find out the connected land. */
int num_Islands(vector <vector <int>> matrix)
{
	queue <Node> Q;

	int islands = 0;

	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[0].size(); j++) {

			/* Start BFS */
			if (matrix[i][j] == 1) {
				islands++;
				Q.push(Node(i, j));

				while (!Q.empty()) {
					int x = Q.front().x;
					int y = Q.front().y;
					int val = matrix[x][y];

					matrix[x][y] = 0;

					PUSH_TO_STACK(x - 1, y, val);
					PUSH_TO_STACK(x + 1, y, val);
					PUSH_TO_STACK(x , y + 1, val);
					PUSH_TO_STACK(x , y - 1, val);

					Q.pop();
				}
			}
		}
	}
	return islands;
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
			matrix[i][j] = rand() % 2;
		}
	}

	printf("Matrix :\n");
	print_matrix(matrix);
	printf("Number of islands = %d\n", num_Islands(matrix));

	return 0;
}
