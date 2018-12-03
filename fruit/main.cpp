/**
 * @file  main.cpp
 * @brief test problem solutions
 *
 * @author  Changrui
 * @date    2018/11/28
 *
 * Copyright © 2018 ChangruiShao. All rights reserved.
 */

#include "tree.hpp"
#include "util.hpp"

#include <iostream>
#include <vector>

using std::cout;
using std::vector;

int main(int argc, const char * argv[]) {
	
	Solution s;
	
/**
 *          1
 *       /     \
 *      2       3
 *     / \     /
 *    4  5    6
 *        \  / \
 *         7 8  9
 * ----------------------
 *          1
 *       /     \
 *      0       1
 *     / \     /
 *    1  0    0
 *        \  / \
 *         0 1  0
 */
	TreeNode *root  = new TreeNode(1);
	TreeNode *node2 = new TreeNode(0);
	TreeNode *node3 = new TreeNode(1);
	TreeNode *node4 = new TreeNode(1);
	TreeNode *node5 = new TreeNode(0);
	TreeNode *node6 = new TreeNode(0);
	TreeNode *node7 = new TreeNode(0);
	TreeNode *node8 = new TreeNode(1);
	TreeNode *node9 = new TreeNode(0);

	root->left   = node2; root->right  = node3;
	node2->left  = node4; node2->right = node5;
	node3->left  = node6;
	node5->right = node7;
	node6->left  = node8; node6->right = node9;

	s.root = root;
	vector<int> result{};
	TreeNode *pResult = nullptr;
#if 0
	// postorder
	result = s.postorderTraversal(s.root);
	print_list(result);
	result = s.recursive_postorderTraversal(s.root);
	print_list(result);
	
	// inorder
	result = s.inorderTraversal(root);
	print_list(result);
	result = s.recursive_inorderTraversal(root);
	print_list(result);
	
	//preorder
	result = s.preorderTraversal(root);
	print_list(result);
	result = s.recursive_preorderTraversal(root);
	print_list(result);
#endif
	// leetcode 814: binary tree pruning
	pResult = s.recursive_pruneTree(root);
	result = s.preorderTraversal(pResult);
	print_list(result);
	pResult = s.pruneTree(root);
	result = s.preorderTraversal(pResult);
	print_list(result);
	

	delete root;
	delete node2;
	delete node3;
	delete node4;
	delete node5;
	delete node6;
	delete node7;
	delete node8;
	delete node9;

	return 0;
}
