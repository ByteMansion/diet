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
using std::pair;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* ight;
	TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};

class Solution {

public:
	// postorder traversal
	vector<int> postorderTraversal(TreeNode* root);
	vector<int> postorderTraversal2(TreeNode* root);
	
	// inorder traversal
	vector<int> inorderTraversal(TreeNode* root);
	vector<int> inorderTraversal(TreeNode* root);
	
	// preorder traversal
	vector<int> preorderTraversal(TreeNode* root);
	vector<int> preorderTraversal(TreeNode* root);

	// Leetcode 814: Binary Tree Pruning
	TreeNode* pruneTree(TreeNode* root);
	TreeNode* recursive_pruneTree(TreeNode* root);
	
	// Leetcode 102: Binary Tree Level Order Traversal
	vector<vector<int>> levelOrder(TreeNode* root);
	vector<vector<int>> levelOrder2(TreeNode* root);
	
	// Leetcode 310: Minimum Height Trees
	vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges);
	vector<int> findMinHeightTrees2(int n, vector<pair<int, int>>& edges);

private:
  TreeNode* root;

};

#endif /* tree_hpp */
