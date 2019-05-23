/**
 * @file	array.cpp
 * @brief	All functions are solutions of leetcode problems.
 *
 * @author	Changrui
 * @date	2018/12/8
 *
 * Copyright © 2018 ChangruiShao. All rights reserved.
 */

#include "../include/array.hpp"

#include <algorithm>
#include <deque>
#include <unordered_map>
#include <map>
#include <unordered_set>
#include <cmath>
#include <string>

using std::swap;
using std::sort;
using std::reverse;
using std::deque;
using std::unordered_map;
using std::multimap;
using std::map;
using std::unordered_set;
using std::log;
using std::string;
using std::to_string;
using std::pair;
using std::make_pair;

/**
 * @brief	Leetcode 31: Next Permutation
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
void nextPermutation(vector<int>& nums)
{
	if(nums.empty() || nums.size() == 1)
		return;

    // find first number which is less than its post element.
    // the found number is target one which should be replaced.
    // e.g. nums=2365, target number=3
	int backward = int(nums.size()) - 1;;
	int foreward = backward - 1;
	while (nums[foreward] >= nums[backward]) {
		foreward--;
		backward--;
        // if this array is in descending order, reverse it and then return result.
		if (foreward == -1) {
			sort(nums.begin(), nums.end());
			return;
		}
	}
    // find last element which is bigger than target number
    // swap found number and the target number, sort all elements to the right of
    // target position in ascending order.
    // e.g. nums=2365, result=2536
	for (int j = int(nums.size()) - 1; j >= foreward; j--) {
		if (nums[j] > nums[foreward]) {
			swap(nums[j], nums[foreward]);
			sort(nums.begin() + backward, nums.end());
			return;
		}
	}
}

/**
 * @brief	Leetcode 31: Next Permutation
 *	This solution is implementation of STL function next_permutation.
 */
void nextPermutation2(vector<int>& nums)
{
	auto last = nums.end();
	auto first = nums.begin();
	if (last == first || first == last-1) {
		return;
	}
	auto i = nums.end()-1;
	while (true) {
		auto ip = i;
		if (*--i < *ip) {
			auto j = nums.end();
			while (*i >= *--j)
				;
			swap(*i, *j);
			sort(ip, last);
			return;
		}
		if (i == first) {
			sort(first, last);
			return;
		}
	}
}
/**
 * @brief	Leetcode 31: Next Permutation
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99.36%
 */
void nextPermutation3(vector<int>& nums)
{
	next_permutation(nums.begin(), nums.end());
}

/**
 * @brief   Leetcode 46: Permutations
 *
 */
vector<vector<int>> permute(vector<int>& nums)
{
    return permuteUnique(nums);
}

/**
 * @brief   Leetcode 46: Permutations
 *  Using Backtracking algorithm to solve this problem.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
static void permuteHelper(vector<int>& nums, vector<vector<int>>& results,
                     vector<int>& permutation)
{
    if(permutation.size() == nums.size()) {
        results.push_back(permutation);
    } else {
        for(int i = 0; i < nums.size(); ++i) {
            if(find(permutation.begin(), permutation.end(), nums[i])
               != permutation.end()) {
                continue;
            }
            permutation.push_back(nums[i]);
            permuteHelper(nums, results, permutation);
            permutation.pop_back();
        }
    }
}
vector<vector<int>> permute2(vector<int>& nums)
{
    vector<vector<int>> results;
    vector<int> permutation;
    permuteHelper(nums, results, permutation);

    return results;
}


/**
 * @brief	Leetcode 47: Permutation II
 *	Given a collection of numbers that might contain duplicates, return
 * 	all possible unique permutations.
 *  This method uses STL function.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
vector<vector<int>> permuteUnique(vector<int>& nums)
{
	vector<vector<int>> result;

	if (nums.empty() || nums.size() == 0) {
		return result;
	}
	sort(nums.begin(), nums.end());
	result.push_back(nums);
	while (next_permutation(nums.begin(), nums.end())) {
		result.push_back(nums);
	}


	return result;
}

/**
 * @brief	Leetcode 47: Permutation II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
vector<vector<int>> permuteUnique2(vector<int>& nums)
{
	vector<vector<int>> result;

	if (nums.empty()) {
		return result;
	}

	sort(nums.begin(), nums.end());
	result.push_back(nums);

	while (1) {
        nextPermutation(nums);
        if(nums == result[0]) {
            break;
        }
		result.push_back(nums);
	}

	return result;
}

/**
 * @brief   Leetcode 47: Permutation II
 *  Using Backtracking algorithm.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
// if nums=[1,2,2,2], then
// results={[1,2,2,2]l,[2,1,2,2],[2,2,1,2],[2,2,2,1]}
static void permuteUniqueHelper(vector<int>& nums, vector<vector<int>>& results,
                                vector<int>& array, vector<bool>& used)
{
    if(array.size() == nums.size()) {
        results.push_back(array);
    } else {
        for(int i = 0; i < nums.size(); ++i) {
            if(used[i] || (i > 0 && nums[i] == nums[i-1] && !used[i-1])) {
                continue;
            }
            used[i] = true;
            array.push_back(nums[i]);
            permuteUniqueHelper(nums, results, array, used);
            used[i] = false;
            array.pop_back();
        }
    }
}
vector<vector<int>> permuteUnique3(vector<int>& nums)
{
    vector<vector<int>> results;
    vector<int> array;
    vector<bool> used(nums.size(), false);
    sort(nums.begin(), nums.end());
    permuteUniqueHelper(nums, results, array, used);

    return results;
}

/**
 * @brief	Leetcode 77: Combinations
 *  Using backtracking algorithm
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 78.5%
 */
static void combineHelper(int n, int k,
                          vector<vector<int>>& results,
                          vector<int>& array,
                          int start)
{
    if (array.size() == k) {
        results.push_back(array);
        return;
    }
    // right border changes to (n+1-k+array.size()), more unnecessary
    // combinations are jumped, and then execution is faster.
	for (int i = start; i <= n; ++i) {
		array.push_back(i);
        combineHelper(n, k, results, array, i+1);
		array.pop_back();
	}

}
vector<vector<int>> combine(int n, int k)
{
	vector<vector<int>> results;
	vector<int> array;
	combineHelper(n, k, results, array, 1);

	return results;
}

/**
 * @brief   Leetcode 77: Combinations
 *  This solution can be accepted, but time complexity is high.
 *  In my point of view, this solution does too much trivial work.
 *
 *  If we choose k numbers in an array with n length and distinct members each other,
 *  this method may be effective.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 1.27%
 */
vector<vector<int>> combine2(int n, int k)
{
    vector<vector<int>> results;

    int num = (1 << n);
    for(int i = 1; i < num; ++i) {
        vector<int> array;
        for(int j = 0; j < n; ++j) {
            if((1 << j) & i) {
                array.push_back(j+1);
            }
        }
        if(array.size() == k) {
            results.push_back(array);
        }
    }

    return results;
}

/**
 * @brief   Leetcode 77: Combinations
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 86.7%
 */
vector<vector<int>> combine3(int n, int k)
{
    vector<vector<int>> results;
    vector<int> array(k, 0);
    int index = 0;
    while(index >= 0) {
        array[index]++;
        if(array[index] > n) {
            index--;
        } else if(index+1 == k) {
            results.push_back(array);
        } else {
            index++;
            array[index] = array[index-1]; 
        }
    }
    return results;
}

/**
 * @brief   Leetcode 77: Combinations
 *  if n=6, k=3, then the results is
 *  [[1,2,3],[1,2,4],[1,3,4],[2,3,4],
 *   [1,2,5],[1,3,5],[2,3,5],[1,4,5],[2,4,5],[3,4,5],
 *   [1,2,6],[1,3,6],[2,3,6],[1,4,6],[2,4,6],[3,4,6],[1,5,6],[2,5,6],[3,5,6],[4,5,6]]
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99.97%
 */
vector<vector<int>> combine4(int n, int k)
{
    vector<vector<int>> results;
    vector<int> nums;
    for(int i = 1; i < k+1; ++i) {
        nums.push_back(i);
    }
    nums.push_back(n+1);
    // if n=6,k=3, then nums=[1,2,3,7]
    int index = 0;
    while(index < k) {
        results.push_back(vector<int>(&nums[0], &nums[k]));

        index = 0;
        while(index < k && (nums[index+1] == nums[index]+1)) {
            nums[index] = index + 1;
            index += 1;
        }
        nums[index] = nums[index] + 1;
    }

    return results;
}

/**
 * @brief   Leetcode 39: Combination Sum
 *  No duplicates in candidates and results can contain duplicates.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 75%
 */
static void combinationSumHelper(vector<int>& candidates,
                                 int target,
                                 vector<vector<int>>& results,
                                 vector<int>& array,
                                 int start)
{
    if(target == 0) {
        results.push_back(array);
        return;
    } else if(target < 0) {
        return;
    }
    // start number determines whether we can use same number repeatedly
    for(int i = start; i < candidates.size(); ++i) {
        if(candidates[i] > target) {
            break;
        }
        array.push_back(candidates[i]);
        target -= candidates[i];
        combinationSumHelper(candidates, target, results, array, i);
        array.pop_back();
        target += candidates[i];
    }
}
vector<vector<int>> combinationSum(vector<int>& candidates, int target)
{
    vector<vector<int>> results;
    sort(candidates.begin(), candidates.end());
    vector<int> array;
    combinationSumHelper(candidates, target, results, array, 0);

    return results;
}

/**
 * @brief   Leetcode 39: Combination Sum
 *  Use Dynamic programming algorithm.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 28.54%
 */
vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
{
    sort(candidates.begin(), candidates.end());

    vector<vector<vector<int>>> dp(target+1, vector<vector<int>>{});
    dp[0].push_back(vector<int>{});

    for(auto& candidate: candidates) {
        for(int sub_target = 0; sub_target + candidate <= target; ++sub_target) {
            vector<vector<int>> new_combinations = dp[sub_target];
            for(auto& combination: new_combinations) {
                combination.push_back(candidate);
            }
            int target_yielded = sub_target + candidate;
            dp[target_yielded].insert(dp[target_yielded].end(), new_combinations.begin(), new_combinations.end());
        }
    }

    return dp[target];
}

/**
 * @brief   Leetcode 40: Combination Sum II
 *  Use Backtracking algorithm
 *  Candidates contain duplicates and results cannot contain duplicates.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99.58%
 */
static void combinationsumIIHelper(vector<int>& candidates, int target,
                                   vector<int>& array, vector<vector<int>>& results,
                                   int start)
{
    if(target == 0) {
        results.push_back(array);
        return;
    }
    for(int i = start; i < candidates.size(); ++i) {
        if(i > start && candidates[i] == candidates[i-1]) {
            continue;
        }
        if(target - candidates[i] < 0) {
            break;
        }
        array.push_back(candidates[i]);
        combinationsumIIHelper(candidates, target-candidates[i], array, results, i+1);
        array.pop_back();
    }
}
vector<vector<int>> combinationSumII(vector<int>& candidates, int target)
{
    sort(candidates.begin(), candidates.end());

    vector<vector<int>> results;
    vector<int> array;
    combinationsumIIHelper(candidates, target, array, results, 0);

    return results;
}

