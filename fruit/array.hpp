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
	vector<int> nums;
	
public:
	// Leetcode 31: Next Permutation
	void nextPermutation(vector<int>& nums);
	void stl_nextPermutation(vector<int>& nums);

	
private:
	
};



#endif /* array_hpp */
