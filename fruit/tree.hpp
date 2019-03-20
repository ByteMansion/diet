/**
 * @file	tree.hpp
 * @brief	Data structures and function declarations
 *
 * @author	Changrui
 * @date	2018/11/28
 *
 * Copyright © 2018 ChangruiShao. All rights reserved.
 */

#ifndef _tree_hpp
#define _tree_hpp

#include <stdio.h>
#include <vector>

using std::vector;
using std::pair;

struct TreeNode {
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x): val(x), left(nullptr), right(nullptr){}
};


// postorder traversal
vector<int> postorderTraversal(TreeNode* root);
vector<int> postorderTraversal2(TreeNode* root);

// inorder traversal
vector<int> inorderTraversal(TreeNode* root);
vector<int> inorderTraversal2(TreeNode* root);

// preorder traversal
vector<int> preorderTraversal(TreeNode* root);
vector<int> preorderTraversal2(TreeNode* root);

// Leetcode 814: Binary Tree Pruning
TreeNode* pruneTree(TreeNode* root);
TreeNode* pruneTree2(TreeNode* root);

// Leetcode 102: Binary Tree Level Order Traversal
vector<vector<int>> levelOrder(TreeNode* root);
vector<vector<int>> levelOrder2(TreeNode* root);

// Leetcode 107: Binary Tree Level Order Traversal II
vector<vector<int>> levelOrderBottom(TreeNode* root);

// Leetcode 310: Minimum Height Trees
vector<int> findMinHeightTrees(int n, vector<pair<int, int>>& edges);
vector<int> findMinHeightTrees2(int n, vector<pair<int, int>>& edges);

// Leetcode 105: Construct Binary Tree from Preorder and Inorder Traversal
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder);

#endif /* tree_hpp */