/**
 * @brief	Leetcode 216: Combination Sum III
 *  combinations of k numbers that add up to a number n
 *  only 1 to 9 can be used and no Duplicates
 *
 *  This method is transformed from problem 77, using Backtracking
 *  algorithm.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
static void combinationSum3Helper(vector<vector<int>>& results,
                                  vector<int>& array,
                                  int k, int start, int end, int targetSum)
{
    if(array.size() == k) {
        if(targetSum == 0) {
            results.push_back(array);
        }
        return;
    }
    for(int i = start; i < end; ++i) {
        array.push_back(i);
        combinationSum3Helper(results, array, k, i+1, end, targetSum-i);
        array.pop_back();
    }
}
vector<vector<int>> combinationSum3(int k, int n)
{
	vector<vector<int>> results;
	vector<int> array;
    combinationSum3Helper(results, array, k, 1, 10, n);

	return results;
}

/**
 * @brief   Leetcode 216: Combination Sum III
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
vector<vector<int>> combinationSum32(int k, int n)
{
    vector<vector<int>> results;
    vector<int> array(k, 0);
    int index = 0;
    int end = 10;
    int sum = 0;
    while(index >= 0) {
        array[index] += 1;
        sum += 1;
        if(array[index] >= end) {
            index -= 1;
        } else if(index+1 == k) {
            if(sum == n) {
                results.push_back(array);
            }
        } else {
            index += 1;
            sum += array[index-1] - array[index];
            array[index] = array[index-1];
        }
    }
    return results;
}


/**
 * @brief   Leetcode 950: Reveal Cards In Increasing Order
 *  This method using less time, but more space.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
vector<int> deckRevealedIncreasing(vector<int>& deck)
{
    if(deck.empty() || deck.size() == 1) {
        return deck;
    }

    // reverse order sort
    sort(deck.rbegin(), deck.rend());

    deque<int> dResult;
    dResult.push_front(deck[0]);
    for(int i = 1; i < deck.size(); ++i) {
        dResult.push_front(dResult.back());
        dResult.pop_back();
        dResult.push_front(deck[i]);
    }

    vector<int> res(dResult.begin(), dResult.end());
    return res;
}

/**
 * @brief   Leetcode 15: 3Sum
 *  This method costs too much time and space.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 11.7%
 */
static void twoSum(vector<int>& nums, int start, int end, int sum,
           vector<vector<int>>& results)
{
    while(start < end) {
        vector<int> ele;
        ele.push_back(-1 * sum);
        if(nums[start] + nums[end] < sum) {
            start++;
        } else if(nums[start] + nums[end] > sum) {
            end--;
        } else {
            ele.push_back(nums[start]);
            ele.push_back(nums[end]);
            results.push_back(ele);
            ele.clear();
			while(start < end && nums[start] == nums[start+1]) start++;
			while(start < end && nums[end] == nums[end-1]) end--;
            start++;
            end--;
        }
    }
}
vector<vector<int>> threeSum(vector<int>& nums)
{
    vector<vector<int>> results;
    if(nums.empty() || nums.size() < 3) {
        return results;
    }

    sort(nums.begin(), nums.end());
    int index = 0;
    while(index < nums.size()-2) {
        twoSum(nums, index+1, int(nums.size()-1), -1*nums[index], results);

        while((index+1 < nums.size()-2) && (nums[index] == nums[index+1])) {
            index++;
        }
		index += 1;
    }

    return results;
}

/**
 * @brief   Leetcode 15: 3Sum
 *  This method integrates above two functions into one. Actually, internal 
 *  solution is as same, but costs less time and space.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 90.6%
 */
vector<vector<int>> threeSum2(vector<int>& nums)
{
    vector<vector<int>> res;
    if(nums.empty() || nums.size() < 3) {
        return res;
    }

    sort(nums.begin(), nums.end());
    for(int i = 0; i < nums.size()-2; ++i) {
        if(i > 0 && nums[i] == nums[i-1]) continue;

        int twoSum = -1 * nums[i];
        int nLeft = i + 1;
        size_t nRight = nums.size() - 1;
        while(nLeft < nRight) {
            if(nums[nLeft] + nums[nRight] == twoSum) {
                res.push_back(vector<int>{nums[i], nums[nLeft], nums[nRight]});
                while(nLeft < nRight && nums[nLeft] == nums[nLeft+1]) nLeft++;
                while(nLeft < nRight && nums[nRight] == nums[nRight-1]) nRight--;
                nLeft++;
                nRight--;
            } else if(nums[nLeft] + nums[nRight] > twoSum) {
                nRight--;
            } else {
                nLeft++;
            }
        }
    }

    return res;
}

/**
 * @brief   Leetcode 16: 3Sum Closest
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 95.8%
 */
int threeSumClosest(vector<int>& nums, int target)
{
	int minGap = INT_MAX;
    sort(nums.begin(), nums.end());

	int result = nums[0] + nums[1] + nums[2];
    for(int i = 0; i < nums.size()-2; ++i) {
        int nLeft = i + 1;
        size_t nRight = nums.size() - 1;
        while(nLeft < nRight) {
            int gap = target - (nums[i] + nums[nLeft] + nums[nRight]);
            if(std::abs(gap) < minGap) {
                minGap = std::abs(gap);
                result = nums[i] + nums[nLeft] + nums[nRight];
            }
            if(gap > 0) {
                nLeft++;
            } else if(gap < 0){
                nRight--;
            } else {
                return result;
            }
        }
    }

    return result;
}

/**
 * @brief   Leetcode 18: 4Sum
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 73%
 */
static void threeSumHelper(vector<int>& nums, int start, int sum,
                      vector<vector<int>>& results)
{
    for(int i = start; i < nums.size()-2; ++i) {
        if(i > start && nums[i] == nums[i-1]) continue;

        int nLeft = i + 1;
        size_t nRight = nums.size() - 1;
        while(nLeft < nRight) {
            if(nums[i] + nums[nLeft] + nums[nRight] == sum) {
                results.push_back(vector<int>{nums[start-1], nums[i], nums[nLeft], nums[nRight]});
                while(nLeft < nRight && nums[nLeft] == nums[nLeft+1]) nLeft++;
                while(nLeft < nRight && nums[nRight] == nums[nRight-1]) nRight--;
                nLeft++;
                nRight--;
            } else if(nums[i] + nums[nLeft] + nums[nRight] < sum) {
                nLeft++;
            } else {
                nRight--;
            }
        }
    }
}
vector<vector<int>> fourSum(vector<int>& nums, int target)
{
    vector<vector<int>> results;
    if(nums.empty() || nums.size() < 4) {
        return results;
    }

    sort(nums.begin(), nums.end());
    for(int i = 0; i < nums.size()-3; ++i) {
        if(i > 0 && nums[i] == nums[i-1]) continue;

        int sum = target - nums[i];
        threeSumHelper(nums, i+1, sum, results);
    }

    return results;
}

/**
 * @brief   Leetcode 18: 4Sum
 *  This method integrates above two functions into one, and then adds some extra conditions to
 *  decrease unnecessary search iterations.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
vector<vector<int>> fourSum2(vector<int>& nums, int target)
{
    vector<vector<int>> results;
    if(nums.empty() || nums.size() < 4) {
        return results;
    }
    sort(nums.begin(), nums.end());
    size_t length = nums.size();
    for(int i = 0 ; i < length-3; ++i) {
        if(nums[i] + nums[i+1] + nums[i+2] + nums[i+3] > target) break;
        if(nums[i] + nums[length-3] + nums[length-2] + nums[length-1] < target) continue;

        if(i > 0 && nums[i] == nums[i-1]) continue;
        for(int j = i+1; j < length-2; ++j) {
            if(nums[i] + nums[j] + nums[j+1] + nums[j+2] > target) break;
            if(nums[i] + nums[j] + nums[length-2] + nums[length-1] < target) continue;

            if(j > i+1 && nums[j] == nums[j-1]) continue;
            int nLeft = j+1;
            size_t nRight = length - 1;
            while(nLeft < nRight) {
                int sum = nums[i] + nums[j] + nums[nLeft] + nums[nRight];
                if(sum == target) {
                    results.push_back(vector<int>{nums[i], nums[j], nums[nLeft], nums[nRight]});
                    while(nLeft < nRight && nums[nLeft] == nums[nLeft+1]) nLeft++;
                    while(nLeft < nRight && nums[nRight] == nums[nRight-1]) nRight--;
                    nLeft++;
                    nRight--;
                } else if(sum < target) {
                    nLeft++;
                } else {
                    nRight--;
                }
            }
        }
    }

    return results;
}

/**
 * @brief   Leetcode 454: 4Sum II
 *  This method is brute force algorithm, which can get correct result, but time limit
 *  exceeded.
 *
 */
int fourSumCount(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D)
{
    if(A.empty()) return 0;

    int result = 0;
    size_t length = A.size();
    for(int i = 0; i < length; ++i) {
        for(int j = 0; j < length; ++j) {
            for(int k = 0; k < length; ++k) {
                for(int l = 0; l < length; ++l) {
                    int sum = A[i] + B[j] + C[k] + D[l];
                    if(sum == 0) {
                        result += 1;
                    }
                }
            }
        }
    }
    return result;
}

/**
 * @brief   Leetcode 454: 4Sum II
 *  In order to meet time limit, we should balance time complexity and space
 *  complexity.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 90%
 */
int fourSumCount2(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D)
{
    int result = 0;
    // sum --> count
    unordered_map<int, int> mSum;
    size_t length = A.size();
    for(int i = 0; i < length; ++i) {
        for(int j = 0; j < length; ++j) {
            mSum[A[i] + B[j]] += 1;
        }
    }

    for(int i = 0; i < length; ++i) {
        for(int j = 0; j < length; ++j) {
            int target = -1 * (C[i] + D[j]);
            auto iter = mSum.find(target);
            if(iter != mSum.end()) {
                result += mSum[target];
            }
        }
    }

    return result;
}

/**
 * @brief   Leetcode 78: Subsets
 *  Backtracking algorithm
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
// if nums=[1,2,3], then
// results={[],[1],[1,2],[1,2,3],[1,3],[2],[2,3],[3]}
static void subsetsHelper(vector<int>& nums, vector<vector<int>>& results,
                          vector<int>& subarray, int start)
{
    results.push_back(subarray);
    for(int i = start; i < nums.size(); ++i) {
        subarray.push_back(nums[i]);
        subsetsHelper(nums, results, subarray, i+1);
        subarray.pop_back();
    }
}
vector<vector<int>> subsets(vector<int>& nums)
{
    vector<vector<int>> results;
    vector<int> subarray;
    subsetsHelper(nums, results, subarray, 0);

    return results;
}

/**
 * @brief   Leetcode 78: Subsets
 *  This method can only use in distinct integer array. If same members exixt in
 *  an array, this method is useless.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 53%
 */
vector<vector<int>> subsets2(vector<int>& nums)
{
    vector<vector<int>> results;
    int count = (1 << nums.size());
    for(int i = 0; i < count; ++i) {
        vector<int> subarray;
        for(int j = 0; j < nums.size(); j++) {
            if((1 << j) & i) {
                subarray.push_back(nums[j]);
            }
        }
        results.push_back(subarray);
    }

    return results;
}

