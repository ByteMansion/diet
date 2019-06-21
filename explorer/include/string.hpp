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
#include <vector>

using std::string;
using std::vector;

// Leetcode 60: Permutation Sequence
string getPermutation(int n, int k);
string getPermutation2(int n, int k);

// Leetcode 131: Palindrome Partitioning
vector<vector<string>> partition(string s);
vector<vector<string>> partition2(string s);

// Leetcode 132: Palindrome Partitioning II
int minCut(string s);
int minCut2(string s);
int minCut3(string s);

// Leetcode 6: ZigZag Conversion
string convert(string s, int numRows);

// Leetcode 8: String to Integer(atoi)
int myAtoi(string str);

// Leetcode 763: Partition Labels
vector<int> partitionLabels(string S);
vector<int> partitionLabels2(string S);

// Leetcode 767: Reorganize String
string reorganizeString(string S);


#endif
