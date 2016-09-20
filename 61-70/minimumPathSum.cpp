//
// Created by zzt on 9/20/16.
//


#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int min(int i, int j) {
        return i < j ? i : j;
    }
public:
    int minPathSum(vector<vector<int>>& v) {
        int m = v.size();
        if (m < 1) {
            return 0;
        }
        int n = v[0].size();
        if (n < 1) {
            return 0;
        }

        for (int i = 0; i < m; i++) {
            for (int s = 0; s < n; s++) {
                if (i == 0) {
                    v[i][s] += v[i][s-1];
                } else if (s == 0) {
                    v[i][s] += v[i-1][s];
                } else {
                    v[i][s] = min(v[i-1][s] + v[i][s], v[i][s] + v[i][s-1]);
                }
            }
        }
        return v[m-1][n-1];
    }
};