/**
 * @brief   Leetcode 78: Subsets
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
// if nums=[1,2,3], then 
// results={[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]}
vector<vector<int>> subsets3(vector<int>& nums)
{
    vector<vector<int>> results{{}};
    for(auto& num: nums) {
        size_t len = results.size();
        for(int i = 0; i < len; ++i) {
            results.push_back(results[i]);
            results.back().push_back(num);
        }
    }
    return results;
}

/**
 * @brief   Leetcode 90: Subsets II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
// if nums=[1,2,2], then
// results={[],[1],[1,2],[1,2,2],[2],[2,2]}
static void subsetsWithDupHelper(vector<int>& nums, vector<vector<int>>& results,
                                 vector<int>& subarray, int start)
{
    results.push_back(subarray);
    for(int i = start; i < nums.size(); ++i) {
        // leave out duplicates
        if(i > start && nums[i] == nums[i-1]) continue;
        subarray.push_back(nums[i]);
        subsetsWithDupHelper(nums, results, subarray, i+1);
        subarray.pop_back();
    }
}
vector<vector<int>> subsetsWithDup(vector<int>& nums)
{
    vector<vector<int>> results;
    sort(nums.begin(), nums.end());

    vector<int> subarray;
    subsetsWithDupHelper(nums, results, subarray, 0);

    return results;
}

/**
 * @brief   Leetcode 90: Subsets II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
// if nums=[1,2,2], then
// results={[],[1],[2],[2,2],[1,2],[1,2,2]}
vector<vector<int>> subsetsWithDup2(vector<int>& nums)
{
    vector<vector<int>> results{{}};
    sort(nums.begin(), nums.end());
    for(int j = 0; j < nums.size(); ) {
        int memCount = 0;
        while(memCount+j < nums.size() && nums[memCount+j] == nums[j]) {
            memCount += 1;
        }
        size_t curSubsetsLength = results.size();
        for(int i = 0; i < curSubsetsLength; ++i) {
            vector<int> subarray = results[i];
            for(int k = 0; k < memCount; ++k) {
                subarray.push_back(nums[j]);
                results.push_back(subarray);
            }
        }
        j += memCount;
    }

    return results;
}

/**
 * @brief   Leetcode 33: Search in Rotated Sorted Array
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
int search(vector<int>& nums, int target)
{
    if(nums.empty()) {
        return -1;
    }
    int left = 0;
    int right = nums.size() - 1;

    while(left+1 < right) {
        int middle = left + (right - left) / 2;
        if(target == nums[middle]) {
            return middle;
        }
        // e.g. nums=[4,5,6,7,8,1,2], target=8
        if(nums[middle] >= nums[left]) {
            if(target > nums[middle]) {
                left = middle;
            } else if(target >= nums[left]){
                right = middle;
            } else {
                left = middle;
            }
        } else {  // e.g. nums=[8,9,1,2,3,4,5], target=4
            if(target < nums[middle]) {
                right = middle;
            } else if(target >= nums[left]){
                right = middle;
            } else {
                left = middle;
            }
        }
    }
    if(nums[left] == target) return left;
    if(nums[right] == target) return right;

    return -1;
}

/**
 * @brief   Leetcode 81: Search in Rotated Sorted Array II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
bool searchII(vector<int>& nums, int target)
{
    if(nums.empty()) {
        return false;
    }

    int left = 0;
    int right = nums.size() - 1;
    while(left+1 < right) {
        int middle = left + (right - left) / 2;
        if(target == nums[middle]) {
            return true;
        }
        while(left+1 < middle && nums[left] == nums[middle]) {
            left++;
        }
        while(right+1 > middle && nums[right] == nums[middle]) {
            right--;
        }
        if(nums[middle] >= nums[left]) {
            if(target > nums[middle]) {
                left = middle;
            } else if(target >= nums[left]) {
                right = middle;
            } else {
                left = middle;
            }
        } else {
            if(target < nums[middle]) {
                right = middle;
            } else if(target >= nums[left]) {
                right = middle;
            } else {
                left = middle;
            }
        }
    }

    if(nums[left] == target) return true;
    if(nums[right] == target) return true;

    return false;
}

/**
 * @brief   Leetcode 34: Find First and Last Position of Element in Sorted Array
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 98.47%
 */
vector<int> searchRange(vector<int>& nums, int target)
{
    if(nums.empty()) {
        return vector<int>{-1, -1};
    }

    int left = 0;
    int right = nums.size() - 1;
    int startIndex = -1;
    int endIndex   = -1;
    while(left + 1 < right) {
        int middle = left + (right - left) / 2;
        if(nums[middle] == target) {
            startIndex = middle;
            endIndex = middle;
            break;
        } else if(nums[middle] > target) {
            right = middle;
        } else {
            left = middle;
        }
    }
    if(nums[left] == target) {
        startIndex = left;
        endIndex = left;
    }
    if(nums[right] == target) {
        startIndex = right;
        endIndex = right;
    }
    while(startIndex > 0 && nums[startIndex-1] == target) {
        startIndex -= 1;
    }
    while(endIndex < nums.size()-1 && nums[endIndex+1] == target) {
        endIndex += 1;
    }

    return vector<int>{startIndex, endIndex};
}
/**
 * @brief   Leetcode 11: Container With Most Water
 *  This method can be accepted, but time complexity is high, which is
 *  O(n^2).
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 12%
 */
int maxArea(vector<int>& height)
{
    if(height.size() < 2) {
        return 0;
    }
    int result = 0;
    int length = height.size();
    for(int dist = 1; dist < length; ++dist) {
        int maxHeight = 0;
        for(int i = 0; i < length && i + dist < length; ++i) {
			int tmp = std::min(height[i], height[i + dist]);
            if(maxHeight < tmp) {
                maxHeight = tmp;
            } else {
                continue;
            }
			result = std::max(result, tmp * dist);
        }
    }

    return result;
}

/**
 * @brief   Leetcode 11: Container with Most Water
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 98.5%
 */
int maxArea2(vector<int>& height)
{
    if(height.size() < 2) {
        return 0;
    }
	int i = 0;
	int j = height.size() - 1;
	int area = 0;
	while (i < j) {
		area = std::max(area, std::min(height[i], height[j]) * (j - i));
		if (height[i] < height[j]) {
			i += 1;
		} else {
			j -= 1;
		}
	}

	return area;
}

/**
 * @brief   Leetcode 26: Remove Duplicates from Sorted Array

 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 20%
 */
int removeDuplicates(vector<int>& nums)
{
    if(nums.size() < 2) {
        return nums.size();
    }

    auto prev = nums.begin();
    auto iter = prev + 1;
    while(iter != nums.end()) {

        if(*iter == *prev) {
            iter = nums.erase(iter);
        } else {
            prev = iter;
            iter += 1;
        }
    }

    return nums.size();
}

/**
 * @brief   Leetcode 26: Remove Duplicates from Sorted Array
 *  This solution is same as above one, but using index to iterate elements.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 20%
 */
int removeDuplicates2(vector<int>& nums)
{
    if(nums.size() < 2) {
        return nums.size();
    }

    for(int i = 1; i < nums.size(); ++i) {
        if(i < nums.size() && nums[i] == nums[i-1]) {
            nums.erase(nums.begin() + i);
            i -= 1;
        }
    }
    return nums.size();
}

/**
 * @brief   Leetcode 26: Remove Duplicates from Sorted Array
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
int removeDuplicates3(vector<int>& nums)
{
    if(nums.size() < 2) {
        return nums.size();
    }

    int dupFlag = -1;
    int i = 1;
    while(i < nums.size()) {
        if(dupFlag == -1 && nums[i] == nums[i-1]) {
            dupFlag = i;
        }
        if(nums[i] == nums[i-1] || dupFlag == -1) {
            i += 1;
        } else {
            nums[dupFlag++] = nums[i++];
        }
    }

    return (dupFlag == -1) ? nums.size() : dupFlag;
}

/**
 * @brief   Leetcode 80: Remove Duplicates from Sorted Array II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
int removeDuplicatesII(vector<int>& nums)
{

    if(nums.size() < 2) {
        return nums.size();
    }

    int dupFlag = -1;
    int i = 1;
    int count = 1;
    while(i < nums.size()) {
        // count number of duplicates
        if(nums[i] == nums[i-1]) {
            count += 1;
        } else {
            count = 1;
        }
        // label first twice more duplicates position
        if(dupFlag == -1 && count > 2) {
            dupFlag = i;
        }
        // exist twice more duplicates
        if(dupFlag != -1) {
            if(count <= 2)
                nums[dupFlag++] = nums[i++];
            else
                i += 1;
        } else { // no-exist twice more duplicates
            i += 1;
        }
    }

    return (dupFlag == -1) ? nums.size() : dupFlag;
}

/**
 * @brief   Leetcode 48: Rotate Image
 *  Those elements form a circle, just swap adjacent two 
 *  elements if rotete degree is 90.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
void rotate(vector<vector<int>>& matrix)
{
    size_t N = matrix[0].size();

    for(int i = 0; i < N/2; ++i) {
        for(int j = i; j < N-1-i; ++j) {
            int tmp = matrix[i][j];
            std::swap(tmp, matrix[j][N-1-i]);
            std::swap(tmp, matrix[N-1-i][N-1-j]);
            std::swap(tmp, matrix[N-1-j][i]);
            std::swap(tmp, matrix[i][j]);
        }
    }
}

/**
 * @brief   Leetcode 48: Roteta Image
 *  A general method when rotating image in clockwise way.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
void rotate2(vector<vector<int>>& matrix)
{
    std::reverse(matrix.begin(), matrix.end());
    const size_t N = matrix[0].size();
    for(int i = 0; i < N; ++i) {
        for(int j = i+1; j < N; ++j) {
            std::swap(matrix[i][j], matrix[j][i]);
        }
    }
}
/**
 * @brief   Leetcode 54: Spiral Matrix
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
vector<int> spiralOrder(vector<vector<int>>& matrix)
{
    if(matrix.empty()) {
        return vector<int>{};
    }
    vector<int> result;
    const size_t R = matrix.size();  // line number
    const size_t C = matrix[0].size();  // column number

    int row = 0, col = 0;
    int COUNT1 = (R%2 ? (R/2+1) : R/2);
	int COUNT2 = (C%2 ? (C/2+1) : C/2);
    while(row < COUNT1 && col < COUNT2) {
        // positive direction
        // line
        for(int j = col; j < C-col; ++j) {
            result.push_back(matrix[row][j]);
        }
        // column
        for(int i = row+1; i < R-row ; ++i) {
            result.push_back(matrix[i][C-col-1]);
        }
        // negative direction
        // line
        for(int j = C-col-2; j >= col && R-row-1 > row; --j) {
            result.push_back(matrix[R-row-1][j]);
        }
        // column
        for(int i = R-row-2; i > row && col < C-col-1; --i) {
            result.push_back(matrix[i][col]);
        }
        // refresh initial value
        row += 1;
        col += 1;
    }

    return result;
}

/**
 * @brief   Leetcode 54: Spiral Matrix
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
vector<int> spiralOrder2(vector<vector<int>>& matrix)
{
    vector<int> results;
    int R = matrix.size();
    if(R == 0) return results;

    int C = matrix[0].size();
    if(C == 0) return results;

    // record target steps in each direction
    vector<int> nSteps{C, R-1};
    // 4 directions to move pointer
    vector<vector<int>> direction{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int maker = 0; // index of direction
    int row = 0;  // initial position
    int col = -1;
    while(nSteps[maker%2]) {
        for(int i = 0; i < nSteps[maker%2]; ++i) {
            row += direction[maker][0];
            col += direction[maker][1];
            results.push_back(matrix[row][col]);
        }
        nSteps[maker%2] -= 1;
        maker = (maker + 1) % 4;
    }

    return results;
}

/**
 * @brief   Leetcode 59: Spiral Matrix II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
vector<vector<int>> generateMatrix(int n)
{
    if(n == 1) {
        return vector<vector<int>>{vector<int>{1}};
    }

    int acc = 1;
    int row = 0;
    int col = 0;
    int iter = ((n % 2) ? (n / 2 + 1) : n/2);
    vector<vector<int>> results(n, vector<int>(n, 0));
    while(acc <= n*n && row < iter && col < iter) {
        // from left to right in a row
        for(int i = col; i < n - col; ++i) {
            results[row][i] = acc++;
        }
        // from up to down in a column
        for(int j = row+1; j < n - row; ++j) {
            results[j][n - col - 1] = acc++;
        }
        // from right to left in a row
        for(int i = n - col - 2; i >= col && (n-row-1 > row); --i) {
            results[n - row - 1][i] = acc++;
        }
        // from down to up in a column
        for(int j = n - row - 2; j > row && (col < n-col-1); --j) {
            results[j][col] = acc++;
        }
        row++;
        col++;
    }

    return results;
}

/**
 * @brief   Leetcode 59: Spiral Matrix II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
vector<vector<int>> generateMatrix2(int n)
{
    if(n == 1) {
        return vector<vector<int>>{vector<int>{1}};
    }
    vector<vector<int>> directions = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    vector<vector<int>> results(n, vector<int>(n, 0));
    int SUM = 1;
    int row = 0;
    int col = 0;
    int DIR = 0;
    int iterCnt = 0;
    while(SUM <= n*n) {
        results[row][col] = SUM++;
        row = row + directions[DIR][0];
        col = col + directions[DIR][1];
        if((row == iterCnt && col == n-1-iterCnt) || (row == n-iterCnt-1 && col == n-iterCnt-1) ||
           (row == n-iterCnt-1 && col == iterCnt) || (row == iterCnt && col == iterCnt)) {
            DIR = (DIR + 1) % 4;
            if(DIR == 0) {
                iterCnt += 1;
                row = iterCnt;
                col = iterCnt;
            }

        }
    }

    return results;
}

/**
 * @brief	Leetcode 55: Jump Game
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 97%
 */
