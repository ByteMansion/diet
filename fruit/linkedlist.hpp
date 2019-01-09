/**
 * @file    linkedlist.hpp
 * @brief	Data structures and function declarations
 *
 * @author	Changrui
 * @date	2019/1/7
 *
 * Copyright © 2018 ChangruiShao. All rights reserved.
 */

#ifndef linkedlist_hpp
#define linkedlist_hpp

#include <cstdio>
#include <vector>

using std::vector;

struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};


// Leetcode 92: Reverse Linked List II
ListNode* reverseBetween(ListNode* head, int m, int n);
ListNode* reverseBetween2(ListNode* head, int m, int n);

// Leetcode 23: Merge k Sorted Lists
ListNode* mergeKLists(vector<ListNode*>& lists);


#endif
