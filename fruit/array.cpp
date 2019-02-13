/**
 * @file	array.cpp
 * @brief	All functions are solutions of leetcode problems.
 *
 * @author	Changrui
 * @date	2018/12/8
 *
 * Copyright © 2018 ChangruiShao. All rights reserved.
 */

#include "array.hpp"

#include <algorithm>
#include <deque>

using std::swap;
using std::sort;
using std::reverse;
using std::deque;

/**
 * @brief	Leetcode 31: Next Permutation
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
void nextPermutation(vector<int>& nums)
{
	if(nums.empty() || nums.size() == 1)
		return;

    // find first number which is less than its post element.
	int backward = int(nums.size()) - 1;;
	int foreward = backward - 1;
	while (nums[foreward] >= nums[backward]) {
		foreward--;
		backward--;
        // if this array is in descending order, reverse it and then return result.
		if (foreward == -1) {
			sort(nums.begin(), nums.end());
			return;
		}
	}
    // find last element, bigger than target number, which is to the right
    // of target, and then swap the two elements, sort all elements to the right of
    // target position in ascending order.
	for (int j = int(nums.size()) - 1; j >= foreward; j--) {
		if (nums[j] > nums[foreward]) {
			swap(nums[j], nums[foreward]);
			sort(nums.begin() + backward, nums.end());
			return;
		}
	}
}

/**
 * @brief	Leetcode 31: Next Permutation
 *	This solution is implementation of STL function next_permutation.
 */
void nextPermutation2(vector<int>& nums)
{
	auto last = nums.end();
	auto first = nums.begin();
	if (last == first || first == last-1) {
		return;
	}
	auto i = nums.end()-1;
	while (true) {
		auto ip = i;
		if (*--i < *ip) {
			auto j = nums.end();
			while (*i >= *--j)
				;
			swap(*i, *j);
			sort(ip, last);
			return;
		}
		if (i == first) {
			sort(first, last);
			return;
		}
	}
}
/**
 * @brief	Leetcode 31: Next Permutation
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 99.36%
 */
void nextPermutation3(vector<int>& nums)
{
	next_permutation(nums.begin(), nums.end());
}

/**
 * @brief	Leetcode 47: Permutation II
 *			Given a collection of numbers that might contain duplicates, return
 * 			all possible unique permutations.
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
vector<vector<int>> permuteUnique(vector<int>& nums)
{
	vector<vector<int>> result;

	if (nums.empty() || nums.size() == 0) {
		return result;
	}
	sort(nums.begin(), nums.end());
	result.push_back(nums);
	while (next_permutation(nums.begin(), nums.end())) {
		result.push_back(nums);
	}


	return result;
}

/**
 * @brief	Leetcode 47: Permutation II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
vector<vector<int>> permuteUnique2(vector<int>& nums)
{
	vector<vector<int>> result;

	if (nums.empty()) {
		return result;
	}

	sort(nums.begin(), nums.end());
	result.push_back(nums);

	while (1) {
        nextPermutation(nums);
        if(nums == result[0]) {
            break;
        }
		result.push_back(nums);
	}

	return result;
}

/**
 * @brief   Leetcode 46: Permutations
 *
 */
vector<vector<int>> permute(vector<int>& nums)
{
    return permuteUnique(nums);
}

/**
 * @brief   Leetcode 950: Reveal Cards In Increasing Order
 *  This method using less time, but more space.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
vector<int> deckRevealedIncreasing(vector<int>& deck)
{
    if(deck.empty() || deck.size() == 1) {
        return deck;
    }

    // reverse order sort
    sort(deck.rbegin(), deck.rend());

    deque<int> dResult;
    dResult.push_front(deck[0]);
    for(int i = 1; i < deck.size(); ++i) {
        dResult.push_front(dResult.back());
        dResult.pop_back();
        dResult.push_front(deck[i]);
    }

    vector<int> res(dResult.begin(), dResult.end());
    return res;
}

/**
 * @brief   Leetcode 15: 3Sum
 *  This method costs too much time and space.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 11.7%
 */
static void twoSum(vector<int>& nums, int start, int end, int sum,
           vector<vector<int>>& results)
{
    while(start < end) {
        vector<int> ele;
        ele.push_back(-1 * sum);
        if(nums[start] + nums[end] < sum) {
            start++;
        } else if(nums[start] + nums[end] > sum) {
            end--;
        } else {
            ele.push_back(nums[start]);
            ele.push_back(nums[end]);
            results.push_back(ele);
            ele.clear();
			while(start < end && nums[start] == nums[start+1]) start++;
			while(start < end && nums[end] == nums[end-1]) end--;
            start++;
            end--;
        }
    }
}
vector<vector<int>> threeSum(vector<int>& nums)
{
    vector<vector<int>> results;
    if(nums.empty() || nums.size() < 3) {
        return results;
    }

    sort(nums.begin(), nums.end());
    int index = 0;
    while(index < nums.size()-2) {
        twoSum(nums, index+1, int(nums.size()-1), -1*nums[index], results);

        while((index+1 < nums.size()-2) && (nums[index] == nums[index+1])) {
            index++;
        }
		index += 1;
    }

    return results;
}

