#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>
#include <vector>

using std::endl;
using std::cout;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        return recursive(nums, 0, nums.size(), target);
    }
    
    int recursive(vector<int>& nums, int left, int right, int target) {
        if (left == right) {
            return -1;
        }
        int mid = (left + right) / 2;
        if(nums[mid] == target) {
            return mid;
        } else if(nums[left] == target) {
            return left;
        } else if(nums[right - 1] == target) {
            return right - 1;
        }
        
        if(nums[mid] > target && nums[mid] < nums[left]) { // mid in the not rotated part
            return recursive(nums, left, mid, target);
        } else if(nums[mid] > target && nums[mid] > nums[left]) { // mid in the rotated part
            if (nums[left] > target) {
                return recursive(nums, mid + 1, right, target);
            } else { 
                return recursive(nums, left, mid, target);
            }
        } else if(nums[mid] < target && nums[mid] < nums[right - 1]) {
            if (nums[right - 1] > target) {
                return recursive(nums, mid + 1, right, target);
            } else {
                return recursive(nums, left, mid, target);
            }
        } else {
            return recursive(nums, mid + 1, right, target);
        }
    }

	int recursive2(vector<int>& nums, int left, int right, int target) {
        if (left == right) {
            return -1;
        }
        int mid = (left + right) / 2;
        if(nums[mid] == target) {
            return mid;
        }
        
        if(nums[mid] > target && nums[mid] <= nums[left]) { // mid == left, size == 1
            return recursive(nums, left, mid, target);
        } else if(nums[mid] > target && nums[mid] > nums[left]) {
            if (nums[left] > target) {
                return recursive(nums, mid + 1, right, target);
            } else { // left <= target, must have left part
                return recursive(nums, left, mid, target);
            }
        } else if(nums[mid] < target && nums[mid] <= nums[right - 1]) { // mid == right, size == 2
            if (nums[right - 1] >= target) {// right >= target, must have right part
                return recursive(nums, mid + 1, right, target);
            } else { 
                return recursive(nums, left, mid, target);
            }
        } else {
            return recursive(nums, mid + 1, right, target);
        }
    }
};
