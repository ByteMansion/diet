/**
 * @file	linkedlist.cpp
 * @brief	All function implementations related to linked list
 *
 * @author	Changrui
 * @date	2019/1/7
 *
 * Copyright © 2019 ChangruiShao. All rights reserved.
 */

#include "linkedlist.hpp"

#include <vector>
#include <queue>
#include <algorithm>
#include <map>

using std::vector;
using std::priority_queue;
using std::less;
using std::greater;
using std::move;
using std::queue;
using std::find;
using std::map;

/**
 * @brief   Leetcode 92: Reverse Linked List II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 55%
 */
ListNode* reverseBetween(ListNode* head, int m, int n)
{
    if(head == nullptr || m == n) {
        return head;
    }
	// This solution is saving the values between m and n, and then
	// assign them to the pointers in reverse order.
    vector<int> valBetween;
    ListNode* index = head;
    int len = 0;
    while(index != nullptr) {
        len += 1;
        if(len >= m && len <= n) {
            valBetween.push_back(index->val);
        }
        index = index->next;
    }

    index = head;
    len = 1;
    size_t scope = valBetween.size();
    while(index != nullptr) {
        if(len >= m && len <= n) {
            index->val = valBetween[scope-len+m-1];
        }
        len++;
        index = index->next;
    }

    return head;
}
/**
 * @brief   Leetcode 92: Reverse Linked List II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 55%
 */
ListNode* reverseBetween2(ListNode* head, int m, int n)
{
	// This solution is setting flags before and behind the target
	// scope, and then reversing the directions of those pointers.
	if(head == nullptr || m == n) {
		return nullptr;
	}
	// flags
	ListNode* front  = nullptr;
	ListNode* back   = nullptr;
	ListNode* nodeM  = nullptr;
	ListNode* nodeN  = nullptr;
	
	ListNode* prev   = nullptr;
	ListNode* behind = nullptr;
	ListNode* node  = head;
	int index = 1;
	while(node != nullptr) {
		// set flag
		if(index == m-1)
			front = node;
		if(index == m)
			nodeM = node;
		if(index == n) {
			nodeN = node;
			back = node->next;
		}
		
		if(index > m && index <= n) {
			// reverse node pointers
			behind = node->next;
			if(index == m+1)
				prev = nodeM;
			node->next = prev;
			prev = node;
			node = behind;
		} else {
			node = node->next;
		}
		index += 1;
	}
	// establish link
	nodeM->next = back;
	if(front != nullptr)
		front->next = nodeN;
	else
		head = nodeN;
	
	return head;
}

/**
 * @brief	Leetcode 21: Merge Two Sorted Lists
 *
 */
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2)
{
    if(l1 == nullptr && l2 == nullptr) {
        return nullptr;
    } else if(l1 == nullptr) {
        return l2;
    } else if(l2 == nullptr) {
        return l1;
    }

    ListNode* head = new ListNode(-1);
    ListNode* index = head;
    while(l1 != nullptr && l2 != nullptr) {
        if(l1->val > l2->val) {
            index->next = l2;
            l2 = l2->next;
        } else {
            index->next = l1;
            l1 = l1->next;
        }
        index = index->next;
    }
    if(l1 == nullptr) index->next = l2;
    if(l2 == nullptr) index->next = l1;

    ListNode* result = head->next;
    delete head;
    return result;
}

/**
 * @brief	Leetcode 23: Merge k Sorted Lists
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 65%
 */
ListNode* mergeKLists(vector<ListNode*>& lists)
{
    if(lists.empty())
        return nullptr;

    ListNode* index = nullptr;
    ListNode* head = nullptr;
    auto cmp = [](ListNode* m, ListNode* n){return (m->val > n->val);};
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pQueue(cmp);
    ListNode* node = nullptr;
    for(int i = 0; i < lists.size(); i++) {
        node = lists[i];
        if(node != nullptr) {
            pQueue.push(node);
            node = node->next;
        }
    }

    while(!pQueue.empty()) {
        node = pQueue.top();
        pQueue.pop();
        if(index == nullptr) {
            index = node;
            head = index;
        } else {
            index->next = node;
            index = index->next;
        }
        node = node->next;
        if(node != nullptr) {
            pQueue.push(node);
        }
    }

    return head;
}


/**
 * @brief	Leetcode 23: Merge k Sorted Lists
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 65%
 */
static ListNode* divideAndConquerSortedLists(vector<ListNode*>& lists, int start, int end)
{
    ListNode* result = nullptr;
    if(start+1 < end) {
        ListNode* result1 = divideAndConquerSortedLists(lists, start, (start+end)/2);
        ListNode* result2 = divideAndConquerSortedLists(lists, (start+end)/2+1, end);
        result = mergeTwoLists(result1, result2);
    } else if(start+1 == end) {
        return mergeTwoLists(lists[start], lists[end]);
    } else if(start == end) {
        return lists[start];
    }
    return result;
}

ListNode* mergeKLists2(vector<ListNode*>& lists)
{
    if(lists.empty() || lists.size() == 0) {
        return nullptr;
    }
    if(lists.size() == 1) {
        return lists[0];
    }

    // devide and conquer
    ListNode* result = divideAndConquerSortedLists(lists, 0, (int)lists.size()-1);

    return result;
}

/**
 * @brief	Leetcode 61: Rotate List
 *
 */
