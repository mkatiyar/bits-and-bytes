/* Binary search trees. This file has both
 * recursive and itearative implementation of the common
 * operations on BSTs
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

/* Global root of the binary tree */
TreeNode *groot = NULL;

/* Insert a node in tree recursively */
void insert_value_recursive(TreeNode **root, int val)
{
	if ((*root) == NULL) {
		(*root) = new TreeNode(val);
		return;
	}

	TreeNode *head = (*root);

	if (val > head->val) {
		insert_value_recursive(&head->right, val);
	} else {
		insert_value_recursive(&head->left, val);
	}
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

/* Tree Traversal routines - recursive version */
void do_something(TreeNode *tmp)
{
	cout << tmp->val << " ";
}

void inorder_recursive(TreeNode *root)
{
	if (root == NULL) {return;}

	inorder_recursive(root->left);
	do_something(root);
	inorder_recursive(root->right);
}

void preorder_recursive(TreeNode *root)
{
	if (root == NULL) {return;}

	do_something(root);
	preorder_recursive(root->left);
	preorder_recursive(root->right);
}

void postorder_recursive(TreeNode *root)
{
	if (root == NULL) {return;}

	postorder_recursive(root->left);
	postorder_recursive(root->right);
	do_something(root);
}

/* Tree Traversal routines - iterative version
 * Check how similar they are.
 */
void inorder_iterative(TreeNode *root)
{
	stack <TreeNode *> S;

	while (root || !S.empty()) {
		if (root) {
			S.push(root);
			root = root->left;
		} else {
			root = S.top();
			S.pop();
			do_something(root); // Do whatever we want with the node
			root = root->right;
		}
	}
}

void preorder_iterative(TreeNode *root)
{
	stack <TreeNode *> S;

	while (root || !S.empty()) {
		if (root) {
			do_something(root); // Do whatever we want with the node
			S.push(root);
			root = root->left;
		} else {
			root = S.top();
			S.pop();
			root = root->right;
		}
	}
}

/* Post order iterative is simply preorder walk (with left and right switched)
 * stored on stack and then printing the values. This version uses two stacks.
 * There is also a single stack version implemented below.
 */
void postorder_iterative_two_stacks(TreeNode *root)
{
	stack <TreeNode *> S;
	stack <TreeNode *> Values;

	while (root || !S.empty()) {
		if (root) {
			S.push(root);
			// Do something with the node
			Values.push(root);
			root = root->right;
		} else {
			root = S.top();
			S.pop();
			root = root->left;
		}
	}

	/* Pop the values off stack */
	while (!Values.empty()) {
		do_something(Values.top());
		Values.pop();
	}
}

/* Post order traversal using single stack */
void postorder_iterative_one_stack(TreeNode *root)
{
	stack <TreeNode *> S;

	while (root || !S.empty()) {
		if (root) {
			if (root->right) {
				S.push(root->right);
			}
			S.push(root);
			root = root->left;
		} else {
			root = S.top();
			S.pop();

			/* If the top of stack is same as root's right,
			 * then make that as root instead and push back
			 * our old root.
			 */
			if (root->right &&
			    (!S.empty() && S.top() == root->right)) {
				S.pop();
				S.push(root);
				root = root->right;
			} else {
				do_something(root);
				root = NULL;
			}
		}
	}
}

/* Common helper routines */
void inorder_walk()
{
	printf("\n++++++++++++++++++++++++++++++++++++++\n");
	printf("Inorder walk :");

	printf("\nRecursive : ");
	inorder_recursive(groot);

	printf("\nIterative : ");
	inorder_iterative(groot);
}

void preorder_walk()
{
	printf("\n++++++++++++++++++++++++++++++++++++++\n");
	printf("Preorder walk : ");

	printf("\nRecursive : ");
	preorder_recursive(groot);

	printf("\nIterative : ");
	preorder_iterative(groot);
}

void postorder_walk()
{
	printf("\n++++++++++++++++++++++++++++++++++++++\n");
	printf("Postorder walk :");

	printf("\nRecursive : ");
	postorder_recursive(groot);

	printf("\nIterative (2 stacks) : ");
	postorder_iterative_two_stacks(groot);

	printf("\nIterative (1 stack)  : ");
	postorder_iterative_one_stack(groot);
}

/* Get a random value for the BST */
int get_random_value()
{
	return (-MAXVAL + (rand() % (2 * MAXVAL)));
}

/* Create the tree */
void create_BST(int n)
{
	/* Generate a binary tree with given number of nodes.
	 * Node values are generated randomly and are inserted
	 * in the existing tree either recursively or iteratively.
	 */
	while (n--) {
		int val = get_random_value();
		if (rand() % 2) {
			insert_value_recursive(&groot, val);
		} else {
			insert_value_iterative(&groot, val);
		}
	}
}

/* Search for a value in tree recursively */
bool is_exist_recursive(TreeNode *root, int val)
{
	if (root == NULL) { return false; }

	if (root->val == val) { return true; }

	if (root->val < val) {
		return is_exist_recursive(root->right, val);
	} else {
		return is_exist_recursive(root->left, val);
	}
}

/* Search for a value in tree iteratively */
bool is_exist_iterative(TreeNode *root, int val)
{
	while (root) {
		if (root->val == val) { return true; }
		if (root->val < val) {
			root = root->right;
		} else {
			root = root->left;
		}
	}

	return false;
}

bool BST_search(TreeNode *root, int val)
{
	printf("Searching %3d : ", val);
	if (rand() % 2) {
		return is_exist_recursive(root, val);
	} else {
		return is_exist_iterative(root, val);
	}
}

int main()
{
	int n;
	cout << "Enter the number of nodes in tree :";
	cin >> n;

	srand(time(NULL));

	create_BST(n);

	inorder_walk();
	preorder_walk();
	postorder_walk();

	printf("\n\nPerforming some searches ...\n");
	int ntests = (rand() % 15 + 1);
	while (ntests--) {
		int val = get_random_value();
		bool ret;

		ret = BST_search(groot, val);

		printf("%s\n", ret ? "EXISTS" : "DOESN'T EXIST");
	}

	printf("\n");
}
