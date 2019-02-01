/**
 * @file    linkedlist.hpp
 * @brief	Data structures and function declarations
 *
 * @author	Changrui
 * @date	2019/1/7
 *
 * Copyright © 2019 ChangruiShao. All rights reserved.
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

struct RandomListNode {
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(nullptr), random(nullptr) {}
};

class Node {
public:
    int val;
    Node* prev;
    Node* next;
    Node* child;

    Node() {}

    Node(int _val, Node* _prev, Node* _next, Node* _child) {
        val = _val;
        prev = _prev;
        next = _next;
        child = _child;
    }
};

// Leetcode 92: Reverse Linked List II
ListNode* reverseBetween(ListNode* head, int m, int n);
ListNode* reverseBetween2(ListNode* head, int m, int n);

// Leetcode 21: Merge Two Sorted Lists
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2);

// Leetcode 23: Merge k Sorted Lists
ListNode* mergeKLists(vector<ListNode*>& lists);
ListNode* mergeKLists2(vector<ListNode*>& lists);

// Leetcode 61: Rotate List
ListNode* rotateRight(ListNode* head, int k);

// Leetcode 725: Split Linked List in Parts
vector<ListNode*> splitListToParts(ListNode* root, int k);

// Leetcode 328: Odd Even Linked List
ListNode* oddEvenList(ListNode* head);

// Leetcode 138: Copy List with Random Pointer
RandomListNode* copyRandomList(RandomListNode* head);
RandomListNode* copyRandomList2(RandomListNode* head);

// Leetcode 82: Remove Duplicates from Sorted List II
ListNode* deleteDuplicates(ListNode* head);

// Leetcode 86: Partition List
ListNode* partition(ListNode* head, int x);

// Leetcode 143: Reorder List
void reorderList(ListNode* head);
void reorderList2(ListNode* head);

// Leetcode 445: Add Two Numbers II
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);

// Leetcode 148: Sort List
ListNode* sortList(ListNode* head);
ListNode* sortList2(ListNode* head);

// Leetcode 24: Swap Nodes in Pairs
ListNode* swapPairs(ListNode* head);

// Leetcode 25: Reverse Nodes in k-Group
ListNode* reverseKGroup(ListNode* head, int k);

// Leetcode 141: Linked List Cycle
bool hasCycle(ListNode* head);
bool hasCycle2(ListNode* head);

// Leetcode 142: Linked List Cycle II
ListNode* detectCycle(ListNode* head);
ListNode* detectCycle2(ListNode* head);

// Leetcode 430: Flatten a Multilevel Doubly Linked List
Node* flatten(Node* head);

// Leetcode 147: Insertion Sort List
ListNode* insertionSortList(ListNode* head);

// Leetcode 817: Linked List Components
int numComponents(ListNode* head, vector<int>& G);
int numComponents2(ListNode* head, vector<int>& G);

// Leetcode 234: Palindrome Linked List
bool isPalindrome(ListNode* head);


#endif