bool canJump(vector<int>& nums)
{
	if (nums.size() < 2) {
		return true;
	}

	const size_t N = nums.size();
	vector<int> dp(N, 0);
	int border = 0;
	for (int i = 0; i < N-1 && i <= border; ++i) {
		dp[i] = i + nums[i];
		border = std::max(dp[i], border);
		if(dp[i] >= N-1) {
			return true;
		}
	}

	return false;
}

/**
 * @brief	Leetcode 55: Jump Game
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 97%
 */
bool canJump2(vector<int>& nums)
{
    if(nums.size() < 2) {
        return true;
    }

    const size_t N = nums.size();
    int steps = nums[0];
    for(int i = 1; i < N; ++i) {
        steps--;
        if(steps < 0) {
            return false;
        }
        if(nums[i] > steps) {
            steps = nums[i];
        }
    }

    return true;
}

/**
 * @brief   Leetcode 45: Jump Games II
 *  In the problem, we can assume that we can always reach the last index.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 15%
 */
int jump(vector<int>& nums)
{
    if(nums.size() < 2) {
        return 0;
    }
    int result = INT_MAX;

    const size_t N = nums.size();
    vector<int> dp(N, 0);
    vector<int> steps(N, 0);
    for(int i = 0; i < N-1; ++i) {
        if(steps[i] >= result) {
            continue;
        }
        dp[i] = i + nums[i];
        for(int j = i+1; j <= dp[i] && j < N; ++j) {
            steps[j] = steps[j] > 0 ? std::min(steps[i]+1, steps[j]) : steps[i] + 1;
        }
        if(dp[i] >= N-1) {
            result = std::min(steps[i] + 1, result);
        }
    }

    return result;
}

/**
 * @brief   Leetcode 45: Jump Games II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99.58%
 */
int jump2(vector<int>& nums)
{
    if(nums.size() < 2) {
        return 0;
    }
    int end = 0;
    int steps = 0;
    int maxPos = 0;

    for(int i = 0; i < nums.size() - 1; ++i) {
        maxPos = std::max(maxPos, i + nums[i]);
        if(maxPos == nums.size() - 1) {
            return ++steps;
        }
        // each time we reach the right border determined by element
        // value, result will increase by 1.
        if(i == end) {
            end = maxPos;
            steps++;
        }
    }

    return steps;
}

/**
 * @brief   Leetcode 45: Jump Games II
 *  BFS method
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99.58%
 */
int jump3(vector<int>& nums)
{
    if(nums.size() < 2) {
        return 0;
    }

    int curMax = 0;
    int nextMax = 0;
    int level = 0;
    int i = 0;
    while(i  <= curMax) {
        level++;
        for(; i <= curMax; ++i) {
            nextMax = std::max(i + nums[i], nextMax);
            if(nextMax >= nums.size()-1) {
                return level;
            }
        }
        curMax = nextMax;
    }

    return 0;
}

/**
 * @brief   Leetcode 45: Jump Games II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 34.9%
 */
int jump4(vector<int>& nums)
{
    if(nums.size() < 2) {
        return 0;
    }
    const size_t N = nums.size();
    int position = N - 1;
    int steps = 0;
    while(position != 0) {
        for(int i = 0; i < position; ++i) {
            if(nums[i] >= position - i) {
                position = i;
                steps += 1;
                break;
            }
        }
    }

    return steps;
}

/**
 * @brief	Leetcode 56: Merge Intervals
 *  This method can NOT be accepted if we use pass-by-value in lambda statement in std::sort()
 *  function, which leads to heap overflow error.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99.7%
 */
vector<Interval> merge(vector<Interval>& intervals)
{
	if (intervals.size() < 2) {
		return intervals;
	}
    // pass-by-reference is necessary.
	std::sort(intervals.begin(), intervals.end(),
			  [](Interval& m, Interval& n){ return m.start <= n.start; } );
	int count = 0;
	for (int i = 0; i < intervals.size(); ++i) {
		Interval tmp(intervals[i].start, intervals[i].end);
		int j = i + 1;
		while (j < intervals.size() && tmp.end >= intervals[j].start) {
			tmp.start = std::min(tmp.start, intervals[j].start);
			tmp.end = std::max(tmp.end, intervals[j].end);
			j += 1;
		}

		intervals[count].start = tmp.start;
		intervals[count].end = tmp.end;
		i = j - 1;
		count += 1;
	}

	intervals.resize(count);
	return intervals;
}

/**
 * @brief	Leetcode 56: Merge Intervals
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 83.2%
 */
vector<Interval> merge2(vector<Interval>& intervals)
{
    if(intervals.size() < 2) {
        return intervals;
    }
    vector<Interval> results;
    unordered_map<int, int> mStartToInterval;
    int minStart = INT_MAX;
    int maxStart = INT_MIN;
    for(int i = 0; i < intervals.size(); ++i) {
        minStart = std::min(intervals[i].start, minStart);
        maxStart = std::max(intervals[i].start, maxStart);
        if(mStartToInterval.find(intervals[i].start) != mStartToInterval.end()) {
            mStartToInterval[intervals[i].start] = std::max(mStartToInterval[intervals[i].start],
                                                            intervals[i].end - intervals[i].start + 1);
        } else {
            mStartToInterval[intervals[i].start] = intervals[i].end - intervals[i].start + 1;
        }
    }

    while(minStart <= maxStart) {
        if(mStartToInterval.find(minStart) == mStartToInterval.end()) {
            minStart += 1;
            continue;
        }
        int curMax = mStartToInterval[minStart] + minStart - 1;
        int index = minStart + 1;
        while(index <= maxStart && index <= curMax) {
            if(mStartToInterval.find(index) != mStartToInterval.end()) {
                curMax = std::max(curMax, mStartToInterval[index] + index - 1);
            }
            index += 1;
        }
        results.push_back(Interval(minStart, curMax));
        minStart = curMax + 1;
    }

    return results;
}

/**
 * @brief   Leetcode 57: Insert Intervals
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 98.7%
 */
vector<Interval> insert(vector<Interval>& intervals, Interval newInterval)
{

    if(intervals.empty()) {
        return vector<Interval>{newInterval};
    }

    int sIndex = 0;
    const size_t N = intervals.size();
    int i = 0;
    while(i < N) {
        if(newInterval.start <= intervals[i].start) {
            sIndex = (i == 0 ? 0 : i - 1);
            intervals.insert(intervals.begin() + i, newInterval);
            break;
        }
        i += 1;
    }
    if(i == N) {
        intervals.insert(intervals.end(), newInterval);
        sIndex = N - 1;
    }

    int count = sIndex;
    for (int i = sIndex; i < intervals.size(); ++i) {
        Interval tmp(intervals[i].start, intervals[i].end);
        int j = i + 1;
        while (j < intervals.size() && tmp.end >= intervals[j].start) {
            tmp.end = std::max(tmp.end, intervals[j].end);
            j += 1;
        }
        intervals[count].start = tmp.start;
        intervals[count].end = tmp.end;
        i = j - 1;
        count += 1;
    }

    intervals.resize(count);
    return intervals;
}

/**
 * @brief   Leetcode 62: Unique Paths
 *  dp[i][j] means all unique paths to arrive at the point (i, j)
 *  time complexity is O(m*n), space complexity is O(m*n)
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
int uniquePaths(int m, int n)
{
    vector<vector<int>> dp(m, vector<int>(n, 1));
    for(int i = 1; i < m; ++i) {
        for(int j = 1; j < n; ++j) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }

    return dp[m-1][n-1];
}

/**
 * @brief   Leetcode 62: Unique Paths
 *  space complexity is O(n)
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
int uniquePaths2(int m, int n)
{
    vector<int> pre(n, 1), cur(n, 1);
    for(int i = 1; i < m; ++i) {
        for(int j = 1; j < n; ++j) {
            cur[j] = pre[j] + cur[j-1];
        }
        std::swap(pre, cur);
    }

    return pre[n-1];
}

/**
 * @brief   Leetcode 62: Unique Paths
 *  space complexity is O(n)
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
int uniquePaths3(int m, int n)
{
    vector<int> cur(n, 1);

    for(int i= 1; i < m; ++i) {
        for(int j = 1; j < n; ++j) {
            cur[j] += cur[j-1];
        }
    }

    return cur[n-1];
}

/**
 * @brief   Leetcode 62: Unique Paths
 *  Mathematical solution
 *  Move m-1 steps down and n-1 steps right, so this problem is nothing but a 
 *  permutation problem.
 *  result = (m + n)! / (m! * n!)
 *  time complexity is O(1).
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
int uniquePaths4(int m, int n)
{
    if(m == 1 || n == 1) {
        return 1;
    }
    if(m < n) {
        std::swap(m, n);
    }
    m--; n--;
    int j = 1;
    int result = 1;
    for(int i = m + 1; i <= m + n; ++i, ++j) {
        result *= i;
        result /= j;
    }

    return result;
}

/**
 * @brief   Leetcode 63: Unique Paths II
 *  The key of the problem is how to return correct result(0) when
 *  all obstacles block each possible paths.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
{
    if(obstacleGrid[0][0])
        return 0;

    const size_t row = obstacleGrid.size();
    const size_t col = obstacleGrid[0].size();

    // initialize first row and first column elements in 1 before first obstacle
    // other elements in 0
    vector<vector<long int>> dp(row, vector<long int>(col, 0));
    for(int i = 0; i < row; ++i) {
        if(obstacleGrid[i][0] == 0)
            dp[i][0] = 1;
        else
            break;
    }
    for(int j = 1; j < col; ++j) {
        if(obstacleGrid[0][j] == 0)
            dp[0][j] = 1;
        else
            break;
    }
    // calculate all paths with obstacles in grid
    for(int i = 1; i < row; ++i) {
        for(int j = 1; j < col; ++j) {
            if(obstacleGrid[i][j] || (obstacleGrid[i-1][j] && obstacleGrid[i][j-1])) {
                continue;
            } else if(obstacleGrid[i-1][j]){
                dp[i][j] = dp[i][j-1];
            } else if(obstacleGrid[i][j-1]) {
                dp[i][j] = dp[i-1][j];
            } else {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
    }

    return dp[row-1][col-1];
}

/**
 * @brief   Leetcode 63: Unique Paths II
 *  Use same method with above solution, but not create extra arrays to save paths instead
 *  of using existent grid.
 *  time complexity is O(M*N), space complexity is O(1).
 *  This solution can NOT be accepted because path number can be greater than integer up-limit.
 *
 */
