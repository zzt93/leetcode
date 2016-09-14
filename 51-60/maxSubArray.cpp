//
// Created by zzt on 9/14/16.
//

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        if (nums.size() == 0) {
            return INT_MIN;
        }
        int maxEndHere = nums[0];
        int max = nums[0];
        for(int i = 1; i < nums.size(); i++) {
            int &n = nums[i];
            if (n + maxEndHere > n) {
                maxEndHere = n + maxEndHere;
            } else {
                maxEndHere = n;
            }

            if (maxEndHere > max) {
                max = maxEndHere;
            }
        }
        return max;
    }
};