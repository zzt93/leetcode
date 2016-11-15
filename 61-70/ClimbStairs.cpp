//
// Created by zzt on 11/15/16.
//


#include <iostream>

using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        if (n == 0) {
            return 1;
        }
        long *dp = new long[n+1];
        dp[0] = 1;
        dp[1] = 1;
        for (int i = 2; i < n+1; i++) {
            dp[i] = dp[i - 1] + dp[i - 2];
        }
        return (int)dp[n];
    }
};