int uniquePathsWithObstacles2(vector<vector<int>>& obstacleGrid)
{
    // initialize
    if(obstacleGrid[0][0]) {
        return 0;
    } else {
        obstacleGrid[0][0] = 1;
    }
    const size_t row = obstacleGrid.size();
    const size_t col = obstacleGrid[0].size();

    for(size_t i = 1; i < row; ++i) {
        obstacleGrid[i][0] = ((obstacleGrid[i][0] == 0 && obstacleGrid[i-1][0] == 1) ? 1 : 0);
    }
    for(size_t j = 1; j < col; ++j) {
        obstacleGrid[0][j] = ((obstacleGrid[0][j] == 0 && obstacleGrid[0][j-1] == 1) ? 1 : 0);
    }

    // get all paths
    for(size_t i = 1; i < row; ++i) {
        for(size_t j = 1; j < col; ++j) {
            if(obstacleGrid[i][j] == 0) {
                obstacleGrid[i][j] = obstacleGrid[i-1][j] + obstacleGrid[i][j-1];
            } else {
                obstacleGrid[i][j] = 0;
            }
        }
    }

    return obstacleGrid[row-1][col-1];
}

/**
 * @brief   Leetcode 980: Unique Paths III
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
static void uniquePathsIIIHelperUtil(vector<vector<int>>& grid,
                                     int row, int col,
                                     vector<int>& end,
                                     const size_t R, const size_t C,
                                     int countOfzeroes, int& results,
                                     int sum, int zero)
{
    int temp = grid[row][col];
    if(temp == 0) { zero += 1; }
    // stop search process when reaching the endpoint or the square has been traversed
    if((row == end[0] && col == end[1]) || temp == INT_MAX) {
        if(zero == countOfzeroes && (temp != INT_MAX && sum+temp == 3)) {
            results += 1;
        }
        return;
    }
    sum += temp;
    grid[row][col] = INT_MAX;

    if(row-1 >= 0) uniquePathsIIIHelperUtil(grid, row-1, col, end, R, C, countOfzeroes, results, sum, zero);
    if(row+1 < R)  uniquePathsIIIHelperUtil(grid, row+1, col, end, R, C, countOfzeroes, results, sum, zero);
    if(col-1 >= 0) uniquePathsIIIHelperUtil(grid, row, col-1, end, R, C, countOfzeroes, results, sum, zero);
    if(col+1 < C)  uniquePathsIIIHelperUtil(grid, row, col+1, end, R, C, countOfzeroes, results, sum, zero);

    grid[row][col] = temp;
}
static void uniquePathsIIIHelper(vector<vector<int>>& grid,
                            vector<int>& start, vector<int>& end,
                            const size_t R, const size_t C,
                            int countOfzeroes,
                            int& results)
{
    int sum = 0;
    int zero = 0;
    int row = start[0], col = start[1];
    uniquePathsIIIHelperUtil(grid, row, col, end, R, C, countOfzeroes, results, sum, zero);
}
int uniquePathsIII(vector<vector<int>>& grid)
{
    // initialization
    const size_t R = grid.size();
    const size_t C = grid[0].size();
    size_t countOfzeroes = 0;
    vector<int> start(2,-1), end(2, -1);
    // get index of startpoint and endpoint, and the number of ZEROes
    for(size_t i = 0; i < R; ++i) {
        for(size_t j = 0; j < C; ++j) {
            if(grid[i][j] == 1) { start[0] = i; start[1] = j; }
            if(grid[i][j] == 2) { end[0] = i; end[1] = j; }
            if(grid[i][j] == 0) { countOfzeroes += 1; }
        }
    }

    int results = 0;
    uniquePathsIIIHelper(grid, start, end, R, C, countOfzeroes, results);

    return results;
}

/**
 * @brief   Minimum Path Sum
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99.25%
 */
int minPathSum(vector<vector<int>>& grid)
{
    if(grid.empty()) {
        return 0;
    }
    const size_t row = grid.size();
    const size_t col = grid[0].size();
    for(int i = 1; i < row; ++i) {
        grid[i][0] += grid[i-1][0];
    }
    for(int j = 1; j < col; ++j) {
        grid[0][j] += grid[0][j-1];
    }
    for(int i = 1; i < row; ++i) {
        for(int j = 1; j < col; ++j) {
            grid[i][j] += std::min(grid[i-1][j], grid[i][j-1]);
        }
    }

    return grid[row-1][col-1];
}

/**
 * @brief   Leetcode 73: Set Matrix Zeroes
 *  Create extra space O(m*n) to save falgs in the positions with zero values
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99%
 */
void setZeroes(vector<vector<int>>& matrix)
{

    if(matrix.empty()) {
        return;
    }

    // search zero element and then save index in an array
    const size_t row = matrix.size();
    const size_t col = matrix[0].size();
    vector<int> mark;
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            if(matrix[i][j] == 0) {
                mark.push_back(i * col + j);
            }
        }
    }
    // traverse zero falg array and set zero at corresponding rows and columns
    for(int i = 0; i < mark.size(); ++i) {
        int R = mark[i] / col;
        int C = mark[i] - R*col;
        std::fill(matrix[R].begin(), matrix[R].end(), 0);  // set whole row values as zeroes 
        for(int j = 0; j < row; ++j) {  // set whole column values as zeroes
            matrix[j][C] = 0;
        }
    }
}

/**
 * @brief   Leetcode 73: Set Matrix Zeroes
 *  Time complexity is O(m*n), space complexity is O(m+n)
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99.4%
 */
void setZeroes2(vector<vector<int>>& matrix)
{
    if(matrix.empty()) {
        return;
    }
    const size_t row = matrix.size();
    const size_t col = matrix[0].size();
    unordered_set<int> rIndex;
    unordered_set<int> cIndex;

    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            if(matrix[i][j] == 0) {
                if(rIndex.find(i) == rIndex.end()) {
                    rIndex.insert(i);
                }
                if(cIndex.find(j) == cIndex.end()) {
                    cIndex.insert(j);
                }
            }
        }
    }

    for(auto& i: rIndex) {
        std::fill(matrix[i].begin(), matrix[i].end(), 0);
    }

    for(auto& j: cIndex) {
        for(int i = 0; i < row; ++i) {
            matrix[i][j] = 0;
        }
    }
}

/**
 * @brief   Leetcode 74: Search a 2D Matrix
 *  This solution uses two divisions algorithm twice - one
 *  for determining target row number, another for target.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 98.6%
 */
bool searchMatrix(vector<vector<int>>& matrix, int target)
{
    if(matrix.empty() || matrix[0].empty()) {
        return false;
    }
    // first two divisions: get target row number
    size_t R = matrix.size()-1;
    int up = 0, down = R;
    while(up+1 < down) {
        int mid = up + (down - up) / 2;
        if(matrix[mid][0] <= target) {
            up = mid;
        } else {
            down = mid;
        }
    }
    if(matrix[up][0] <= target) R = up;
    if(matrix[down][0] <= target) R = down;

    // second two divisions: get target index number
    int left = 0;
    int right = matrix[R].size() - 1;
    while(left + 1 < right) {
        int mid = left + (right - left) / 2;
        if(matrix[R][mid] == target) {
            return true;
        }
        if(matrix[R][mid] <= target) {
            left = mid;
        } else {
            right = mid;
        }
    }
    if(matrix[R][left] == target || matrix[R][right] == target) { return true; }

    return false;
}

/**
 * @brief   Leetcode 240: Search a 2D Matrix II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 25%
 */
bool searchMatrixII(vector<vector<int>>& matrix, int target)
{
    if(matrix.empty() || matrix[0].empty()) {
        return false;
    }

    int R = matrix.size() - 1;
    int C = matrix[0].size() - 1;
    int uLevel = 0, bLevel = R;
    while(uLevel < bLevel) {
        if(matrix[uLevel][C] < target) uLevel++;
        else break;
    }
    while(bLevel > uLevel) {
        if(matrix[bLevel][0] > target) bLevel--;
        else break;
    }

    for(R = uLevel; R <= bLevel; ++R) {
        int left = 0;
        int right = C;
        while(left + 1 < right) {
            int mid = left + (right - left) / 2;
            if(matrix[R][mid] == target) {
                return true;
            }
            if(matrix[R][mid] > target) {
                right = mid;
            } else {
                left = mid;
            }
        }
        if(matrix[R][left] == target || matrix[R][right] == target) { return true; }
    }

    return false;
}

/**
 * @brief   Leetcode 75: Sort Colors
 *  This solution can solve the problem, but not perfect bacause in some cases, assign
 *  a value in certain position directly is not a good choice or meeting our demands.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
void sortColors(vector<int>& nums)
{
    if(nums.empty() || nums.size() < 2) {
        return;
    }

    vector<int> count(3, 0);
    for(int i = 0; i < nums.size(); ++i) {
        count[nums[i]] += 1;
    }

    int k = 0;
    for(int i = 0; i < 3; ++i) {
        for(int j = 1; j <= count[i]; ++j) {
            nums[k++] = i;
        }
    }
}

/**
 * @brief   Leetcode 75: Sort Colors
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
void sortColors2(vector<int>& nums)
{
    if(nums.empty() || nums.size() < 2) {
        return;
    }
    int pre = 0;
    for(int i = 0;  i < nums.size(); ++i) {
        if(nums[i] == 0) {
            std::swap(nums[pre], nums[i]);
            pre++;
        }
    }
    for(int i = pre; i < nums.size(); ++i) {
        if(nums[i] == 1) {
            std::swap(nums[pre], nums[i]);
            pre++;
        }
    }
    for(int i = pre; i < nums.size(); ++i) {
        if(nums[i] == 2) {
            std::swap(nums[pre], nums[i]);
            pre++;
        }
    }
}

/**
 * @brief   Leetcode 79: Word Search
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 98.98%
 */
static bool existDFS(vector<vector<char>>& board,
					 int row, int col,
					 const string& word,
					 int index,
					 const size_t R, const size_t C)
{
	if (board[row][col] != word[index]) {
		return false;
	}
	if (index == word.size()-1) {
		return true;
	}
    // change the content, to avoid duplicated search
	char temp = board[row][col];
	board[row][col] = '*';

	bool res = false;
	if (row-1 >= 0) {
		res = existDFS(board, row-1, col, word, index+1, R, C);
	}
	if (!res && row+1 < R) {
		res = existDFS(board, row+1, col, word, index+1, R, C);
	}
	if (!res && col-1 >= 0) {
		res = existDFS(board, row, col-1, word, index+1, R, C);
	}
	if (!res && col+1 < C) {
		res = existDFS(board, row, col+1, word, index+1, R, C);
	}
	board[row][col] = temp;  // change content back!

	return res;
}
bool exist(vector<vector<char>>& board, string word)
{
	if(board.empty() || board[0].empty()){
		if(word.empty()) return true;
		else return false;
	}

	const size_t R = board.size();
	const size_t C = board[0].size();
	for (int i = 0; i < R; ++i) {
		for (int j = 0; j < C; ++j) {
			if (existDFS(board, i, j, word, 0, R, C)) {
				return true;
			}
		}
	}

	return false;
}

