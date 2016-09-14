//
// Created by zzt on 9/14/16.
//
#include <iostream>
#include <vector>

using namespace std;

int dir[4][2] = {
        {0,  1},
        {1,  0},
        {0,  -1},
        {-1, 0}
};

class Solution {
    enum Dir {
        RIGHT = 0,
        DOWN = 1,
        LEFT = 2,
        UP = 3
    };
public:
    vector<int> spiralOrder(vector<vector<int>> &matrix) {
        if (matrix.empty()) {
            return vector<int>();
        }
        vector<int> res(matrix[0].begin(), matrix[0].end());
        int m = matrix.size(), n = matrix[0].size();
        int sum = 0;
        int aim = m * n - n;
        int x = 1;
        int y = n - 1;
        Dir d = DOWN;
        for (int l1 = m - 1, l2 = n - 1; sum < aim; l1--, l2--) {
            if (l1 > 0) {
                pushLineAndChangeDir(res, matrix, x, y, d, l1);
                sum += l1;
            }
            if (l2 > 0) {
                pushLineAndChangeDir(res, matrix, x, y, d, l2);
                sum += l2;
            }
        }
        return res;
    }

    void pushLineAndChangeDir(vector<int> &res, vector<vector<int>> &m, int &x, int &y, Dir &d, int len) {
        res.push_back(m[x][y]);
        int c = 1;
        while (c < len) {
            x += dir[d][0];
            y += dir[d][1];
            //cout << x << " " << y << endl;
            res.push_back(m[x][y]);
            c++;
        }
        d = static_cast<Dir>((d + 1) % 4);
        x += dir[d][0];
        y += dir[d][1];
    }
};