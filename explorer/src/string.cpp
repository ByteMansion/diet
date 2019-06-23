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
#include "array.hpp"

#include <limits.h>
#include <stdlib.h>

#include <functional>
#include <unordered_set>
#include <algorithm>
#include <queue>

using std::pair;
using std::make_pair;
using std::function;
using std::vector;
using std::unordered_set;
using std::next_permutation;
using std::sort;
using std::stable_sort;
using std::priority_queue;

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
 * If using all test cases in problem 132, time limit or memory limit 
 * exceeded will happen.
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
static void partitionHelper(const string& s, vector<vector<string>>& results,
                            vector<string>& subresult, int start)
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
    partitionHelper(s, results, subresult, 0);

    return results;
}

/**
 * @brief   Leetcode 131: Palindrome Partitioning
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
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
    vector<vector<string>> ret;
    function<void (vector<pair<int, int>>& progress, int idx)> helper;
    helper = [&ret, &pals, sz = s.size(), &helper] (vector<pair<int, int>>& progress, int idx) -> void {
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

    vector<pair<int, int>> progress;
    helper(progress, 0);
    return ret;
}

/**
 * @brief   Leetcode 132: Palindrome Partitioning II
 *  This method can get right result, but time limit exceeded.
 *
 */
static void minCutHelper(string& s, vector<string>& group, int& result, int start)
{
    if(start == s.length()) {
        if(group.size()-1 < result) {
            result = group.size() - 1;
        }
        return;
    }
    for(int i = start; i < s.length(); ++i) {
        // if number of palindromes exceeds current result before reaching the end of string,
        // terminate this iteration and continue searching better result.
        if(result != INT_MIN && group.size() > 0 && group.size()-1 > result) {
            break;
        }
        if(isPalindrome(s, start, i)) {
            group.push_back(s.substr(start, i-start+1));
            minCutHelper(s, group, result, i+1);
            group.pop_back();
        }
    }

}
int minCut(string s)
{
    int result = INT_MIN;
    vector<string> group;
    minCutHelper(s, group, result, 0);

    return result;
}

/**
 * @brief   Leetcode 132: Palindrome Partitioning II
 *  Using dynamic programming method.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 89%
 */
int minCut2(string s)
{
    const size_t N = s.length();
    if(N <= 1) {
        return 0;
    }

    bool isPalin[N][N];
    int dp[N+1];
    std::fill_n(&isPalin[0][0], N*N, false);
    for(int i = 0; i <= N; ++i) {
        dp[i] = i - 1;
    }

    for(int j = 1; j < N; ++j) {
        for(int i = j; i >= 0; --i) {
            if(s[i] == s[j] && (j-i < 2 || isPalin[i+1][j-1])) {
                isPalin[i][j] = true;
                dp[j+1] = std::min(dp[j+1], dp[i]+1);
            }
        }
    }
    return dp[N];
}

/**
 * @brief   Leetcode 132: Palindrome Partitioning
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 95%
 */
int minCut3(string s)
{
    const size_t N = s.length();
    if(N <= 1) {
        return 0;
    }

    int dp[N+1];
    for(int i = 0; i <= N; ++i) {
        dp[i] = i - 1;
    }

    for(int i = 1; i < N; ++i) {
        // odd length substring
        for(int j = 0; (i-j) >= 0 && (i+j) < N && s[i-j] == s[i+j]; ++j) {
            dp[i+j+1] = std::min(dp[i-j] + 1, dp[i+j+1]);
        }
        // even length substring
        for(int j = 0; (i-j) >= 0 && (i+j) < N && s[i-j-1] == s[i+j]; ++j) {
            dp[i+j+1] = std::min(dp[i-j-1] + 1, dp[i+j+1]);
        }
    }
    return dp[N];
}

/**
 * @brief   Leetcode 6: ZigZag Conversion
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 87%
 */
