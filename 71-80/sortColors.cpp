//
// Created by zzt on 1/15/17.
//

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
    void swap(vector<int> &n, int f, int s) {
        int t = n[f];
        n[f] = n[s];
        n[s] = t;
    }

public:
    void sortColors(vector<int> &n) {
        int m = 0, s = 0, e = n.size() - 1;
        /*
         * invariant:
         * 0 [0, m)
         * 1 [m, s)
         * unknown [s, e+1)
         * 2 [e+1, size)
         */
        while (s < e + 1) {
            if (n[s] == 0) {
                swap(n, s, m);
                s++;
                m++;
            } else if (n[s] == 1) {
                s++;
            } else {
                assert(n[s] == 2);
                while (s < e + 1 && n[e] == 2) {
                    e--;
                }
                if (s < e + 1) {
                    if (n[e] == 1) {
                        swap(n, s, e);
                        s++;
                        e--;
                    } else {
                        assert(n[e] == 0);
                        swap(n, s, e);
                        e--;
                    }
                } else {
                    break;
                }
            }
        }
    }
};