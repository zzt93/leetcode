//
// Created by zzt on 1/25/17.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    void combineR(vector<vector<int>> &vv, int n, int k, vector<int> &v, int startI, int len) {
        if (k == len) {
            vv.push_back(v);
            return;
        } else if (startI == n) {
            return;
        }
        // not choose this one
        combineR(vv, n, k, v, startI + 1, len);
        // choose this one
        v[len] = startI + 1;
        combineR(vv, n, k, v, startI + 1, len+1);
    }

    vector<vector<int>> combine(int n, int k) {
        vector<vector<int>> vv;
        vector<int> v(k);
        combineR(vv, n, k, v, 0, 0);
        return vv;
    }
};