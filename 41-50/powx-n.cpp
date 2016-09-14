#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    double myPow(double x, int n) {
        if (n == 1) {
            return x;
        } else if (n == 0) {
            return 1;
        } else if (n == -1) {
            return 1 / x;
        }
        
        double t = myPow(x, n / 2);
        if ((n & 1) == 0) {
            return t * t;
        } else {
            return t * t * (n < 0 ? 1/x : x);
        }
    }
};