/**
 * @brief   Leetcode 212: word Search II
 *  Reusing solution to the problem 79, this one can be accepted, but efficiency is
 *  low.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 18.5%
 */
vector<string> findWords(vector<vector<char>>& board, vector<string>& words)
{
    vector<string> results;

    if(board.empty() || board[0].empty()) {
        if(words.empty()) {
            return vector<string>{};
        }
    }

    for(auto& word : words) {
        if(exist(board, word)) {
            results.push_back(word);
        }
    }

    return results;
}

/**
 * @brief   Leetcode 212: Word Search II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 19%
 */
static bool findWordsHelper(vector<vector<char>>& board,
						   int row, int col,
						   const string& word, int index,
						   const int R, const int C)
{
	if(board[row][col] != word[index]) {
		return false;
	}
	if(index == word.size() - 1) {
		return true;
	}
	bool res = false;
	char temp = board[row][col];
	board[row][col] = '*';
	
	if(row-1 >= 0)         res = findWordsHelper(board, row-1, col, word, index+1, R, C);
	if(!res && row+1 < R)  res = findWordsHelper(board, row+1, col, word, index+1, R, C);
	if(!res && col-1 >= 0) res = findWordsHelper(board, row, col-1, word, index+1, R, C);
	if(!res && col+1 < C)  res = findWordsHelper(board, row, col+1, word, index+1, R, C);
	
	board[row][col] = temp;
	
	return res;
}
vector<string> findWords2(vector<vector<char>>& board, vector<string>& words)
{
	vector<string> results;
	std::sort(words.begin(), words.end());
	unordered_map<char, int> charToIndex;
	int index = 0;
	for(auto& word: words) {
		if(charToIndex.find(word[0]) == charToIndex.end())
			charToIndex[word[0]] = index;
		
		index += 1;
	}
	
	const int R = board.size();
	const int C = board[0].size();
	for(int i = 0; i < R; ++i) {
		for(int j = 0; j < C; ++j) {
			if(charToIndex.find(board[i][j]) != charToIndex.end()) {
				index = charToIndex[board[i][j]];
				while(index < words.size() && words[index][0] == board[i][j]) {
					if(findWordsHelper(board, i, j, words[index], 0, R, C)) {
						if(std::find(results.begin(), results.end(), words[index]) == results.end())
							results.push_back(words[index]);
					}
					index += 1;
				}
			}
		}
	}
	
	return results;
}

/**
 * @brief   Leetcode 212: Word Search II
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 18.85%
 */
vector<string> findWords3(vector<vector<char>>& board, vector<string>& words)
{
    const int R = board.size();
    const int C = board[0].size();
    vector<vector<std::pair<int, int>>> charToPos(26, vector<std::pair<int, int>>{}); 
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            charToPos[board[i][j] - 'a'].push_back(std::make_pair(i, j));
        }
    }

    std::sort(words.begin(), words.end());
    vector<string> results;
    for(auto& word: words) {
        if(charToPos[word[0]-'a'].empty()) {
            continue;
        }
        for(int k = 0; k < charToPos[word[0]-'a'].size(); ++k) {
            int i = charToPos[word[0]-'a'][k].first;
            int j = charToPos[word[0]-'a'][k].second;
            if(findWordsHelper(board, i, j, word, 0, R, C)) {
                results.push_back(word);
                break;
            }
        }
    }

    return results;
}

/**
 * @brief   Leetcode 212: Word Search II
 *  This is a typical Trie problem. We can using trie data structure to solve this problem
 *  in a more efficient way but higher space complexity.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 89.65%
 */
static TrieNode* buildTrie(vector<string>& words)
{
    TrieNode* root = new TrieNode();

    for(int i = 0; i < words.size(); ++i) {
        TrieNode* node = root;
        for(int j = 0; j < words[i].size(); ++j) {
            int index = words[i][j] - 'a';
            if(node->child[index] == nullptr) {
                node->child[index] = new TrieNode();
            }
            node = node->child[index];
        }
        node->word = words[i];
    }

    return root;
}
static void findWordsHelper(vector<vector<char>>& board, int row, int col,
                            TrieNode* node, const int R, const int C,
                            vector<string>& results)
{
    char temp = board[row][col];
    if(temp == '*' || node->child[temp-'a'] == nullptr) {
        return;
    }
    if(node->child[temp-'a']->word != "") {
        results.push_back(node->child[temp-'a']->word);
        node->child[temp-'a']->word = "";  // avoid duplicates
        // NOT return because longer strings should also be traversed
    }
    board[row][col] = '*';
    if(row-1 >= 0) findWordsHelper(board, row-1, col, node->child[temp-'a'], R, C, results);
    if(row+1 < R)  findWordsHelper(board, row+1, col, node->child[temp-'a'], R, C, results);
    if(col-1 >= 0) findWordsHelper(board, row, col-1, node->child[temp-'a'], R, C, results);
    if(col+1 < C)  findWordsHelper(board, row, col+1, node->child[temp-'a'], R, C, results);
    board[row][col] = temp;
}
vector<string> findWords4(vector<vector<char>>& board, vector<string>& words)
{
    TrieNode* root = buildTrie(words);

    vector<string> results;
    const size_t R = board.size();
    const size_t C = board[0].size();
    for(int i = 0; i < R; ++i) {
        for(int j = 0; j < C; ++j) {
            findWordsHelper(board, i, j, root, R, C, results);
        }
    }

    return results;
}

/**
 * @brief   Leetcode 37: Sudoku Solver
 *  ToDo: 10/4/2019
 */
void solveSudoku(vector<vector<char>>& board)
{

}

/**
 * @brief   Leetcode 120: Triangle
 *  This code can pass simple cases, but if the triangle is too large,
 *  execution will exceed time limit.
 *
 */
static void minimumTotalHelper(vector<vector<int>>& triangle,
                               size_t row, size_t col, const size_t R,
                               int& minSum, int sum)
{
    if(row == R-1) {
        minSum = std::min(minSum, sum + triangle[row][col]);
        return;
    }
    sum += triangle[row][col];

    minimumTotalHelper(triangle, row+1, col, R, minSum, sum);
    minimumTotalHelper(triangle, row+1, col+1, R, minSum, sum);
}
int minimumTotal(vector<vector<int>>& triangle)
{
    if(triangle.empty() || triangle[0].empty()) {
        return 0;
    }
    const size_t R = triangle.size();
    int minSum = INT_MAX;

    minimumTotalHelper(triangle, 0, 0, R, minSum, 0);

    return minSum;
}

/**
 * @brief	Leetcode 120: Triangle
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99.53%
 */
int minimumTotal2(vector<vector<int>>& triangle)
{
	if(triangle.empty() || triangle[0].empty()) {
		return 0;
	}
	
	const size_t R = triangle.size();
	for (int i = R-1; i > 0; --i) {
		size_t C = triangle[i].size();
		for (int j = 0; j < C-1; ++j) {
			triangle[i-1][j] = std::min(triangle[i][j] + triangle[i-1][j],
										triangle[i][j+1] + triangle[i-1][j]);
		}
	}
	
	return triangle[0][0];
}

/*
 * @brief	Leetcode 152: Maximum Product Subarray
 *	This is a brute force solution, which can be accepted, but
 *  a low efficiency.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 5%
 */
int maxProduct(vector<int>& nums)
{
	int result = INT_MIN;
	const size_t SIZE = nums.size();
	for (int i = SIZE - 1; i >= 0; --i) {
		int sum = 1;
		for (int j = i; j >= 0; --j) {
			sum *= nums[j];
			result = std::max(result, sum);
		}
	}
	return result;
}

/**
 * @brief   Leetcode 152: Maximum Product Subarray
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
int maxProduct2(vector<int>& nums)
{
    int result = nums[0];

    int imax = result;
    int imin = result;
    for(int i = 1; i < nums.size(); ++i) {
        // if multiplied by a negative number, the maximum and the minimum
        // will exchange
        if(nums[i] < 0) {
            std::swap(imax, imin);
        }
        imax = std::max(nums[i], imax * nums[i]);
        imin = std::min(nums[i], imin * nums[i]);

        result = std::max(result, imax);
    }

    return result;
}

/**
 * @brief   Leetcode 713: Subarray Product Less Than K
 *  In this array, all elements are positive integers.
 *  Notice: if duplicate elements exist, subarray can be duplicate.
 *  This solution can get correct result, but time limit exceeded.
 *
 */
static void numSubarrayProductLessThanKHelper(vector<int>& nums, int start,
                                       const int k, int product,
                                       int& count)
{
    if(product >= k) {
        return;
    } else {
        count++;
    }
    for(int i = start+1; i < nums.size(); ++i) {
        product *= nums[i];
        if(product < k) count++;
        else break;
    }
}
int numSubarrayProductLessThanK(vector<int>& nums, int k)
{
    int count = 0;
    for(int i = 0; i < nums.size(); ++i){
        int product = nums[i];
        numSubarrayProductLessThanKHelper(nums, i, k, product, count);
    }

    return count;
}

/**
 * @brief   Leetcode 713: Subarray Product Less Than K
 *  This method can be accepted, but not efficient. This solution transforms
 *  the problem into a 2-divisions question from a product because the product
 *  may be too large and exceed int scope.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 5.73%
 */
