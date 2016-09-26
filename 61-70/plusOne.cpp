//
// Created by zzt on 9/21/16.
//


#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> plusOne(vector<int>& digits) {
        int carry = 1;
        int n = digits.size();
        vector<int> v(n);
        for (int i = n - 1; i >= 0; i--) {
            int sum = carry + digits[i];
            v[i] = sum % 10;
            carry = sum / 10;
        }
        if (carry != 0) {
            v.insert(v.begin(), carry);
        }
        return v;
    }
};