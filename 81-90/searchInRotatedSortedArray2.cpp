#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>

using std::endl;
using std::cout;

/*
	run time O(n) in worst case, no better than linear search
*/
class Solution {
public:
    bool search(vector<int>& nums, int target) {
        return recursive(nums, 0, nums.size(), target);
    }
    
    bool recursive(vector<int>& nums, int left, int right, int target) {
        if (left == right) {
            return false;
        }
        int mid = (left + right) / 2;
        if(nums[mid] == target) {
            return true;
        } 
        return recursive(nums, left, mid, target) | recursive(nums, mid + 1, right, target);
    }
};
