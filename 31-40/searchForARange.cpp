#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>
#include <vector>

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        vector<int> res;
        res.push_back(search(nums, target, true));
        res.push_back(search(nums, target, false));
        return res;
    }
    
    int search(vector<int>& n, int t, bool firstOrLast) {
        int left = 0, right = n.size();
        int aim = -1;
        while(left < right) {
            int mid = (left + right) / 2;
            if(n[mid] == t) {
                aim = mid;
                if(firstOrLast) {
                    right = mid;
                } else {
                    left = mid + 1;
                }
            } else if (n[mid] > t) {
                right = mid;
            } else {
                left = mid + 1;
            }
        }
        return aim;
    }
};
