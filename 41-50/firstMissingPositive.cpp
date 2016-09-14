#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        set<int> s(nums.begin(), nums.end());
        // remove duplicate and sort
        vector<int> tmp(s.begin(), s.end());
        vector<int>::iterator upper = upper_bound(tmp.begin(), tmp.end(), 0);
        int i = 1;
        while(upper != tmp.end() && i == *upper) {
            i++;
            upper++;
        }
        return i;
    }
};
