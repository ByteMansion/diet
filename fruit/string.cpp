/**
 * @file	string.cpp
 * @brief	Data structures and function declarations
 *
 * @author	Changrui
 * @date	2019/2/2
 *
 * Copyright © 2019 ChangruiShao. All rights reserved.
 */

#include "string.hpp"

/**
 * @brief   Leetcode 60: Permutation Sequence
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 26%
 */
string getPermutation(int n, int k)
{
    string result(n, '1');
    for(int i = 0; i < n; i++) {
        result[i] += i;
    }
    while(k-- > 1) {
        next_permutation(result.begin(), result.end());
    }

    return result;
}

/**
 * @brief   Leetcode 60: Permutation Sequence
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
string getPermutation2(int n, int k)
{
    string result(n, '0');
    vector<int> nums(n+1, 0);
    vector<int> factorial(n+1, 1);  // factorial number of index
    // get factorial numbers
    for(int i = 1; i <= n; i++) {
        factorial[i] = factorial[i-1] * i;
        nums[i] += i;
    }

    int pos = 0;
    while(nums.size() > 1) {
        int m = k % factorial[--n];
        if(m == 0) {
            int index = k / factorial[n];
            result[pos++] += nums[index];
            nums.erase(nums.begin() + index);
            break;
        } else {
            int index = k / factorial[n] + 1;
            result[pos++] += nums[index];
            nums.erase(nums.begin() + index);
            k = m;
        }
    }
    // when k is even
    if(nums.size() > 1 && n > 0) {
        for(int i = n; i > 0; i--) {
            result[pos++] += nums[i];
        }

    }

    return result;
}

/**
 * @brief   Leetcode 131: Palindrome Partitioning
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 46%
 */
static bool isPalindrome(const string s, int left, int right)
{
    while(left < right) {
        if(s[left++] != s[right--]) {
            return false;
        }
    }
    return true;
}
static void partitionHelper(string& s, vector<string>& results,
                            string& substring, int start)
{
    if(start >= s.length()) {
        results.push_back(subresult);
    } else {
        for(int i = start; i < s.length(); ++i) {
            subresult.push_back(s.substr(start, i-start+1));
            partitionHelper(s, results, subresult, i+1);
            subresult.pop_back();
        }
    }
}
vector<vector<string>> partition(string s)
{
    vector<vector<string>> results;
    if(s.empty()) {
        return results;
    }
    vector<string> subresult;
    partitionHelper(s, results, substring, 0);

    return results;
}
