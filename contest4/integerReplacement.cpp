//
// Created by zzt on 9/11/16.
//
#include <vector>
#include <iostream>
#include <map>

using namespace std;


class Solution {
    map<long, int> a;
public:
    int longRe(long l) {
        if (l == 1) {
            return 0;
        }
        if (a.count(l)) {
            return a[l];
        }
        int m;
        if ((l & 1) == 0) {
            m = longRe(l / 2);
        } else {
            int f = longRe(l - 1);
            int s = longRe(l + 1);
            m = f < s ? f : s;
        }
        a[l] = m + 1;
        return m + 1;
    }

    int integerReplacement(int l) {
        return longRe(l);
    }
};

int main() {
    Solution s;
    cout << s.integerReplacement(2147483647);

    for (int i = 1; i < 1000; ++i) {
        cout << i << ": " << s.integerReplacement(i) << endl;
    }
}