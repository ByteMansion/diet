/**
 * @file	tree.cpp
 * @brief	All functions are solutions of leetcode problems.
 *
 * @author	Changrui
 * @date	2018/11/28
 *
 * Copyright © 2018 ChangruiShao. All rights reserved.
 */

#include "tree.hpp"

#include <stack>

using namespace std;

/**
 * @brief   non-recursive postorder traversal
 * @param
 *  root    root node of binary tree
 * @return  vector of tree member
 */
vector<int> Solution::postorder_traversal(TreeNode *root)
{
	vector<int> result{};
	if(root == nullptr)
        return result;

	TreeNode *pNode = root;
	TreeNode *pFlag = nullptr;
	stack<TreeNode *> sNode;

	while(pNode != nullptr || !sNode.empty()) {
		while(pNode != nullptr) {
			sNode.push(pNode);
			pNode = pNode->left;
		}
		pNode = sNode.top();
		if(pNode->right == nullptr || pNode->right == pFlag) {
			result.push_back(pNode->val);
			sNode.pop();
			pFlag = pNode;
            pNode = nullptr;
		} else {
			pNode = pNode->right;
		}
	}

	return result;
}

/**
 * @brief   recursive implementation of postorder traversal
 * @param
 *  root    root node of binary tree
 */
void postorder_traversal_helper(TreeNode *root, vector<int>& result)
{
    if(root == nullptr) {
        return;
    }
    if(root->left) {
        postorder_traversal_helper(root->left, result);
    }
    if(root->right) {
        postorder_traversal_helper(root->right, result);
    }
    result.push_back(root->val);
}

vector<int> Solution::recursive_postorder_traversal(TreeNode *root)
{
	vector<int> result{};
    postorder_traversal_helper(root, result);
	
	return result;
}

/**
 * @brief	non-recursive implementation of inorder traversal
 * @param
 *  root	root node of binary tree
 */
vector<int> Solution::inorder_traversal(TreeNode *root)
{
	vector<int> result{};
	if(root == nullptr)
		return result;
	
	TreeNode *pNode = root;
	stack<TreeNode *> sNode;
	
	while (pNode != nullptr || !sNode.empty()) {
		while (pNode != nullptr) {
			sNode.push(pNode);
			pNode = pNode->left;
		}
		pNode = sNode.top();
		result.push_back(pNode->val);
		sNode.pop();
		
		if(pNode->right == nullptr) {
			pNode = nullptr;
		} else {
			pNode = pNode->right;
		}
	}
	return result;
}

/**
 * @brief	recursive inorder traversal
 */
void inorder_traversal_helper(TreeNode *root, vector<int>& result)
{
	if(root == nullptr)
		return;
	
	if(root->left) {
		inorder_traversal_helper(root->left, result);
	}
	result.push_back(root->val);
	if(root->right) {
		inorder_traversal_helper(root->right, result);
	}
}

vector<int> Solution::recursive_inorder_traversal(TreeNode *root)
{
	vector<int> result{};
	inorder_traversal_helper(root, result);
	
	return result;
}

/**
 * @brief	non-recursive preorder traversal
 */
vector<int> Solution::preorder_traversal(TreeNode *root)
{
	vector<int> result{};
	if(root == nullptr)
		return result;
	
	TreeNode *pNode = root;
	stack<TreeNode *> sNode;
	sNode.push(pNode);
	
	while (!sNode.empty()) {
		pNode = sNode.top();
		result.push_back(pNode->val);
		sNode.pop();
		
		if(pNode->right) {
			sNode.push(pNode->right);
		}
		if(pNode->left) {
			sNode.push(pNode->left);
		}
	}
	
	return result;
}

/**
 * @brief	recursive preorder traversal
 */
void preorder_traversal_helper(TreeNode *root, vector<int>& result)
{
	if(root == nullptr)
		return;
	
	result.push_back(root->val);
	if(root->left) {
		preorder_traversal_helper(root->left, result);
	}
	if(root->right) {
		preorder_traversal_helper(root->right, result);
	}
}

vector<int> Solution::recursive_preorder_traversal(TreeNode *root)
{
	vector<int> result{};
	preorder_traversal_helper(root, result);
	
	return result;
}

/**
 * @brief	Leetcode 814: Binary Tree Pruning
 * 	We are given the head node root of a binary tree, where additionally e
 * 	very node's value is either a 0 or a 1. Return the same tree where every
 *	subtree (of the given tree) not containing a 1 has been removed.
 *	(Recall that the subtree of a node X is X, plus every node that is a descendant of X.)
 *
 * @param
 * 	root	head node root of a binary tree
 * @return	pointer to a TreeNode node.
 */
TreeNode* Solution::pruneTree(TreeNode *root)
{
    TreeNode *result = nullptr;


	return result;
}
