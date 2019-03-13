/**
 * @file	array.cpp
 * @brief	All functions are solutions of leetcode problems.
 *
 * @author	Changrui
 * @date	2018/12/8
 *
 * Copyright © 2018 ChangruiShao. All rights reserved.
 */

#include "array.hpp"

#include <algorithm>
#include <deque>
#include <unordered_map>
#include <map>
#include <unordered_set>

using std::swap;
using std::sort;
using std::reverse;
using std::deque;
using std::unordered_map;
using std::multimap;
using std::map;
using std::unordered_set;

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
 * @brief   Leetcode 39: Combination Sum
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
    // start number determines whether we can same number repeatedly
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
 *  Using Dynamic programming algorithm.
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
 *  Using Backtracking algorithm
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
    int right = (int)nums.size() - 1;

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
    int right = (int)nums.size() - 1;
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
    int right = (int)nums.size() - 1;
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
    int length = (int)height.size();
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
	int j = (int)height.size() - 1;
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
        return (int)nums.size();
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

    return (int)nums.size();
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
        return (int)nums.size();
    }

    for(int i = 1; i < nums.size(); ++i) {
        if(i < nums.size() && nums[i] == nums[i-1]) {
            nums.erase(nums.begin() + i);
            i -= 1;
        }
    }
    return (int)nums.size();
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
        return (int)nums.size();
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

    return (dupFlag == -1) ? (int)nums.size() : dupFlag;
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
        return (int)nums.size();
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

    return (dupFlag == -1) ? (int)nums.size() : dupFlag;
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
    int N = (int)matrix[0].size();
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
    int R = (int)matrix.size();  // line number
    int C = (int)matrix[0].size();  // column number

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
    int R = (int)matrix.size();
    if(R == 0) return results;

    int C = (int)matrix[0].size();
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

	int N = (int)nums.size();
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

    int N = (int)nums.size();
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

    int N = (int)nums.size();
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
    int N = (int)nums.size();
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
    int N = (int)intervals.size();
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
    long int result = 1;
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
    int row = obstacleGrid.size();
    int col = obstacleGrid[0].size();

    vector<vector<long int>> dp(row, vector<long int>(col, 0));
    for(int i = 0; i < row; ++i) {
        if(obstacleGrid[i][0] == 0)
            dp[i][0] =1;
        else
            break;
    }
    for(int j = 0; j < col; ++j) {
        if(obstacleGrid[0][j] == 0)
            dp[0][j] = 1;
        else
            break;
    }
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
