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
#include <list>
#include <queue>

using std::stack;
using std::list;
using std::queue;
using std::pair;
using std::move;

/**
 * @brief   non-recursive postorder traversal
 * @param
 *  root    root node of binary tree
 * @return  vector of tree member
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
vector<int> Solution::postorderTraversal(TreeNode *root)
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
void postorderTraversalHelper(TreeNode *root, vector<int>& result)
{
    if(root == nullptr) {
        return;
    }
    if(root->left) {
        postorderTraversalHelper(root->left, result);
    }
    if(root->right) {
        postorderTraversalHelper(root->right, result);
    }
    result.push_back(root->val);
}

vector<int> Solution::recursive_postorderTraversal(TreeNode *root)
{
	vector<int> result{};
    postorderTraversalHelper(root, result);
	
	return result;
}

/**
 * @brief	non-recursive implementation of inorder traversal
 * @param
 *  root	root node of binary tree
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
vector<int> Solution::inorderTraversal(TreeNode *root)
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
void inorderTraversalHelper(TreeNode *root, vector<int>& result)
{
	if(root == nullptr)
		return;
	
	if(root->left) {
		inorderTraversalHelper(root->left, result);
	}
	result.push_back(root->val);
	if(root->right) {
		inorderTraversalHelper(root->right, result);
	}
}

vector<int> Solution::recursive_inorderTraversal(TreeNode *root)
{
	vector<int> result{};
	inorderTraversalHelper(root, result);
	
	return result;
}

/**
 * @brief	non-recursive preorder traversal
 *
 * --------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
vector<int> Solution::preorderTraversal(TreeNode *root)
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
void preorderTraversalHelper(TreeNode *root, vector<int>& result)
{
	if(root == nullptr)
		return;
	
	result.push_back(root->val);
	if(root->left) {
		preorderTraversalHelper(root->left, result);
	}
	if(root->right) {
		preorderTraversalHelper(root->right, result);
	}
}

vector<int> Solution::recursive_preorderTraversal(TreeNode *root)
{
	vector<int> result{};
	preorderTraversalHelper(root, result);
	
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
 *
 * --------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
TreeNode* Solution::pruneTree(TreeNode *root)
{
    TreeNode *result = root;
	if(root == nullptr)
		return result;
	
	TreeNode *pNode = root;
	TreeNode *pFlag = nullptr;
	stack<TreeNode *> sNode;
	
	// assign -1 to the root node of subtree not containing a 1
	// postorder traversal
	while (pNode != nullptr || !sNode.empty()) {
		while (pNode != nullptr) {
			sNode.push(pNode);
			pNode = pNode->left;
		}
		pNode = sNode.top();
		if (pNode->right == nullptr || pNode->right == pFlag) {
			if((pNode->left == nullptr || pNode->left->val == -1) &&
			   (pNode->right == nullptr || pNode->right->val == -1) &&
			   pNode->val == 0) {
				pNode->val = -1;
			}
			pFlag = pNode;
			pNode = nullptr;
			sNode.pop();
		} else {
			pNode = pNode->right;
		}
	}

	// assign nullptr to the node whose value is -1
	// preorder traversal
	if (root->val == -1) {
		return nullptr;
	}
	sNode.push(root);
	while (!sNode.empty()) {
		root = sNode.top();
		sNode.pop();
		if (root->right != nullptr) {
			if (root->right->val == -1) {
				root->right = nullptr;
			} else {
				sNode.push(root->right);
			}
		}
		if (root->left != nullptr) {
			if (root->left->val == -1) {
				root->left = nullptr;
			} else {
				sNode.push(root->left);
			}
		}
	}
	return result;
}

/**
 * @brief	Leetcode 814: Binary Tree Pruning
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 33%
 */
TreeNode* Solution::recursive_pruneTree(TreeNode *root)
{
	if(root == nullptr)
		return nullptr;
	root->left = recursive_pruneTree(root->left);
	root->right = recursive_pruneTree(root->right);
	if(root->left == nullptr && root->right == nullptr && root->val == 0)
		return nullptr;
	
	return root;
}

/**
 * @brief	Leetcode 102: Binary Tree Level Order Traversal
 *
 * --------------------------------------------------------
 */
vector<vector<int>> Solution::levelOrder(TreeNode* root) {
	vector<vector<int>> result;
	if (root == nullptr) {
		return result;
	}
	vector<int>	level;
	
	queue<TreeNode*> sLevel1;
	queue<TreeNode*> sLevel2;
	sLevel1.push(root);
	while (true) {
		while (!sLevel1.empty()) {
			TreeNode *node = sLevel1.front();
			sLevel1.pop();
			level.push_back(node->val);
			if (node->left) {
				sLevel2.push(node->left);
			}
			if (node->right) {
				sLevel2.push(node->right);
			}
		}
		result.push_back(level);
		level.clear();
		if (sLevel2.empty()) {
			break;
		}
		sLevel1 = sLevel2;
	}

	return result;
}


/**
 * @brief	Leetcode 310: Minimum Height Trees
 *
 * this problem is related to BFS and graph.
 * the solution below is by graph theory.
 * --------------------------------------------
 * Accepted Solutions Runtime Distribution 83%
 */
vector<int> Solution::findMinHeightTrees(int n, vector<pair<int, int>>& edges)
{
	// adjacent node list
	vector<vector<int>> adjacencyList(n);
	for (int i = 0; i < n; ++i) {
		adjacencyList[i] = vector<int>();
	}
	// get node degree
	vector<int> degree(n, 0);
	for (auto const& edge : edges) {
		adjacencyList[edge.first].push_back(edge.second);
		adjacencyList[edge.second].push_back(edge.first);
		++degree[edge.first];
		++degree[edge.second];
	}
	
	vector<int> leafNodes;
	for (int i = 0; i < n; ++i) {
		if (degree[i] == 1) {
			leafNodes.push_back(i);
			degree[i] = 0;
		}
	}
	
	int numNodes = n;
	while (numNodes > 2) {
		vector<int> newLeafNodes;
		numNodes -= leafNodes.size();
		for (auto node : leafNodes) {
			for (auto neigh : adjacencyList[node]) {
				--degree[neigh];
				if (degree[neigh] == 1) {
					newLeafNodes.push_back(neigh);
				}
			}
		}
		leafNodes = move(newLeafNodes);
	}
	
	if (n == 1) {
		leafNodes.push_back(0);
	}
	return leafNodes;
}
/**
 * @brief	Leetcode 310: Minimum Height Trees
 *
 * --------------------------------------------
 * Accepted Solutions Runtime Distribution 83%
 */
vector<int> Solution::findMinHeightTrees2(int n, vector<pair<int, int>>& edges)
{
	if (n < 2) return {0};

	vector<int> indegres(n, 0);
	vector<vector<int>> graph(n);

	for (auto& p: edges) {
		graph[p.first].push_back(p.second);
		graph[p.second].push_back(p.first);
		indegres[p.first]++;
		indegres[p.second]++;
	}

	queue<int> que;
	for (int i = 0; i < n; i++)
	if (indegres[i] == 1)
	que.push(i);


	while (n > 2) {
		size_t k = que.size();
		n -= k;
		
		for (int i = 0; i < k; i++) {
			auto u = que.front(); que.pop();
			
			for (auto v: graph[u])
				if (--indegres[v] == 1)
					que.push(v);
					}
	}

	vector<int> res;
	while (!que.empty()) {
		res.push_back(que.front());
		que.pop();
	}

	return res;
}
