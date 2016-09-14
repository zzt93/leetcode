//
// Created by zzt on 9/14/16.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = nums.size();
        int max = 0 + nums[0];

        for (int i = 1; i < n; i++) {
            if (i > max) {
                break;
            }
            if (nums[i] + i > max) {
                max = nums[i] + i;
            }

        }
        return max >= n - 1;
    }
};