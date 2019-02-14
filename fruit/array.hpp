/**
 * @file	array.hpp
 * @brief	Data structures and function declarations
 *
 * @author	Changrui
 * @date	2018/11/28
 *
 * Copyright © 2018 ChangruiShao. All rights reserved.
 */

#ifndef _array_hpp
#define _array_hpp

#include <stdio.h>
#include <vector>

using std::vector;

// Leetcode 31: Next Permutation
void nextPermutation(vector<int>& nums);
void nextPermutation2(vector<int>& nums);
void nextPermutation3(vector<int>& nums);

// Leetcode 46: Permutation
vector<vector<int>> permute(vector<int>& nums);
vector<vector<int>> permute2(vector<int>& nums);

// Leetcode 47: Permutation II
vector<vector<int>> permuteUnique(vector<int>& nums);
vector<vector<int>> permuteUnique2(vector<int>& nums);
vector<vector<int>> permuteUnique3(vector<int>& nums);

// Leetcode 950: Reveal Cards In Increasing Order
vector<int> deckRevealedIncreasing(vector<int>& deck);

// Leetcode 15: 3Sum
vector<vector<int>> threeSum(vector<int>& nums);
vector<vector<int>> threeSum2(vector<int>& nums);

// Leetcode 16: 3Sum Closest
int threeSumClosest(vector<int>& nums, int target);

// Leetcode 18: 4Sum
vector<vector<int>> fourSum(vector<int>& nums, int target);
vector<vector<int>> fourSum2(vector<int>& nums, int target);

// Leetcode 454: 4Sum II
int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D);

// Leetcode 78: Subsets
vector<vector<int>> subsets(vector<int>& nums);
vector<vector<int>> subsets2(vector<int>& nums);
vector<vector<int>> subsets3(vector<int>& nums);

// Leetcode 90: Subsets II
vector<vector<int>> subsetsWithDup(vector<int>& nums);
vector<vector<int>> subsetsWithDup2(vector<int>& nums);



#endif /* array_hpp */
