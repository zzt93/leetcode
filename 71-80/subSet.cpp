//
// Created by zzt on 1/28/17.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void subsetR(vector<vector<int>> &vv, vector<int> &n, int i) {
        if (i == n.size()) {
            vv.push_back(vector<int>());
            return;
        }
        // sub problem solution
        subsetR(vv, n, i+1);
        // induce big problem solution
        vector<vector<int>> tmp = vv;
        for (vector<int> &ve: tmp) {
           ve.push_back(n[i]);
        }
        vv.insert(vv.end(), tmp.begin(), tmp.end());
    }
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<int> empty;
        vector<vector<int>> res;
        subsetR(res, nums, 0);
        return res;
    }
};

