//
// Created by zzt on 9/20/16.
//


#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePathsWithObstacles(vector<vector<int>>& v) {
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
                if (v[i][s] == 0) {
                    if (i == 0 && s == 0) {
                        v[0][0] = v[0][0] == 0 ? 1 : 0;
                    } else if (i == 0) {
                        v[i][s] = v[i][s-1];
                    } else if (s == 0) {
                        v[i][s] = v[i-1][s];
                    } else {
                        v[i][s] = v[i-1][s] + v[i][s-1];
                    }
                } else {
                    v[i][s] = 0;
                }
            }
        }
        return v[m-1][n-1];
    }
};