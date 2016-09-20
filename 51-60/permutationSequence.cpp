//
// Created by zzt on 9/20/16.
//


#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
    char itoc(int i) {
        return (char)('0' + i);
    }
public:
    string getPermutation(int n, int k) {
        vector<int> v(n);
        int per = 1;
        for(int i = 0; i < n; i++) {
            v[i] = i + 1;
            per *= (i + 1);
        }
        char *tmp = new char[n + 1];
        tmp[n] = '\0';
        // make it zero-based
        recursive(tmp, v, k - 1, per);
        return string(tmp);
    }

    void recursive(char *res, vector<int> &v, int k, int perN) {
        assert(perN >= k);
        int n = v.size();
        if (k == 0) {
            for (int i = 0; i < n; i++) {
                res[i] = itoc(v[i]);
            }
            return;
        }

        int perN_1 = perN / n;
        int ordinal = k / perN_1;
        int aim = v[ordinal];
        cout << perN_1 << ordinal << aim << endl;
        v.erase(v.begin() + ordinal);
        recursive(res + 1, v, k % perN_1, perN_1);
        res[0] = itoc(aim);
    }
};