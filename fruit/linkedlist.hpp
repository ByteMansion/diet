/**
 * @brief	solutions of leetcode problems related to linked list
 *
 * @author	Changrui
 * @date	2019/1/7
 *
 * Copyright © 2018 ChangruiShao. All rights reserved.
 */

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution_l {
public:
    // Leetcode 92: Reverse Linked List II
    ListNode* reverseBetween(ListNode* head, int m, int n);

private:
    ListNode* head;
}
