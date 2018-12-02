/**
 * @file	tree.hpp
 * @brief	Data structures of leetcode problems needed and class solutions
 *
 * @author	Changrui
 * @date	2018/11/28
 *
 * Copyright © 2018 ChangruiShao. All rights reserved.
 */

#ifndef tree_hpp
#define tree_hpp

#include <stdio.h>
#include <vector>

using std::vector;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

class Solution {
public:
  TreeNode *root;

public:
	// postorder traversal
	vector<int> postorder_traversal(TreeNode *root);
	vector<int> recursive_postorder_traversal(TreeNode *root);
	
	// inorder traversal
	vector<int> inorder_traversal(TreeNode *root);
	vector<int> recursive_inorder_traversal(TreeNode *root);
	
	// preorder traversal
	vector<int> preorder_traversal(TreeNode *root);
	vector<int> recursive_preorder_traversal(TreeNode *root);

	// Leetcode 814: Binary Tree Pruning
	TreeNode* pruneTree(TreeNode* root);

private:

};

#endif /* tree_hpp */
