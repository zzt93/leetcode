#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>
#include <vector>

class Solution {
public:
    int searchInsert(vector<int>& n, int target) {
        int left = 0, right = n.size();
        while(left < right) {
            int mid = (left + right) / 2;
            if(n[mid] == target) {
                return mid;
            } else if (n[mid] < target) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        if(left == n.size()) {
            return left;
        }
        if(n[left] < target) {
            return left + 1;
        } else {
            return left;
        }
    }
};
