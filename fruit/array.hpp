/**
 * @file	tree.hpp
 * @brief	Data structures of leetcode problems needed and class solutions
 *
 * @author	Changrui
 * @date	2018/11/28
 *
 * Copyright © 2018 ChangruiShao. All rights reserved.
 */

#ifndef array_hpp
#define array_hpp

#include <stdio.h>
#include <vector>

using std::vector;

class Solution_A {

public:
	// Leetcode 31: Next Permutation
	void nextPermutation(vector<int>& nums);
	void nextPermutation2(vector<int>& nums);
	void nextPermutation3(vector<int>& nums);

	// Leetcode 47: Permutation II
	vector<vector<int>> permuteUnique(vector<int>& nums);
	vector<vector<int>> permuteUnique2(vector<int>& nums);

private:
    vector<int> nums;

};



#endif /* array_hpp */