int numSubarrayProductLessThanK2(vector<int>& nums, int k)
{
    int result = 0;
    double logk = log(k);
    // get log values of all elements in number array
    vector<double> logNums(nums.size()+1, 0);
    for(int i = 0; i < nums.size(); ++i) {
        logNums[i+1] = logNums[i] + log(nums[i]);
    }

    for(int i = 0; i < nums.size(); ++i) {
        int left = i + 1;
        int right = logNums.size();  // if right = logNums.size()-1, the last element will not be included
        while(left < right) {
            int mid = left + (right - left) / 2;
            if(logNums[mid] - logNums[i] < logk - 0.000001) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        result += left - i - 1;
    }

    return result;
}

/**
 * @brief Leetcode 713: Subarray Product Less Than K
 *  This method is called slide window.
 *  Maintain a max-product-window less than K. If a new introduced element
 *  makes product window greater than K, move left border forward until product
 *  window less than K.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 78.23%
 */
int numSubarrayProductLessThanK3(vector<int>& nums, int k)
{
    int result = 0;
    int left = 0;
    int prod = 1;
    for(int i = 0; i < nums.size(); ++i) {
        prod *= nums[i];
        while(left <= i && prod >= k) {
            prod /= nums[left];
            left++;
        }
        result += i - left + 1;
    }

    return result;
}

/**
 * @brief   Leetcode 560: Subarray Sum Equals K
 *  Notice: The numbers are not all positive.
 *  Brute force solutionr. Can be accepted, but not efficient.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 26%
 */
int subarraySum(vector<int>& nums, int k)
{
    int result = 0;

    for(int i = 0; i < nums.size(); ++i) {
        int sum = 0;
        for(int j = i; j < nums.size(); ++j) {
            sum += nums[j];
            if(sum == k) { result += 1; }
        }
    }

    return result;
}

/**
 * @brief	Leetcode 560: Subarray Sum Equals K
 *  time complexity is O(n), space complexity is also O(n)
 *  This method uses more extra space in order to get faster.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 78%
 */
int subarraySum2(vector<int>& nums, int k)
{
    int result = 0;

    // sumOfNumbers[i]: sum of all elements from 0 to i
    // if it is allowed to change the value of nums, we needn't
    // create extra sum vector.
    // sumToCount[i]:   count of values that in sumOfNumbers
    vector<int> sumOfNumbers(nums.size(), 0);
    unordered_map<int, int> sumToCount;
    sumToCount[nums[0]] = 1;
    sumOfNumbers[0] = nums[0];
    for (int i = 1; i < nums.size(); ++i) {
        sumOfNumbers[i] = sumOfNumbers[i-1] + nums[i];
        if(sumToCount.find(sumOfNumbers[i]) != sumToCount.end()) {
            sumToCount[sumOfNumbers[i]] += 1;
        } else {
            sumToCount[sumOfNumbers[i]] = 1;
        }
    }

    // sumOfNumbers[k]: the sum of all elements starting from index 0 is k
    if(sumToCount.find(k) != sumToCount.end()) {
        result += sumToCount[k];
    }
    // the sum of elements starting from index (i+1) is k
    for(int i = 0; i < nums.size(); ++i) {
        // if the sum at index i is not used, decrease sumToCount by 1
        // because we only calculate the sum of elements starting from index i+1
        sumToCount[sumOfNumbers[i]] -= 1;
        if(sumToCount.find(sumOfNumbers[i]+k) != sumToCount.end()) {
            result += sumToCount[sumOfNumbers[i]+k];
        }
    }

    return result;
}

/**
 * @brief Leetcode 560: Subarray Sum Equals K
 *  This solution use above method inversely, which can simplify the procedure
 *  to a great extent.
 *  Brilliant and elegant!
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99%
 */
int subarraySum3(vector<int>& nums, int k)
{
    int result = 0;

    unordered_map<int, int> mSumToCount;
    int curSum = 0;

    mSumToCount[0] = 1;
    for(int i = 0; i < nums.size(); ++i) {
        curSum += nums[i];
        if(mSumToCount.find(curSum - k) != mSumToCount.end()) {
            result += mSumToCount[curSum - k];
        }
        mSumToCount[curSum] += 1;
    }

    return result;
}

/**
 * @brief   Leetcode 238: Product of Array Except Self
 *  Notice: Should solve it without division and in O(n)
 *  This method can solve this problem in O(n) time and O(n) space.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 78%
 */
vector<int> productExceptSelf(vector<int>& nums)
{
    vector<int> result(nums.size(), 1);

    vector<int> productToIndex(nums.size(), 1);
    productToIndex[0] = nums[0];
    for(int i = 1; i < nums.size(); ++i) {
        productToIndex[i] = productToIndex[i-1] * nums[i];
    }
    int factor = 1;
    for(int i = nums.size()-1; i > 0; --i) {
        result[i] = productToIndex[i-1] * factor;
        factor *= nums[i];
    }
    result[0] = factor;

    return result;
}

/**
 * @brief   Leetcode 238: Product of Array Except Self
 *  Use same method as above solution, but create constant
 *  extra space.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99%
 */
vector<int> productExceptSelf2(vector<int>& nums)
{
    vector<int> result(nums.size(), 1);
    result[0] = nums[0];
    for(int i = 1; i < nums.size(); ++i) {
        result[i] = result[i-1] * nums[i];
    }

    int factor = 1;
    for(int i = nums.size()-1; i > 0; --i) {
        result[i] = result[i-1] * factor;
        factor *= nums[i];
    }
    result[0] = factor;

    return result;
}

/**
 * @brief   Leetcode 153: Find Minimum in Rotated Array
 *  No duplicats exist in this array.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
int findMin(vector<int>& nums)
{
    int left = 0;
    int right = nums.size() - 1;

    if(nums[left] < nums[right]) {
        return nums[left];
    }
    while(left < right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] < nums[right]) {
            right = mid;
        } else {
            left = mid;
        }
    }
    return (nums[left] > nums[right]) ? nums[right] : nums[left];
}

/**
 * @brief   Leetcode 154: Find Minimum in Rotated Array II
 *  Exist duplicates in the array.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99.38%
 */
int findMinII(vector<int>& nums)
{
    int left = 0;
    int right = nums.size() - 1;

    if(nums[left] < nums[right]) {
        return nums[left];
    }
    while(left + 1 < right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] < nums[right]) {
            right = mid;
        } else if(nums[mid] > nums[right]){
            left = mid;
        } else {
            while(nums[right] == nums[mid] && right >= mid) {
                right -= 1;
            }
            if(right <= mid) {
                right = mid;
            } else {
                left = mid;
            }
        }
    }
    return (nums[left] >= nums[right]) ? nums[right] : nums[left];
}

/**
 * @brief   Leetcode 162: Find Peak Element
 *  This method scans this array and return the first peak.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99%
 */
int findPeakElement(vector<int>& nums)
{
    if(nums.size() < 2 || nums[0] > nums[1]) {
        return 0;
    }
    for(int i = 1; i < nums.size()-1; ++i) {
        if(nums[i] > nums[i-1] && nums[i] > nums[i+1]) {
            return i;
        }
    }

    return nums.size()-1;
}

/**
 * @brief   Leetcode 162: Find Peak Element
 *  Below method is a modification of Binary Search.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99%
 */
int findPeakElement2(vector<int>& nums)
{
    if(nums.size() < 2 || nums[1] < nums[0]) {
        return 0;
    }
    int left = 0;
    int right = nums.size() - 1;
    while(left + 1 < right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] < nums[mid+1]) {
            left = mid;
        } else {
            right = mid;
        }
    }
    return right;
}

/**
 * @brief	Leetcode 209: Minimum Size Subarray Sum
 *  time complexity is O(n).
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 98.52%
 */
int minSubArrayLen(int s, vector<int>& nums)
{
	int result = INT_MAX;

	int post = 0;
	int sum = 0;
	for (int i = 0; i < nums.size(); ++i) {
		sum += nums[i];
		while (sum >= s) {
			result = std::min(result, i-post+1);
			sum -= nums[post];
			post += 1;
		}
	}
	if(result == INT_MAX) result = 0;

	return result;
}

/**
 * @brief   Leetcode 209: Minimum Size Subarray Sum
 *  time complexity is O(nlogn).
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 98.54%
 */
static int findMinSubArrayLenHelper(vector<int>& nums,
                                     int start, int sum)
{
    int left = start;
    int right = nums.size() - 1;
    while(left + 1 < right) {
        int mid = left + (right - left) / 2;
        if(nums[mid] < sum) {
            left = mid;
        } else {
            right = mid;
        }
    }
    if(nums[left] >= sum) return left;
    if(nums[right] >= sum) return right;
    return INT_MAX;
}
int minSubArrayLen2(int s, vector<int>& nums)
{
    int result = INT_MAX;

    for(int i = 1; i < nums.size(); ++i) {
        nums[i] += nums[i-1];
    }

    int sum;
    for(int i = 0; i < nums.size(); ++i) {
        if(i == 0) sum = s;
        else sum = nums[i-1] + s;
        int temp = findMinSubArrayLenHelper(nums, i, sum);
        if(temp != INT_MAX) {
            result = std::min(result, temp - i + 1);
        }
    }

    if(result == INT_MAX) result = 0;
    return result;
}

/**
 * @brief   Leetcode 718: Maximum Length of Repeated Subarray
 *  This is a brute force solution with high time complexity.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 5.45%
 */
int findLength(vector<int>& A, vector<int>& B)
{
    int result = INT_MIN;

    for(int i = 0; i < A.size(); ++i) {
        for(int j = 0; j < B.size(); ++j) {
            int count = 0;
            while(i+count < A.size() && j+count < B.size() &&
                  A[i+count] == B[j+count]) {
                count += 1;
            }
            result = std::max(count, result);
            if(j+result >= B.size()) break;
        }
        if(i+result >= A.size()) break;
    }
    return result;
}

/**
 * @brief   Leetcode 718: Maximum Length of Repeated Subarray
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 30%
 */
int findLength2(vector<int>& A, vector<int>& B)
{
    int result = 0;

    int m = A.size();
    int n = B.size();
    vector<vector<int>> dp(m+1, vector<int>(n+1,0));
    for(int i = m-1; i >= 0; --i) {
        for(int j = n-1; j >= 0; --j) {
            dp[i][j] = (A[i] == B[j]) ? 1+dp[i+1][j+1] : 0;
            result = std::max(result, dp[i][j]);
        }
    }

    return result;
}

/**
 * @brief   Leetcode 718: Maximum Length of Repeated Subarray
 *  Use dynamic programming.
 *  dp[i][j] = (A[i]==B[j]) ? 1+dp[i+1][j+1] : 0;
 *  dp[i][j]: max length of common subarray start at A[i] and B[j]
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 88%
 */
int findLength3(vector<int>& A, vector<int>& B)
{
    int m = A.size();
    int n = B.size();
    vector<int> dp(n+1, 0);
    int result = 0;
    for(int i = m-1; i >= 0; --i) {
        for(int j = 0; j < n; ++j) {
            dp[j] = (A[i] == B[j]) ? 1+dp[j+1] : 0;
            result = std::max(result, dp[j]);
        }
    }

    return result;
}

/**
 * @brief   Leetcode 228: Summary Ranges
 *  Sorted array with no duplicates
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
vector<string> summaryRanges(vector<int>& nums)
{
    // if nums array is empty
    if(nums.empty()) {
        return vector<string>{};
    }
    vector<string> results;
    string str;
    int i = 0;
    str += to_string(nums[i]);
    int count = 1;
    for(i = 1; i < nums.size(); ++i) {
        if(nums[i] == nums[i-1]+1) {
            count += 1;
            continue;
        } else {
            if(count > 1) {
                str += "->";
                str += to_string(nums[i-1]);
            }
            results.push_back(str);
            str.clear();
            count = 1;
            str += to_string(nums[i]);
        }
    }
    if(count > 1 && i == nums.size()) {
        str += "->";
        str += to_string(nums[nums.size()-1]);
    }
    if(!str.empty()) results.push_back(str);

    return results;
}

/**
 * @brief   Leetcode 287: Find the Duplicate Number
 *  conditions: 1) O(1) extra space
 *              2) less than O(n^2) time complexity
 *              3) must NOT modify original array
 *              4) elements range from 1 to n with length of array is n+1
 * solutions: 1) two loops to compare every element with other elements
 *               time complexity is O(n ^2)
 *            2) sort and get duplicate number
 *               time complexity of sorting is O(nlogn)
 *            3) bit or hash set
 *               time complexity is O(n), space complexity is O(n)
 *            4) Floyd's tortoise and hare algorithm (cycle detection algorithm)
 *               time complexity is O(n), space complexity is O(1)
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99%
 */
int findDuplicate(vector<int>& nums)
{
	int tortoise = nums[0];
	int hare = nums[0];
	do {
		tortoise = nums[tortoise];
		hare = nums[nums[hare]];
	} while (tortoise != hare);

	hare = nums[0];
	while (hare != tortoise) {
		tortoise = nums[tortoise];
		hare = nums[hare];
	}

	return hare;
}