/**
 * @brief   Leetcode 15: 3Sum
 *  This method integrates above two functions into one. Actually, internal 
 *  solution is as same, but costs less time and space.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 90.6%
 */
vector<vector<int>> threeSum2(vector<int>& nums)
{
    vector<vector<int>> res;
    if(nums.empty() || nums.size() < 3) {
        return res;
    }

    sort(nums.begin(), nums.end());
    for(int i = 0; i < nums.size()-2; ++i) {
        if(i > 0 && nums[i] == nums[i-1]) continue;

        int twoSum = -1 * nums[i];
        int nLeft = i + 1;
        int nRight = nums.size() - 1;
        while(nLeft < nRight) {
            if(nums[nLeft] + nums[nRight] == twoSum) {
                res.push_back(vector<int>{nums[i], nums[nLeft], nums[nRight]});
                while(nLeft < nRight && nums[nLeft] == nums[nLeft+1]) nLeft++;
                while(nLeft < nRight && nums[nRight] == nums[nRight-1]) nRight--;
                nLeft++;
                nRight--;
            } else if(nums[nLeft] + nums[nRight] > twoSum) {
                nRight--;
            } else {
                nLeft++;
            }
        }
    }

    return res;
}

/**
 * @brief   Leetcode 16: 3Sum Closest
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 95.8%
 */
int threeSumClosest(vector<int>& nums, int target)
{
    int result;
    int minGap = INT_MAX
    sort(nums.begin(), nums.end());

    for(int i = 0; i < nums.size()-2; ++i) {
        int nLeft = i + 1;
        int nRight = nums.size() - 1;
        while(nLeft < nRight) {
            int gap = target - (nums[i] + nums[nLeft] + nums[nRight]);
            if(std::abs(gap) < result) {
                minGap = std::abs(gap);
                result = nums[i] + nums[nLeft] + nums[nRight];
            }
            if(gap > 0) {
                nLeft++;
            } else if(gap < 0){
                nRight--;
            } else {
                return result;
            }
        }
    }

    return result;
}

/**
 * @brief   Leetcode 18: 4Sum
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 73%
 */
static void threeSumHelper(vector<int>& nums, int start, int sum,
                      vector<vector<int>>& results)
{
    for(int i = start; i < nums.size()-2; ++i) {
        if(i > start && nums[i] == nums[i-1]) continue;

        int nLeft = i + 1;
        int nRight = nums.size() - 1;
        while(nLeft < nRight) {
            if(nums[i] + nums[nLeft] + nums[nRight] == sum) {
                results.push_back(vector<int>{nums[start-1], nums[i], nums[nLeft], nums[nRight]});
                while(nLeft < nRight && nums[nLeft] == nums[nLeft+1]) nLeft++;
                while(nLeft < nRight && nums[nRight] == nums[nRight-1]) nRight--;
                nLeft++;
                nRight--;
            } else if(nums[i] + nums[nLeft] + nums[nRight] < sum) {
                nLeft++;
            } else {
                nRight--;
            }
        }
    }
}
vector<vector<int>> fourSum(vector<int>& nums, int target)
{
    vector<vector<int>> results;
    if(nums.empty() || nums.size() < 4) {
        return results;
    }

    sort(nums.begin(), nums.end());
    for(int i = 0; i < nums.size()-3; ++i) {
        if(i > 0 && nums[i] == nums[i-1]) continue;

        int sum = target - nums[i];
        threeSumHelper(nums, i+1, sum, results);
    }

    return results;
}

/**
 * @brief   Leetcode 18: 4Sum
 *  This method integrates above two functions into one, and then adds some extra conditions to
 *  decrease unnecessary search iterations.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 100%
 */
vector<vector<int>> fourSum2(vector<int>& nums, int target)
{
    vector<vector<int>> results;
    if(nums.empty() || nums.size() < 4) {
        return results;
    }
    sort(nums.begin(), nums.end());
    size_t length = nums.size();
    for(int i = 0 ; i < length-3; ++i) {
        if(nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target) break;
        if(nums[i] + nums[length-3] + nums[length-2] + nums[length-1] < target) continue;

        if(i > 0 && nums[i] == nums[i-1]) continue;
        for(int j = i+1; j < length-2; ++j) {
            if(nums[i] + nums[j] + nums[j+1] + nums[j+2] > target) break;
            if(nums[i] + nums[j] + nums[length-2] + nums[length-1] < target) continue;

            if(j > i+1 && nums[j] == nums[j-1]) continue;
            int nLeft = j+1;
            int nRight = length - 1;
            while(nLeft < nRight) {
                int sum = nums[i] + nums[j] + nums[nLeft] + nums[nRight];
                if(sum == target) {
                    results.push_back(vector<int>{nums[i], nums[j], nums[nLeft], nums[nRight]});
                    while(nLeft < nRight && nums[nLeft] == nums[nLeft+1]) nLeft++;
                    while(nLeft < nRight && nums[nRight] == nums[nRight-1]) nRight--;
                    nLeft++;
                    nRight--;
                } else if(sum < target) {
                    nLeft++;
                } else {
                    nRight--;
                }
            }
        }
    }

    return results;
}
