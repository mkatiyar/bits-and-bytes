/* Definition of the tree node to be used in other programs
 *
 * Author : Manish Katiyar <mkatiyar@gmail.com>
 */

#ifndef __TREENODE__
#define __TREENODE__

struct TreeNode {
	int val;
	TreeNode *right;
	TreeNode *left;

	TreeNode(int v) {
		val = v;
		right = left = NULL;
	}
};
#endif
