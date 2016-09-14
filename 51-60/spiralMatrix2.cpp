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
    vector<vector<int>> generateMatrix(int n) {
        vector<int> v(n);
        vector<vector<int>> vv(n, v);

        int i;
        for (i = 0; i < n; i++) {
            vv[0][i] = i + 1;
        }
        i++;

        int x = 1, y = n - 1;
        Dir d = DOWN;
        for (int l = n - 1; l > 0; l--) {
            setValueAndChangeDir(vv, x, y, d, l, i);
            setValueAndChangeDir(vv, x, y, d, l, i);
        }
        return vv;
    }

    void setValueAndChangeDir(vector<vector<int>> &m, int &x, int &y, Dir &d, int len, int &i) {
        m[x][y] = i++;
        int c = 1;
        while (c < len) {
            x += dir[d][0];
            y += dir[d][1];
            //cout << x << " " << y << endl;
            m[x][y] = i++;
            c++;
        }
        d = static_cast<Dir>((d + 1) % 4);
        x += dir[d][0];
        y += dir[d][1];
    }
};