ListNode* rotateRight(ListNode* head, int k)
{
	if (head == nullptr || k == 0) {
		return head;
	}
	// get the length of this list and rotate position
	ListNode* index = head;
	size_t length = 0;
	while (index != nullptr) {
		index = index->next;
		length++;
	}
	k = k % length;
	if (k == 0) {
		return head;
	}
	// set flag
	ListNode* prev = nullptr;
	ListNode* post = nullptr;
	ListNode* tail = nullptr;
	index = head;
	size_t position = 1;
	while (index != nullptr) {
		if (position == length - k) {
			prev = index;
			post = index->next;
		}
		if (index->next == nullptr) {
			tail = index;
		}
		index = index->next;
		position++;
	}
	// adjust pointers
	tail->next = head;
	prev->next = nullptr;
	
	return post;
}

/**
 * @brief	Leetcode 725: Split Linked List in Parts
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 99%
 */
vector<ListNode*> splitListToParts(ListNode* root, int k)
{
	if (root == nullptr) {
		return vector<ListNode*>(k, nullptr);
	}
	if (k == 1) {
		return vector<ListNode*>(1, root);
	}
	// get the length of this list
	ListNode* index = root;
	size_t length = 0;
	while (index != nullptr) {
		index = index->next;
		length++;
	}
	
	vector<ListNode*> result(k, nullptr);
	// fill result vector with nodes in list
	// last elements in list maybe nullptr
	if (k >= length) {
		index = root;
		size_t position = 0;
		while (index != nullptr) {
			result[position++] = index;
			ListNode* post = index->next;
			index->next = nullptr;
			index = post;
		}
	} else {
		// all elements in list are not nullptr
		size_t dist = length / k;  // minimal distance of each element in result
		size_t mode = length % k;  // count of maximum distance elements in result
		
		size_t distance = dist;  // distance of each element in result
		size_t position = 0;  // position of elements in result
		size_t distCnt  = 0;
		index = root;
		while (index != nullptr) {
			if(position < mode) {
				distance = dist + 1;
			} else {
				distance = dist;
			}
			distCnt++;
			if(distCnt == distance) {
				result[position++] = root;
				root = index->next;
				index->next = nullptr;
				index = root;
				distCnt = 0;
			} else {
				index = index->next;
			}
		}
	}
	
	return result;
}

/**
 * @brief	Leetcode 328: Odd Even Linked List
 *
 */
ListNode* oddEvenList(ListNode* head)
{
	if (head == nullptr) {
		return nullptr;
	}
	if (head->next == nullptr) {
		return head;
	}
	ListNode* odd    = head;
	ListNode* even   = head->next;
	ListNode* cornor = even;
	ListNode* index  = head;
	size_t    pos    = 0;
	
	while (index != nullptr) {
		pos++;
		if (pos < 3) {
			index = index->next;
			continue;
		}
		ListNode* post = index->next;
		if (pos % 2) {
			odd->next = index;
			odd = odd->next;
		} else {
			even->next = index;
			even = even->next;
		}
		index = post;
	}

	odd->next = cornor;
	even->next = nullptr;
	
	return head;
}

/**
 * @brief   Leetcode 138: Copy List with Random Pointer
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 2.75%
 * Space complexity is O(n), time complexity is O(n).
 */
RandomListNode* copyRandomList(RandomListNode* head)
{
    if(head == nullptr) {
        return nullptr;
    }

	vector<RandomListNode*> visited;
    RandomListNode* index = head;
    RandomListNode* randomHead = nullptr;
	RandomListNode* iResult = nullptr;
    map<RandomListNode*, RandomListNode*> mapping;  // map new cloned node to old one
    while(index != nullptr) {
        // copy unvisited node
		if (find(visited.begin(), visited.end(), index) == visited.end()) {
			iResult = new RandomListNode(index->label);
			visited.push_back(index);
            mapping[index] = iResult;
			if (randomHead == nullptr) {
				randomHead = iResult;
			}
		}
		// copy next pointer
        if(index->next != nullptr) {
        	auto pNode = find(visited.begin(), visited.end(), index->next);
        	if (pNode == visited.end()) {
                RandomListNode* newNode = new RandomListNode(index->next->label);
                iResult->next = newNode;
                visited.push_back(index->next);
                mapping[index->next] =  iResult->next;
            } else {
                iResult->next = mapping[index->next];
            }
        }
		// copy random pointer
        if(index->random != nullptr) {
            auto pNode = find(visited.begin(), visited.end(), index->random) ;
            if (pNode == visited.end()) {
                RandomListNode* newNode = new RandomListNode(index->random->label);
                iResult->random = newNode;
                visited.push_back(index->random);
                mapping[index->random] =  iResult->random;
            } else {
                iResult->random = mapping[index->random];
            }
        }

		// iterate
		index = index->next;
		iResult = iResult->next;
    }

    return randomHead;
}

/**
 * @brief   Leetcode 138: Copy List with Random Pointer
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution %
 */
RandomListNode* copyRandomList2(RandomListNode* head)
{
    if(head == nullptr) {
        return nullptr;
    }
    // set new cloned node behind original node
    RandomListNode* index = head;
    RandomListNode* iResult = nullptr;
    RandomListNode* iPost = nullptr;
    while(index != nullptr) {
        iResult = new RandomListNode(index->label);
        iPost   = index->next;
        index->next = iResult;
        iResult->next = iPost;
        index = index->next->next;
    }
    // set random pointer of cloned pointer
    index = head;
    while(index != nullptr) {
        index->next->random = index->random->next;
        index = index->next->next;
    }

    // get new cloned list by changing pointer direction
    index = head;
    RandomListNode* randomHead = head->next;
    while(index != nullptr) {
        iResult = index->next;
        iPost = index->next->next;
        index->next = iPost;
        iResult->next = iPost->next;
        index = iPost;
    }

    return randomHead;
}
