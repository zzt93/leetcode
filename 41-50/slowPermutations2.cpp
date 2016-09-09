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
    struct Less {
        bool operator()(const vector<int> &v, const vector<int> &n) {
            for(int i = 0; i < v.size(); i++) {
                if(v[i] < n[i]) {
                    return true;
                } else if (v[i] > n[i]){
                    return false;
                }
            }
            return false;
        }
    };
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> tmp;
        permute(nums, 0, nums.size(), tmp);
        set<vector<int>, Less> s(tmp.begin(), tmp.end());
        return vector<vector<int>> (s.begin(), s.end());
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
        for(int i = has; i < nums.size(); i++) {
            swap(nums, has, i);
            permute(nums, has + 1, aim, res);
            swap(nums, i, has);
        }
    }
};
