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

// Leetcode 77: Combinations
vector<vector<int>> combine(int n, int k);
vector<vector<int>> combine2(int n, int k);
vector<vector<int>> combine3(int n, int k);

// Leetcode 39: Combination Sum
vector<vector<int>> combinationSum(vector<int>& candidates, int target);
vector<vector<int>> combinationSum2(vector<int>& candidates, int target);

// Leetcode 40: Combination Sum II
vector<vector<int>> combinationsumII(vector<int>& candidates, int target);

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

// Leetcode 33: Search in Rotated Sorted Array
int search(vector<int>& nums, int target);

// Leetcode 81: Search in Rotated Sorted Array II
bool searchII(vector<int>& nums, int target);

// Leetcode 34: Find First and Last Position of Element in Sorted Array
vector<int> searchRange(vector<int>& nums, int target);

// Leetcode 11: Container With Most Water
int maxArea(vector<int>& height);
int maxArea2(vector<int>& height);

// Leetcode 26: Remove Duplicates from Sorted Array
int removeDuplicates(vector<int>& nums);
int removeDuplicates2(vector<int>& nums);
int removeDuplicates3(vector<int>& nums);

// Leetcode 80: Remove Duplicates from Sorted Array II
int removeDuplicatesII(vector<int>& nums);

// Leetcode 48: Rotate Image
void rotate(vector<vector<int>>& matrix);
void rotate2(vector<vector<int>>& matrix);

// Leetcode 54: Spiral Matrix
vector<int> spiralOrder(vector<vector<int>>& matrix);
vector<int> spiralOrder2(vector<vector<int>>& matrix);

// Leetcode 55: Jump Game
bool canJump(vector<int>& nums);
bool canJump2(vector<int>& nums);





#endif /* array_hpp */
