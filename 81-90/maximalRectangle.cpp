//
// Created by zzt on 2/19/17.
//

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;


class Solution {
    /**
     * largest rect in [1, 1] can't induce the largest in [0, 0]
     */
//    vector<int> recur(vector<vector<char>> &m, vector<vector<vector<int>>> &dp, int i, int x, vector<vector<int>> &rowZ,
//              vector<vector<int>> &colZ) {
//        if (m[i][x] == '0') {
//            return {0, 0};
//        }
//        if (dp[i][x][0] != 0) {
//            return dp[i][x];
//        }
//        vector<int> &row = rowZ[i], &col = colZ[x];
//        int rowL = m[0].size(), colL = m.size();
//        vector<int>::iterator rFirstZero = upper_bound(row.begin(), row.end(), x),
//                cFirstZero = upper_bound(col.begin(), col.end(), i);
//        int rfz = rFirstZero == row.end() ? rowL : *rFirstZero,
//                cfz = cFirstZero == col.end() ? colL : *cFirstZero;
//        int rl = rfz - x, cl = cfz - i;
//        int innerRl = rl, innerCl = cl;
//        assert(rl >= 1 && cl >= 1);
//        if (rl > 1 && cl > 1) {
//            vector<int> sub = recur(m, dp, i + 1, x + 1, rowZ, colZ);
//            if (sub[0] < rl -1) {
//                innerRl = sub[0] + 1;
//            }
//            if (sub[1] < cl - 1) {
//                innerCl = sub[1] + 1;
//            }
//        }
//        int inner = innerCl * innerRl;
//        int rowSpace = 1 * rl;
//        int colSpace = 1 * cl;
//
//        if (inner >= rowSpace && inner >= colSpace) {
//            rl = innerRl;
//            cl = innerCl;
//        } else if (rowSpace >= inner && rowSpace >= colSpace) {
//            cl = 1;
//        } else {
//            rl = 1;
//        }
//        dp[i][x][0] = rl;
//        dp[i][x][1] = cl;
//        return {rl, cl};
//    }

    vector<int>
    recur2(vector<vector<char>> &m, int i, int x, vector<vector<int>> rowZ, vector<vector<int>> colZ, int depth, int er,
               int ec) {
        if (er == 1 || ec == 1) {
        }
    }
public:

    int maximalRectangle(vector<vector<char>> &matrix) {
        if (matrix.size() == 0) {
            return 0;
        }
        int cc = matrix.size();
        int rc = matrix[0].size();
//        vector<int> rowAndCol(2, 0);
//        vector<vector<vector<int>>> dp(cc, vector<vector<int>>(rc, rowAndCol));
        vector<vector<int>> rowZ(cc, vector<int>());
        vector<vector<int>> colZ(rc, vector<int>());
        for (int i = 0; i < matrix.size(); ++i) {
            for (int x = 0; x < matrix[0].size(); ++x) {
                if (matrix[i][x] == '0') {
                    rowZ[i].push_back(x);
                    colZ[x].push_back(i);
                }
            }
        }
        int max = 0;
        for (int i = 0; i < matrix.size(); ++i) {
            for (int x = 0; x < matrix[0].size(); ++x) {
                int er = rc - i;
                int ec = cc - x;
                vector<int> tmp = recur2(matrix, i, x, rowZ, colZ, 0, er, ec);
                if (tmp[0] * tmp[1] > max) {
                    max = tmp[0] * tmp[1];
                }
            }
        }
        return max;
    }
};

vector<vector<char>> input(int i, int i1);

vector<vector<char>> input(int x, int y) {
    vector<vector<char>> res(x, vector<char>(y)) ;
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            res[i][j] = '0' + ((1+i) * (3+j)) % 3 == 0;
        }
    }
    return res;
}


int main() {
    Solution s;
    vector<vector<char>> matrix = {
            {'1','0','1','0','0'},
            {'1','0','1','1','1'},
            {'1','1','1','1','1'},
            {'1','0','0','1','0'},
    };
    cout << s.maximalRectangle(matrix);
    return 0;
}
