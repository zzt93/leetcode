//
// Created by zzt on 11/21/16.
//

#include <iostream>
#include <vector>

using namespace std;

class Solution {
    int lcs(string s1, string s2) {
        vector<int> tmp(s2.size() + 1);
        vector<vector<int>> dp(s1.size() + 1, tmp);
        for (int i = 0; i <= s2.size(); i++) {
            dp[0][i] = 0;
        }
        for (int i = 0; i <= s1.size(); i++) {
            dp[i][0] = 0;
        }

        for (int i = 1; i <= s1.size(); i++ ) {
            for (int j = 1; j <= s2.size(); j++) {
                if (s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1] + 1;
                } else {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        return dp[s1.size()][s2.size()];
    }
public:
    int minDistance2(string word1, string word2) {
        int len = lcs(word1, word2);
        int add = word2.size() - len;
        int del = word1.size() - len;
        if (add == 0) {
            return del;
        } else if (del == 0) {
            return add;
        } else {
            // Fail to deal with this case
            return -1;
        }
    }

    int minDistance(string s1, string s2) {
        vector<int> tmp(s2.size() + 1);
        vector<vector<int>> dp(s1.size() + 1, tmp);
        for (int i = 0; i <= s2.size(); i++) {
            dp[0][i] = i;
        }
        for (int i = 0; i <= s1.size(); i++) {
            dp[i][0] = i;
        }
        for (int i = 1; i <= s1.size(); i++ ) {
            for (int j = 1; j <= s2.size(); j++) {
                if (s1[i-1] == s2[j-1]) {
                    dp[i][j] = dp[i-1][j-1];
                } else {
                    dp[i][j] = min(dp[i-1][j-1], min(dp[i-1][j], dp[i][j-1])) + 1;
                }
            }
        }
        return dp[s1.size()][s2.size()];
    }
};