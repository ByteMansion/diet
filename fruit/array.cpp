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

using std::swap;
using std::sort;

/**
 * @brief	Leetcode 31: Next Permutation
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 34%
 */
bool cmp(int& i, int& j)
{
	return (i > j);
}
void Solution_A::nextPermutation(vector<int>& nums) {
	if(nums.empty() || nums.size() == 1)
		return;
	
	int backward = int(nums.size()) - 1;;
	int foreward = backward - 1;
	while (nums[foreward] >= nums[backward]) {
		foreward--;
		backward--;
		if (foreward == -1) {
			sort(nums.begin(), nums.end());
			return;
		}
	}
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
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 99.36%
 */
void Solution_A::stl_nextPermutation(vector<int>& nums)
{
	next_permutation(nums.begin(), nums.end());
}
