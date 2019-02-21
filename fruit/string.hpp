/**
 * @file	string.hpp
 * @brief	Data structures and function declarations
 *
 * @author	Changrui
 * @date	2019/2/2
 *
 * Copyright © 2019 ChangruiShao. All rights reserved.
 */

#ifndef _string_hpp
#define _string_hpp

#include <stdio.h>
#include <string>

using std::string;

// Leetcode 60: Permutation Sequence
string getPermutation(int n, int k);
string getPermutation2(int n, int k);

// Leetcode 131: Palindrome Partitioning
vector<vector<string>> partition(string s);
vector<vector<string>> partition2(string s);


#endif
