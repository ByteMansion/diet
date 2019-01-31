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
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <set>

using std::vector;
using std::priority_queue;
using std::less;
using std::greater;
using std::move;
using std::queue;
using std::find;
using std::map;
using std::stack;
using std::unordered_map;
using std::unordered_set;
using std::set;

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
 * Accepted Solutions Runtime Distribution 97%
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
		if (index->random != nullptr) {
			index->next->random = index->random->next;
		}
        index = index->next->next;
    }

    // get new cloned list by changing pointer direction
    index = head;
    RandomListNode* randomHead = head->next;
    while(index != nullptr) {
        iResult = index->next;
        iPost = index->next->next;
        index->next = iPost;
		if (iPost != nullptr) {
			iResult->next = iPost->next;
		}
        index = iPost;
    }

    return randomHead;
}

/**
 * Leetcode 82: Remove Duplicates from Sorted List II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */

ListNode* deleteDuplicates(ListNode* head)
{
    if(head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* resultHead  = nullptr;
    ListNode* resultIndex = nullptr;
    ListNode* index       = head;
    size_t    cnt         = 1;

    while(index != nullptr) {
        while(index->next != nullptr && index->next->val == index->val) {
            index = index->next;
            cnt++;
        }
        if(cnt == 1) {
            if(resultIndex == nullptr) {
                resultIndex = index;
                resultHead = resultIndex;
            } else {
                resultIndex->next = index;
                resultIndex = resultIndex->next;
            }
        }

        index = index->next;
        cnt = 1;
    }
    if(resultIndex != nullptr) {
        resultIndex->next = nullptr;
    }

    return resultHead;
}

/**
 * @brief   Leetcode 86: Pertition List
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
ListNode* partition(ListNode* head, int x)
{
    if(head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* resultHead = nullptr;
    ListNode* lessIndex = nullptr;
    ListNode* greatIndex = nullptr;
    ListNode* index = head;

    while(index != nullptr) {
        if(index->val < x) {
            if(lessIndex == nullptr) {
                lessIndex = index;
                resultHead = lessIndex;
            } else {
                lessIndex->next = index;
                lessIndex = lessIndex->next;
            }
        } else {
            if(greatIndex == nullptr) {
                greatIndex = index;
                head = greatIndex;
            } else {
                greatIndex->next = index;
                greatIndex = greatIndex->next;
            }
        }
        index = index->next;
    }
    if(lessIndex != nullptr && greatIndex != nullptr) {
        lessIndex->next = head;
        greatIndex->next = nullptr;
    } else {
        resultHead = head;
    }


    return resultHead;
}

/**
 * @brief   Leetcode 143: Reorder List
 *  This method uses a map to save half list. Space complexity is 
 *  O(n), time complexity is O(n).
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 65%
 */
void reorderList(ListNode* head)
{
    if(head == nullptr || head->next == nullptr) {
        return;
    }

    ListNode* index = head;
    map<size_t, ListNode*> mList;
    size_t nodeCnt = 0;
    size_t halfCnt = 0;

    while(index != nullptr) {
        nodeCnt++;
        index = index->next;
    }

    if(nodeCnt % 2) {
        halfCnt = nodeCnt / 2 + 1;
    } else {
        halfCnt = nodeCnt / 2;
    }

    size_t num = 1;
    index = head;
    while(num <= halfCnt) {
        mList[num++] = index;
        index = index->next;
    }

    num = nodeCnt / 2;
    while(index != nullptr) {
        ListNode* post = mList[num]->next;
        ListNode* postIndex = index->next;
        mList[num]->next = index;
        if(num == nodeCnt / 2){
           if(nodeCnt % 2) {
               index->next = mList[halfCnt];
               mList[halfCnt]->next = nullptr;
           } else {
               index->next = nullptr;
            }
        } else {
            index->next = post;
        }
        index = postIndex;
        num--;
    }
}

/**
 * @brief   Leetcode 143: Reorder List
 *  This method traverses list two times and space complexity is
 *  O(1), time complexity is O(n).
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
static ListNode* reverseList(ListNode* head)
{
    if(head == nullptr || head->next == nullptr) {
        return head;
    }
    ListNode* last = nullptr;
    ListNode* post = nullptr;
    ListNode* index = head;
    while(index != nullptr) {
        post = index->next;
        index->next = last;
        last = index;
        index = post;
    }

    return last;
}
void reorderList2(ListNode* head)
{
    if(head == nullptr || head->next == nullptr) {
        return;
    }

    ListNode* index = head;
    size_t length = 0;
    while(index != nullptr) {
        length++;
        index = index->next;
    }

    size_t halfLength = 0;
    if(length % 2) {
        halfLength = length / 2 + 1;
    } else {
        halfLength = length / 2;
    }

    size_t num = 1;
    index = head;
    while(num++ < halfLength) {
        index = index->next;
    }

    ListNode* middleIndex = reverseList(index->next);
    index->next = nullptr;

    index = head;
    while(middleIndex != nullptr) {
        ListNode* post = index->next;
        ListNode* middlePost = middleIndex->next;
        index->next = middleIndex;
        middleIndex->next = post;
        middleIndex = middlePost;
        index = post;
    }
}

/**
 * @brief   Leetcode 445: Add Two Numbers II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 99%
 */
static size_t getLengthofList(ListNode* head)
{
    if(head == nullptr) {
        return 0;
    }
    ListNode* index = head;
    size_t length = 0;
    while(index != nullptr) {
        length++;
        index = index->next;
    }

    return length;
}
ListNode* addTwoNumbers(ListNode* index1, ListNode* index2)
{
    size_t length1 = getLengthofList(index1);
    size_t length2 = getLengthofList(index2);

    if(length1 < length2) {
        ListNode* tmp = index1;
        index1 = index1;
        index2 = tmp;
    }
    ListNode* result = index1;

    stack<ListNode*> sList1;
    stack<ListNode*> sList2;
    while(index1 != nullptr) {
        sList1.push(index1);
        index1 = index1->next;
    }
    while(index2 != nullptr) {
        sList2.push(index2);
        index2 = index2->next;
    }
    size_t sum = 0;
    size_t increase = 0;
    while(!sList1.empty() && !sList2.empty()) {
        index1 = sList1.top();
        sList1.pop();
        index2 =sList2.top();
        sList2.pop();
        sum = index1->val + index2->val + increase;
        index1->val = sum % 10;
        increase = sum / 10;
    }
    while(!sList1.empty()) {
        index1 = sList1.top();
        sList1.pop();
        sum = index1->val + increase;
        index1->val = sum % 10;
        increase = sum / 10;
    }
    if(increase != 0) {
        ListNode* node = new ListNode(1);
        node->next = result;
        result = node;
    }

    return result;
}

/**
 * Leetcode 148: Sort List
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 71%
 */
ListNode* sortList(ListNode* head)
{
    if(head == nullptr || head->next == nullptr) {
        return head;
    }

    ListNode* index = head;
    auto cmp = [](ListNode* m, ListNode* n){return (m->val > n->val);};
    priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> pQueue(cmp);

    while(index != nullptr) {
        pQueue.push(index);
        index = index->next;
    }
    ListNode* result = nullptr;
    ListNode* front = nullptr;
    while(!pQueue.empty()) {
        front = pQueue.top();
        if(result == nullptr) {
            index = front;
            result = index;
        } else {
            index->next = front;
            index = index->next;
        }
        pQueue.pop();
    }
    front->next = nullptr;

    return result;

}

/**
 * @brief   Leetcode 148: Sort List
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
static ListNode* mergeList(ListNode* left, ListNode* right)
{
    ListNode dummy(INT_MIN);
    ListNode* tail = &dummy;

    while(left && right) {
        if(left->val < right->val) {
            tail->next = left;
            left = left->next;
        } else {
            tail->next = right;
            right = right->next;
        }

        tail = tail->next;
    }

    tail->next = (left == nullptr) ? right : left;

    return dummy.next;
}
/**
 * The key of this question is how to find the middle node of a list.
 * In each iteration, fast node moves forward two steps, one step ahead of slow node.
 * Finally, the node before slow node is the middle of list when fast node hits the tail.
 */
static ListNode* sortListHelperMergeSort(ListNode* head)
{
    if(head == nullptr || head->next == nullptr) {
        return head;
    }
    if(head->next->next == nullptr) {
        ListNode* left = head;
        ListNode* right = head->next;
        left->next = nullptr;
        return mergeList(left, right);
    }

    ListNode* fast = head;
    ListNode* slow = head;
    ListNode* pslow = head;
    while(fast != nullptr) {
        if(fast->next == nullptr) {
            break;
        }
        fast = fast->next->next;
        if(pslow != slow) {
            pslow = slow;
        }
        slow = slow->next;
    }
    pslow->next = nullptr;
    ListNode* left = sortListHelperMergeSort(head);
    ListNode* right = sortListHelperMergeSort(slow);
    return mergeList(left, right);
}

ListNode* sortList2(ListNode* head)
{
    return sortListHelperMergeSort(head);
}

/**
 * @brief   Swap Nodes in Pairs
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
ListNode* swapPairs(ListNode* head)
{
	if (head == nullptr || head->next == nullptr) {
		return head;
	}
	
	ListNode dummy(INT_MIN);
	ListNode* index = head;
	ListNode* prev = &dummy;
	while (index != nullptr && index->next != nullptr) {
		ListNode* last = index->next->next;
		ListNode* post = index->next;
		index->next = last;
		post->next = index;
		prev->next = post;
		
		prev = index;
		index = last;
	}
	
	return dummy.next;
}

/**
 * @brief   Leetcode 25: Reverse Nodes in k-Group
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
static ListNode* getKthNode(ListNode* head, int k) {
	if(head == nullptr) {
		return nullptr;
	}
    int i = 1;
    while(i < k) {
        if(head->next == nullptr) {
			return nullptr;
        }
        head = head->next;
        i += 1;
    }
	return head;
}
static ListNode* reverseList(ListNode* first, ListNode* end)
{
    ListNode* index = first;
    ListNode* last = end;
    ListNode* post = nullptr;
    while(index != end) {
        post = index->next;
        index->next = last;
        last = index;
        index = post;
    }
    return last;
}

ListNode* reverseKGroup(ListNode* head, int k)
{
    if(k <= 1 || head == nullptr) {
        return head;
    }

    ListNode dummy(INT_MIN);
    ListNode* index = head;
    ListNode* prev = &dummy;
	ListNode* end = nullptr;

    while(index != nullptr) {
		ListNode* last = getKthNode(index, k);
		if (last == nullptr) {
            if(dummy.next == nullptr) {
                dummy.next = index;
            }
			break;
		}
        end = last->next;
        prev->next = reverseList(index, end);
        prev = index;
        index = end;
    }

    return dummy.next;
}

/**
 * @brief   Leetcode 141: Linked List Cycle
 *  This solution has high space complexity O(n).
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 0.82%
 */
bool hasCycle(ListNode* head)
{
    if(head == nullptr || head->next == nullptr) {
        return false;
    }

    set<ListNode*> sList;
    while(head != nullptr) {
        if(find(sList.begin(), sList.end(), head) != sList.end()) {
            return true;
        }
        sList.insert(head);
        head = head->next;
    }

    return false;
}
 /**
  * @brief  Leetcode 141: Linked List Cycle
  *  This method decreases space complexity to O(1) using two pointers --
  *  one moves fast, but another slow. If the linked list has a cycle, fast pointer and 
  *  slow pointer meet at certain node finally.
  *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
  */
bool hasCycle2(ListNode* head)
{
    if(head == nullptr || head->next == nullptr) {
        return false;
    }
    ListNode* fast = head->next->next;
    ListNode* slow = head;
    while(fast != slow) {
        if(fast == nullptr) {
            return false;
        }
        slow = slow->next;
        if(fast->next) {
            fast = fast->next->next;
        } else {
            fast = fast->next;
        }
    }

    return true;
}

/**
 * @brief   Leetcode 142: Linked List Cycle II
 *  This method needs O(n) extra space.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 0.87%
 */
ListNode* detectCycle(ListNode* head)
{
    if(head == nullptr || head->next == nullptr) {
        return nullptr;
    }

    unordered_set<ListNode*> sList;
    ListNode* index = head;
    while(index != nullptr) {
        if(find(sList.begin(), sList.end(), index) != sList.end()) {
            return index;
        }
        sList.insert(index);
        index = index->next;
    }

    return nullptr;
}

/**
 * @brief   Leetcode 142: Linked List Cycle II
 *	Floyd's cycle detection algorithm
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
ListNode* detectCycle2(ListNode* head)
{
	ListNode* fast = head;
	ListNode* slow = head;
	while (fast && slow && fast->next) {
		fast = fast->next->next;
		slow = slow->next;
		if (fast == slow) {
			slow = head;
			while (slow != fast) {
				slow = slow->next;
				fast = fast->next;
			}
			return slow;
		}
	}

	return nullptr;
}

/**
 * @brief   Leetcode 430: Flatten a Multilevel Doubly Linked List
 *
 */
Node* flatten(Node* head)
{
    if(head == nullptr) {
        return nullptr;
    }
    Node* resultHead = head;
    while(head != nullptr) {
        if(head->child == nullptr) {
            head = head->next;
        } else {
            Node* post = head->next;
            Node* childHead = flatten(head->child);
            Node* index = childHead;
            while(index != nullptr) {
                index = index->next;
            }
            head->child = nullptr;
            head->next = childHead;
            index->prev->next = post;
            head = post;
        }
    }

    return resultHead;
}