string convert(string s, int numRows)
{
    if(numRows == 1) {
        return s;
    }

    const size_t N = s.length();
    vector<string> resGroup(numRows, "");

    int index = 0;
    int num = 0;
    bool isPositive = true;
    while(index < N) {
        if(num == numRows - 1) {
            isPositive = false;
        } else if(num == 0) {
            isPositive = true;
        }
        resGroup[num].push_back(s[index++]);

        if(isPositive) {
            num += 1;
        } else {
            num -= 1;
        }
    }
    for(int i = 1; i < numRows; ++i) {
        resGroup[0].insert(resGroup[0].end(), resGroup[i].begin(), resGroup[i].end());
    }

    return resGroup[0];
}

/**
 * @brief   Leetcode 8: String to Integer(atoi)
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 98.5%
 */
static bool isInteger(char ch)
{
    if(ch >= '0' && ch <= '9') {
        return true;
    }
    return false;
}
int myAtoi(string str)
{
    // judge if the string is valid
    size_t N = str.length();
    int start = 0;
    for(start = 0; start < N; ++start) {
        if(str[start] != ' ') {
            break;
        }
    }
    if(start == N || ((str[start] > '9' || str[start] < '0') &&
      (str[start] != '+' && str[start] != '-'))) {
        return 0;
    }

    // judge if integer is positive
    int startIndex = start;
    bool isPositive = true;
    if(str[start] == '-' && start+1 < N && isInteger(str[start+1])) {
        isPositive = false;
        startIndex = (str[start] == '-') ? (start+1) : start;
    } else if((str[start] == '+' && start+1 < N && isInteger(str[start+1])) || isInteger(str[start])) {
        isPositive = true;
        startIndex = (str[start] == '+') ? (start+1) : start;
    } else {
        return 0;
    }

    // get the end of valid string
    int endIndex = startIndex;
    while(endIndex+1 < N && isInteger(str[endIndex+1])) {
        endIndex += 1;
    }

    // convert from string to integer
    int result = 0;
    for(int i = startIndex; i <= endIndex; ++i) {
        if(isPositive){
            if(result > INT_MAX/10 || (result == INT_MAX/10 && INT_MAX%10 <= str[i] - '0')) {
                return INT_MAX;
            }
        } else {
            if(result >  INT_MAX/10 || (result == INT_MAX/10 && INT_MIN%10*(-1) <= str[i] - '0')){
                return INT_MIN;
            }
        }
        result = (str[i] - '0') + result * 10;
    }

    return (isPositive ? result : (-1 * result));
}

/**
 * @brief   Leetcode 763: Partition Labels
 *  Transform this problem to a vector related one, so we can solve this problem
 *  in another way.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
vector<int> partitionLabels(string S)
{
    if(S.empty()) {
        return vector<int>{};
    }
    if(S.length() < 2) {
        return vector<int>{1};
    }
    vector<Interval> intervals;
    for(char ele = 'a'; ele <= 'z'; ++ele) {
        int firstPos = S.find_first_of(ele);
        int lastPos  = S.find_last_of(ele);
        if(firstPos != std::string::npos && lastPos != std::string::npos) {
            intervals.push_back(Interval(firstPos, lastPos));
        }
    }
    merge(intervals);

    vector<int> results;
    for(int i = 0; i < intervals.size(); ++i) {
        results.push_back(intervals[i].end - intervals[i].start + 1);
    }

    return results;
}

/**
 * @brief   Leetcode 763: Partition Labels
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 16%
 */
vector<int> partitionLabels2(string S)
{
    if(S.empty()) {
        return vector<int>{};
    }
    if(S.length() < 2) {
        return vector<int>{1};
    }

    vector<int> results;
    int maxPos = 0;
    int minPos = 0;
    for(int i = 0; i < S.length() && i <= maxPos; ++i) {
        minPos = std::min(minPos, i);
        maxPos = std::max(maxPos, (int)S.find_last_of(S[i]));
        if(i == maxPos) {
            results.push_back(maxPos - minPos + 1);
            if(maxPos == S.length() - 1) {
                return results;
            }
            minPos = maxPos + 1;
            maxPos = maxPos + 1;
        }
    }

    return results;
}

/**
 * @brief	Leetcode 767: Reorganize String
 *  S consists of lowercase letters and has length of [1, 500]
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 86.51%
 */
