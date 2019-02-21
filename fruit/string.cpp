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
 * Using backtracking algorithm
 * Time complexity is O(n*2^n)
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
static bool isPalindrome(const string& s, int left, int right)
{
    while(left < right) {
        if(s[left++] != s[right--]) {
            return false;
        }
    }
    return true;
}
static void partitionHelper(const string& s, vector<string>& results,
                            string& substring, int start)
{
    if(start >= s.length()) {
        results.push_back(subresult);
        return;
    }
    for(int i = start; i < s.length(); ++i) {
        if(isPalindrome(s, start, i)) {
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

/**
 * @brief   Leetcode 131: Palindrome Partitioning
 *
 */
vector<vector<string>> partition2(string s)
{
    // Build a list of all palindrome beginning at each index
    vector<vector<string>> pals(s.size(), vector<string>{});
    for(int i = 0; i < s.size(); ++i) {
        // offset 0 for odd length palindromes and 1 for even length palindromes
        for(auto offset: {0, 1}) {
            // keep expanding around index i so long as we still have a valid Palindrome
            for(int j = 0; i-j >= 0 && i+j+offset < s.size() && s[i-j] == s[i+j+offset]; ++j) {
                pals[i-j].emplace_back(&s[i-j], j*2+1+offset);
            }
        }
    }

    // Helper lambda that cycles through all the palindromes starting at the passed index
    std::vector<std::vector<std::string>> ret;
    std::function <void (std::vector<std::pair<int, int>>& progress, int idx)> helper;
    helper = [&ret, &pals, sz = s.size(), &helper] (std::vector<std::pair<int, int>>& progress, int idx) -> void {
        // Terminal case, add all the palindromes used to reach here to ret.
        if (idx == sz) {
          ret.emplace_back();
          for (auto& pal : progress) {
            ret.back().emplace_back(pals[pal.first][pal.second]);
          }
          return;
        }

        // Branch out for each palindrome starting at index idx
        auto& pals_at_idx = pals[idx];
        for (int i = 0; i < pals_at_idx.size(); ++i) {
          progress.emplace_back(std::make_pair(idx, i));
          helper(progress, idx + pals_at_idx[i].size());
          progress.pop_back();
        }
      };

    std::vector<std::pair<int, int>> progress;
    helper(progress, 0);
    return ret;
}
