//
// Created by zzt on 9/29/16.
//


#include <iostream>
#include <fstream>

using namespace std;

class Solution {

    int linear(int x, int start) {
        int i;
        for (i = start; i <= x; i++) {
            int t = i * i;
            if (t > x || t < 0) {
                break;
            }
        }
        return i - 1;
    }

    int est(int x) {
        if (x < 100) {
            return linear(x, 0);
        } else {
            return 2 * est(x / 4);
        }
    }
public:
    int mySqrt(int x) {
        return linear(x, est(x));
    }
};

int main() {
    Solution s;
    ifstream in("testcase/sqrtx");
    int i;
    while (in >> i) {
        cout << i << ":" << s.mySqrt(i) << endl;
    }
}