string reorganizeString(string S)
{
    vector<pair<char,int>> idxToCnt;
    for (int i = 0; i < 26; ++i) {
        idxToCnt.push_back(make_pair(i+'a', 0));
    }
    for(auto& ch: S) {
        int index = ch - 'a';
        idxToCnt[index].second++;
    }
    // use stable sort to maintain element order
    // sort is not stable, may lead to adjacent elements
    stable_sort(idxToCnt.begin(), idxToCnt.end(),
                [](auto m, auto n) { return m.second > n.second; } );
    int mostChar = idxToCnt[0].second;
    if(mostChar - 1 > S.length() - mostChar) {
        return "";
    }

    int i = 0;
    while(idxToCnt[0].second > 0) {
        S[i++] = idxToCnt[0].first;
        idxToCnt[0].second--;
        if(idxToCnt[1].second > 0) {
            S[i++] = idxToCnt[1].first;
            idxToCnt[1].second--;
        } else {
            break;
        }
        // use stable sort
        stable_sort(idxToCnt.begin(), idxToCnt.end(),
                    [](auto m, auto n) { return m.second > n.second; } );
    }

    return S;
}

/**
 * @brief   Leetcode 767: Reorganize String
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 86%
 */
string reorganizeString2(string S)
{
    // get count of each character
    vector<int> charStat(26, 0);
    for(int i = 0; i < S.length(); ++i) {
        charStat[S[i] - 'a']++;
        if(charStat[S[i] - 'a'] > (S.length() + 1) / 2) {
            return "";
        }
    }
    // construct priority queue by char count descending order
    priority_queue<pair<int, char>> qChar;
    for(int i = 0; i < 26; ++i) {
        if(charStat[i] > 0) {
            qChar.emplace(make_pair(charStat[i], i + 'a'));
        }
    }

    int i = 0;
    pair<int, char> prev;  // save previous char info
    while(!qChar.empty()) {
        auto curr = qChar.top();
        qChar.pop();
        S[i++] = curr.second;
        curr.first--;
        if(prev.first > 0) {  // after current char processed, push previous char
            qChar.emplace(prev);
        }
        prev = curr;
    }

    return S;
}

/**
 * @brief   Leetcode 358: Rearrange String k Distance Apart
 *  Given a non-empty string str and an integer k, rearrange the string such that
 *  the same characters are at least distance k from each other.
 *  All input strings are given in lowercase letters. If it is not possible to rearrange
 *  the string, return an empty string "".
 *
 */
 string rearrangeString(string str, int k)
{
    if(str.length() < 2 || k == 1) {
        return str;
    }

    int mostChar = 0;
    int mostCharCnt = 0;
    vector<int> cCnt(26, 0);
    for(int i = 0; i < str.size(); ++i) {
        int index = str[i] - 'a';
        cCnt[index] += 1;
        if(cCnt[index] == mostChar) {
            mostCharCnt += 1;
        } else if(cCnt[index] > mostChar) {
            mostChar    = cCnt[index];
            mostCharCnt = 1;
        }
    }
    // check if we can rearrange the string
    int leftover = str.length() - mostChar * mostCharCnt;
    int needed   = (mostChar - 1) * (k - mostCharCnt);
    if(k > mostCharCnt && leftover < needed) {  // in this case, we can not get what we want
        return "";
    }

    // we can get rearranged string
    // construct priority queue
    priority_queue<pair<int, char>> qCnt;
    for(int i = 0; i < 26; ++i) {
        if(cCnt[i] == 0) continue;
        qCnt.emplace(make_pair(cCnt[i], i + 'a'));
    }

    int pos = 0;
    while(!qCnt.empty()) {
        priority_queue<pair<int, char>> tempQ;
        int i = 0;
        while(i++ < k && !qCnt.empty()) {
            auto ele = qCnt.top();
            qCnt.pop();
            str[pos++] = ele.second;
            ele.first--;
            if(ele.first > 0) {
                tempQ.emplace(ele);
            }
        }
        while(!tempQ.empty()) {
            auto ele = tempQ.top();
            tempQ.pop();
            qCnt.emplace(ele);
        }
    }

    return str;
}
