/**
 * @file    main.cpp
 * @brief   test the validity of solutions
 *
 * @author  Changrui
 * @date    2018/11/28
 *
 * Copyright © 2018 ChangruiShao. All rights reserved.
 */

#include "tree.hpp"
#include "util.hpp"
#include "array.hpp"
#include "linkedlist.hpp"

#include <iostream>
#include <vector>
#include <string>

using std::cout;
using std::vector;
using std::endl;
using std::begin;
using std::end;

template <typename T, typename... Args>
void fruit_log(T s, Args... args) {
	cout << s << "\t";
	vector<std::string> var = {to_string(args)...};
	for (auto iter = begin(var); iter != end(var); iter++) {
		cout << *iter << " ";
	}
	cout << endl;
};
template <typename T>
void printArray(vector<T>& nums) {
	for (auto iter = begin(nums); iter < end(nums); iter++) {
		cout << *iter << "\t";
	}
	cout << endl;
}

void printList(ListNode* head)
{
	ListNode* index = head;
	while (index != nullptr) {
		cout << index->val << " ";
		index = index->next;
	}
	cout << endl;
}
// test tree related solutions
#if 0
int main(int argc, const char * argv[]) {

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
	TreeNode *node2 = new TreeNode(2);
	TreeNode *node3 = new TreeNode(3);
	TreeNode *node4 = new TreeNode(4);
	TreeNode *node5 = new TreeNode(5);
	TreeNode *node6 = new TreeNode(6);
	TreeNode *node7 = new TreeNode(7);
	TreeNode *node8 = new TreeNode(8);
	TreeNode *node9 = new TreeNode(9);

	root->left   = node2; root->right  = node3;
	node2->left  = node4; node2->right = node5;
	node3->left  = node6;
	node5->right = node7;
	node6->left  = node8; node6->right = node9;
	
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
#endif
// test list related solutions
int main()
{
	ListNode* head  = new ListNode(1);
	ListNode* node1 = new ListNode(2);
	ListNode* node2 = new ListNode(3);
	ListNode* node3 = new ListNode(4);
	ListNode* node4 = new ListNode(5);
	head->next  = node1;  node1->next = node2;
	node2->next = node3;  node3->next = node4;
	printList(head);
	
//	ListNode* l2 = new ListNode(1);
//	ListNode* n1 = new ListNode(3);
//    ListNode* n2 = new ListNode(5);
//    l2->next = n1; n1->next = n2;
//	printList(l2);
	
	ListNode* result = rotateRight(head, 10);
	printList(result);
	
    delete head;
    delete node1; delete node2;
    delete node3; delete node4;
//    delete l2;
//    delete n1; delete n2;

	return 0;
}
