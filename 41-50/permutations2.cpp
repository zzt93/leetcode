//
// Created by zzt on 9/9/16.
//

#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    vector<vector<int>> permuteUnique(vector<int>& nums) {
        vector<vector<int>> tmp;
        permute(nums, 0, nums.size(), tmp);
        return tmp;
    }

    void swap(vector<int> &v, int i, int j) {
        int t = v[i];
        v[i] = v[j];
        v[j] = t;
    }

    void permute(vector<int>& nums, int has, int aim, vector<vector<int>> & res) {
        if (has == aim) {
            res.push_back(vector<int>(nums.begin(), nums.begin() + aim));
        }
        set<int> dup;
        for(int i = has; i < nums.size(); i++) {
            if (dup.count(nums[i])) {
                continue;
            } else {
                dup.insert(nums[i]);
            }
            swap(nums, has, i);
            permute(nums, has + 1, aim, res);
            swap(nums, i, has);
        }
    }
};