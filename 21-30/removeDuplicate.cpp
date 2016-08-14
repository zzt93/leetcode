#include <iostream>


class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if(nums.empty()) {
            return 0;
        }
        int len = 1;
        int now = nums[0];
        for(int i = 1; i < nums.size(); i++) {
            if(nums[i] > now) {
                nums[len] = nums[i];
                len++;
                now = nums[i];
            }
        }
        return len;
    }
};
