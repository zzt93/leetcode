//
// Created by zzt on 1/7/17.
//
#include <iostream>
#include <vector>
#include <set>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>> &matrix) {
        set<int> rows, cols;
        for (int j = 0; j < matrix.size(); ++j) {
            vector<int> &v = matrix[j];
            for (int k = 0; k < v.size(); ++k) {
                int &i = v[k];
                if (i == 0) {
                    rows.insert(j);
                    cols.insert(k);
                }
            }
        }
        for (int r: rows) {
            //set row to 0
        }
        for (int c: cols) {
            // set col to 0
        }
    }
};