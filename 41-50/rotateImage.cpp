//
// Created by zzt on 9/10/16.
//
#include <vector>

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        int mid = n / 2;
        for (int i = 0; i < mid; i++) {
            for (int j = 0; j < mid; j++) {
                move(matrix, i, j);
            }
        }
        if (n % 2 == 1) {
            for (int j = 0; j < mid; j++) {
                move(matrix, mid, j);
            }
        }
    }

    void move(vector<vector<int>>& matrix, int i, int j) {
        int n = matrix.size();
        int thrX = i, thrY = j;
        int tmp = matrix[thrX][thrY];

        int fouX = n - 1 - thrY, fouY = thrX;
        matrix[thrX][thrY] = matrix[fouX][fouY];

        int firX = n - 1 - thrX, firY = fouX;
        matrix[fouX][fouY] = matrix[firX][firY];

        int secX = thrY, secY = firX;
        matrix[firX][firY] = matrix[secX][secY];

        matrix[secX][secY] = tmp;
    }
};