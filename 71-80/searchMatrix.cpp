//
// Created by zzt on 1/7/17.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    void i2RowCol(int i, int &r, int &c, int n) {
        r = i / n;
        c = i % n;
    }

public:
    bool searchMatrix(vector<vector<int>> &matrix, int target) {
        if (matrix.size() == 0) {
            return false;
        }
        int m = matrix.size(), n = matrix[0].size();
        int left = 0, right = m * n;
        while (left < right) {
            int half = (left + right) / 2;
            int r, c;
            i2RowCol(half, r, c, n);
            if (matrix[r][c] == target) {
                return true;
            } else if (matrix[r][c] < target) {
                left = half + 1;
            } else {
                right = half;
            }
        }
        return false;
    }
};