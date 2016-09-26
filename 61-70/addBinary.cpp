//
// Created by zzt on 9/21/16.
//


#include <iostream>
#include <list>

using namespace std;

class Solution {
public:
    string addBinary(string a, string b) {
        int as = a.size();
        int bs = b.size();
        list<char> l;
        int carry = 0;
        for (int i = as - 1, j = bs - 1; i >= 0 || j >= 0; i--, j--) {
            int sum = carry;
            if (i >= 0) {
                sum += (a[i] - '0');
            }
            if (j >= 0) {
                sum += (b[j] - '0');
            }
            carry = sum / 2;
            cout << sum;
            l.push_front((char)(sum % 2 + '0'));
        }
        if (carry != 0) {
            l.push_front((char)(carry + '0'));
        }
        return string(l.begin(), l.end());
    }
};