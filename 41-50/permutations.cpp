#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> res;
        permute(nums, 0, nums.size(), res);
        return res;
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

