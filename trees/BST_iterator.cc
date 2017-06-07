/* Iterator for Binary search trees. The iterator isn't really
 * specific for BST and should be applicable to any binary tree.
 * This code uses this iterator to print common elements between
 * two binary search trees.
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */

#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include "node.h"

using namespace std;

/* Maximum value in the BST tree. Values are generated randomly */
#define MAXVAL 75


bool has_next_node(stack <TreeNode *>& Spath)
{
	return !Spath.empty();
}

TreeNode* get_next_node(stack <TreeNode *>& Spath)
{
	if (Spath.empty()) return NULL;

	TreeNode *tmp = Spath.top();

	Spath.pop();

	TreeNode *root = tmp->right;

	while (root) {
		Spath.push(root);
		root = root->left;
	}

	return tmp;
}

/* Insert a node in tree iteratively */
void insert_value_iterative(TreeNode **root, int val)
{
	while (*root != NULL) {
		if (val > (*root)->val) {
			root = &(*root)->right;
		} else {
			root = &(*root)->left;
		}
	}
	(*root) = new TreeNode(val);
}

/* Initialize the initial state of stack to be the leftmost child */
void init_stack(stack <TreeNode *>& S, TreeNode *root)
{
	while (root) {
		S.push(root);
		root = root->left;
	}
}

void print_common_elements(TreeNode *tree1, TreeNode *tree2)
{
	stack <TreeNode *> Stree1, Stree2;

	init_stack(Stree1, tree1);
	init_stack(Stree2, tree2);

	printf("\nCommon elements between two trees are : [ ");
	while(has_next_node(Stree1) && has_next_node(Stree2)) {
		int a = Stree1.top()->val;
		int b = Stree2.top()->val;

		if (a == b) {
			cout << a << " ";
			(void)get_next_node(Stree1);
			(void)get_next_node(Stree2);
		} else if (a < b) {
			while (!Stree1.empty() && Stree1.top()->val < b) {
				(void)get_next_node(Stree1);
			}
		} else {
			while (!Stree2.empty() && Stree2.top()->val < a) {
				(void)get_next_node(Stree2);
			}
		}
	}
	printf(" ]");
}

/* Get a random value for the BST */
int get_random_value()
{
	return (-MAXVAL + (rand() % (2 * MAXVAL)));
}

/* Create the tree */
void create_BST(TreeNode **root, int n)
{
	/* Generate a binary tree with given number of nodes.
	 * Node values are generated randomly and are inserted
	 * in the existing tree.
	 */
	while (n--) {
		int val = get_random_value();
		insert_value_iterative(root, val);
	}
}

/* Use the iterator to print the tree */
void print_tree(TreeNode *root)
{
	stack <TreeNode *> S;

	printf("\n[ ");

	init_stack(S, root);

	while (has_next_node(S)) {
		printf("%3d ", get_next_node(S)->val);
	}

	printf(" ]\n");
}

int main()
{
	int n;
	cout << "Enter the number of nodes in tree :";
	cin >> n;

	srand(time(NULL));

	TreeNode *groot1 = NULL, *groot2 = NULL;

	create_BST(&groot1, n);
	create_BST(&groot2, n);

	printf("Initial trees: ");
	print_tree(groot1);
	print_tree(groot2);

	print_common_elements(groot1, groot2);

	printf("\n");
}
