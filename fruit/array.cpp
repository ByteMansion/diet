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
using std::reverse;

/**
 * @brief	Leetcode 31: Next Permutation
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 34%
 */
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
 *			This solution is implementation of STL function next_permutation.
 */
void Solution_A::stlSrc_nextPermutation(vector<int>& nums)
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
void Solution_A::stl_nextPermutation(vector<int>& nums)
{
	next_permutation(nums.begin(), nums.end());
}

/**
 * @brief	Leetcode 47: Permutation II
 *			Given a collection of numbers that might contain duplicates, return
 * 			all possible unique permutations.
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution 45%
 */
vector<vector<int>> Solution_A::permuteUnique(vector<int>& nums)
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
 */
bool permutation2(vector<int>& nums)
{
	return false;
}
vector<vector<int>> Solution_A::permuteUnique2(vector<int>& nums)
{
	vector<vector<int>> result;
	
	if (nums.empty()) {
		return result;
	}
	
	sort(nums.begin(), nums.end());
	
	result.push_back(nums);
	
	while (permutation2(nums)) {
		result.push_back(nums);
	}
	
	return result;
}