/**
 * @brief   Leetcode 287: Find the Duplicate Number
 *  Another efficient solution: use Brent's algorithm
 *
 *  lambda: the length of cycle
 *  mu:     the smallest index of the cycle, or the first index of repetition
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99%
 */
int findDuplicate2(vector<int>& nums)
{
    // get the length of cycle directly
    int power = 1;
    int lambda = 1;
    int tortoise = nums[0];
    int hare = nums[nums[0]];
    while(tortoise != hare) {
        if(power == lambda) {
            tortoise = hare;
            power *= 2;
            lambda = 0;
        }
        hare = nums[hare];
        lambda += 1;
    }

    // move forward first pointer by lambda steps
    hare = nums[0];
    for(int i = 0; i < lambda; ++i) {
        hare = nums[hare];
    }
    // get mu when nums[mu] == nums[mu+lambda]
    tortoise = nums[0];
    while(hare != tortoise) {
        hare = nums[hare];
        tortoise = nums[tortoise];
    }

    return hare;
}

/**
 * @brief   Leetcode 41: First Missing Positive
 *  Given an unsorted integer array, find the smallest missing positive integer.
 *  the solution should run in O(n) time and uses constant extra space.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
int firstMissingPositive(vector<int>& nums)
{
    int result = 1;
    sort(nums.begin(), nums.end());
    for(int i = 0; i < nums.size(); ++i) {
        // jump over negative numbers
        if(nums[i] <= 0) {
            continue;
        }
        // if exist duplicates, jump over the second and after
        if(i > 0 && nums[i] == nums[i-1]){
            continue;
        }
        if(nums[i] > result) {
            break;
        } else {
            result += 1;
        }
    }
    return result;
}

/**
 * @brief   Leetcode 41: First Missing Positive
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
int firstMissingPositive2(vector<int>& nums)
{
    // partition: left numbers are positive, the other are negative
    int numOfPositive = -1;
    for(int i = 0; i < nums.size(); ++i) {
        if(nums[i] > 0) {
            numOfPositive += 1;
            std::swap(nums[numOfPositive], nums[i]);
        }
    }
    numOfPositive += 1;

    // if nums[i] exists ranging from 1 to k, set nums[nums[i]-1] to its negative
    for(int i = 0; i < numOfPositive; ++i) {
        int temp = std::abs(nums[i]);
        if(temp <= numOfPositive) {
            nums[temp] =  (nums[temp-1] < 0) ? nums[temp-1] : (-1 * nums[temp-1]);
        }
    }

    for(int i = 0; i < numOfPositive; ++i) {
        if(nums[i] > 0) {
            return i+1;
        }
    }
    return numOfPositive+1;
}

/**
 * @brief   Leetcode 41: First Missing Position
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
int firstMissingPositive3(vector<int>& nums)
{
    // if i > 0 && i <= nums.size(), then nums[i] = i+1
    int i = 0;
    while(i < nums.size()) {
        if(nums[i] > 0 && nums[i] <= nums.size() && nums[i] != nums[nums[i]-1]) {
            // i does not increase by 1 for we need to relocate the exchanged number
            std::swap(nums[i], nums[nums[i]-1]);
        } else {
            i++;
        }
    }

    // if nums[i] != i+1, then i+1 is the missing positive
    for(int i = 0; i < nums.size(); ++i) {
        if(nums[i] != i+1) {
            return i+1;
        }
    }

    return nums.size()+1;
}

/**
 * @brief   Leetcode 229: Majority Element II
 *  The algorithm should run in linear time and in O(1) space.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 32.2%
 */
vector<int> majorityElementII(vector<int>& nums)
{
    if(nums.empty()) {
        return vector<int>{};
    }
    vector<int> result;
    int count = 1;
    const size_t limit = nums.size() / 3;
    std::sort(nums.begin(), nums.end());
    for(int i = 1; i < nums.size(); ++i) {
        if(nums[i] == nums[i-1]) {
            count += 1;
            continue;
        }
        if(count > limit) {
            result.push_back(nums[i-1]);
        }
        count = 1;
    }
    if(count > limit) {
        result.push_back(nums[nums.size()-1]);
    }

    return result;
}

/**
 * @brief   Leetcode 229: Majority Element II
 *  The algorithm should run in linear time and in O(1) space.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 87.27%
 */
vector<int> majorityElement2(vector<int>& nums)
{
    if(nums.empty()) {
        return vector<int>{};
    }

    vector<int> result;
    const size_t limit = nums.size() / 3;
    sort(nums.begin(), nums.end());
    for(int i = 0; i < nums.size(); ++i) {
        if(i+limit < nums.size() && nums[i] == nums[i+limit]) {
            if(result.empty() || (!result.empty() && result[result.size()-1] != nums[i])) {
                result.push_back(nums[i]);
            }
            i += limit;
        }
    }

    return result;
}

/**
 * @brief   Leetcode 169: Majority Element
 *  Boyer-Moore majority vote algorithm
 * 
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 97.91%
 */
int majorityElement(vector<int>& nums)
{
    int result = nums[0];
    int votes = 1;
    for(int i = 1; i < nums.size(); ++i) {
        if(nums[i] == result) {
            votes += 1;
            continue;
        }
        if(votes > 0) {
            votes -= 1;
        } else {
            result = nums[i];
            votes = 1;
        }
    }
    return result;
}

/**
 * @brief   Leetcode 229: Majority Element II
 *  The algorithm should run in linear time and in O(1) space.
 *  Boyer-Moore Majority Vote algorithm
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 99%
 */
vector<int> majorityElement3(vector<int>& nums)
{
    if (nums.empty()){
        return vector<int>{};
    }
    // get two possible candidates
    vector<int> result;
    int count1 = 0, count2 = 0;
    int candidate1 = 0, candidate2 = 1;
    for(auto& num: nums) {
        if(candidate1 == num) {
            count1 += 1;
        } else if(candidate2 == num) {
            count2 += 1;
        } else if(count1 == 0) {
            candidate1 = num;
            count1 = 1;
        } else if(count2 == 0) {
            candidate2 = num;
            count2 = 1;
        } else {
            count1 -= 1;
            count2 -= 1;
        }
    }
    // get # of candidates
    count1 = 0;
    count2 = 0;
    for(auto& num: nums) {
        if(num == candidate1) {
            count1 += 1;
        }
        if(num == candidate2) {
            count2 += 1;
        }
    }
    // judge if the candidate is correct
    if(count1 > nums.size() / 3) {
        result.push_back(candidate1);
    }
    if(count2 > nums.size() / 3) {
        result.push_back(candidate2);
    }

    return result;
}

/**
 * @brief   Leetcode 442: Find All Duplicates in an Array
 *  You should not use extra space and solve it in O(n) time.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 97.17%
 */
vector<int> findDuplicates(vector<int>& nums)
{
    if(nums.empty() || nums.size() < 2) {
        return vector<int>{};
    }
    // place value (i+1) into (i)th position
    vector<int> results;
    for(int i = 0; i < nums.size(); ++i) {
        if(nums[i] != i+1) {
            while(nums[i] != nums[nums[i]-1]) {
                std::swap(nums[i], nums[nums[i]-1]);
            }
        }
    }

    // if nums[i] != i+1, value nums[i] is duplicated and value (i+1) is lost
    for(int i = 0; i < nums.size(); ++i) {
        if(nums[i] != i+1) {
            results.push_back(nums[i]);
        }
    }

    return results;
}

/**
 * @brief   Leetcode 289: Game of Life
 *  This method use O(m*n) extra space and iterate O(8*m*n) times. 
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 100%
 */
void gameOfLife(vector<vector<int>>& board)
{
    if(board.empty() || board[0].empty()) {
        return;
    }

    size_t row = board.size();
    size_t col = board[0].size();
    vector<vector<int>> result(row, vector<int>(col, 0));
    // 8 relative positions to current position
    vector<pair<int, int>> pos = {make_pair(-1,-1), make_pair(-1, 0), make_pair(-1,1), make_pair(0, -1),
                                  make_pair( 0, 1), make_pair( 1,-1), make_pair( 1,0), make_pair(1,  1)};
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            int count = 0;
            for(int m = 0; m < pos.size(); ++m) {
                if(i+pos[m].first < row && i+pos[m].first >= 0 && j+pos[m].second >= 0 && j+pos[m].second < col)
                    count += board[i+pos[m].first][j+pos[m].second];
            }
            if(count == 3 || (count == 2 && board[i][j] == 1)) {
                result[i][j] = 1;
            }
        }
    }
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            board[i][j] = result[i][j];
        }
    }
}

/**
 * @brief   Leetcode 289: Game of Life
 *  A better solution is to solve this problem in-place, not using O(m*n) extra space.
 *
 *  The most difficult part of this solution is how to save current state and next state
 *  before reaching the end at the same time.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 97.28%
 */
void gameOfLife2(vector<vector<int>>& board)
{
    if(board.empty() || board[0].empty()) {
        return;
    }
    size_t row = board.size();
    size_t col = board[0].size();
    // 8 relative positions to current position
    vector<pair<int, int>> pos = {make_pair(-1,-1), make_pair(-1, 0), make_pair(-1,1), make_pair(0, -1),
                                  make_pair( 0, 1), make_pair( 1,-1), make_pair( 1,0), make_pair(1,  1)};
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            int count = 0;
            // calculate sum of adjacent cell value
            for(auto& move : pos) {
                int hor = i + move.first;
                int ver = j + move.second;
                if(hor >= 0 && hor < row && ver >= 0 && ver < col) {
                    count += board[hor][ver] & 1;
                }
            }
            // 1st bit is current state, 2nd bit is next state
            if(count == 3 || (count == 2 && board[i][j] == 1)) {
                board[i][j] |= 2;
            }
        }
    }
    // refresh current state of board
    for(int i = 0; i < row; ++i) {
        for(int j = 0; j < col; ++j) {
            board[i][j] >>= 1;
        }
    }
}

/**
 * @brief   Leetcode 457: Circular Array Loop
 *  1. Movements follow a single direction.
 *  2. Loop length > 1
 *
 *  Best solution can solve the problem in O(n) time complexity and O(1)
 *  extra space.
 *
 * -------------------------------------------
 * Accepted Solutions Runtime Distribution beats 36%
 */
static bool directionCheck(vector<int>& nums, int& start, int next)
{
    if(next < 0) {
        next += nums.size();
    } else if(next >= nums.size()) {
        next -= nums.size();
    }
    // single direction
    if(nums[start] * nums[next] <= 0) {
        return false;
    }
    start = next;
    return true;
}
bool circularArrayLoop(vector<int>& nums) {

    if(nums.size() < 2) {
        return false;
    }

    // !Note: this operation may lead to 0 value.
    for(int i = 0; i < nums.size(); ++i) {
        nums[i] = (nums[i] > 0) ? (nums[i] % nums.size()) : -1 * (-1 * nums[i] % nums.size());
    }
    for(int start = 0; start < nums.size(); ++start) {
        int slow = start;
        int fast = start;
        int length = 0;
        while(slow != fast || length == 0) {
            if(!directionCheck(nums, slow, slow + nums[slow])) break;
            if(!directionCheck(nums, fast, fast + nums[fast])) break;
            if(!directionCheck(nums, fast, fast + nums[fast])) break;

            length += 1;
        }
        // if lack condition slow == fast, we can not cover below case.
        // In this case, single direction check returns false, but length is greater than 1.
        // [2,2,2,2,2,4,7]
        if(slow == fast && length > 1) {
            return true;
        }
    }

    return false;
}
