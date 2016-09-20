//
// Created by zzt on 9/20/16.
//


#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int uniquePaths(int m, int n) {
        if (m < 1 || n < 1) {
            return 0;
        }
        vector<int> row(n);
        vector<vector<int>> v(m, row);
        for (int i = 0; i < m; i++) {
            for (int s = 0; s < n; s++) {
                if (i == 0 || s == 0) {
                    v[i][s] = 1;
                } else {
                    v[i][s] = v[i-1][s] + v[i][s-1];
                }
            }
        }
        return v[m-1][n-1];
    }
};