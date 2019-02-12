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

// Leetcode 47: Permutation II
vector<vector<int>> permuteUnique(vector<int>& nums);
vector<vector<int>> permuteUnique2(vector<int>& nums);

// Leetcode 46: Permutation
vector<vector<int>> permute(vector<int>& nums);

// Leetcode 950: Reveal Cards In Increasing Order
vector<int> deckRevealedIncreasing(vector<int>& deck);


#endif /* array_hpp */
