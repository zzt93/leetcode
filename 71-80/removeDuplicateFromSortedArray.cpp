//
// Created by zzt on 1/30/17.
//

#include <iostream>
#include <vector>

static const int MAX_OCCURS = 2;
using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& n) {
        if (n.size() <= 1) {
            return n.size();
        }
        int newI = 1, oldI = 1;
        int last = n[0], count = 1;
        while (oldI < n.size()) {
            if (n[oldI] == last) {
                count++;
                if (count <= MAX_OCCURS) {
                    n[newI++] = n[oldI];
                } else {
                    // abandon this element
                }
            } else {
                count = 1;
                last = n[oldI];
                n[newI++] = n[oldI];
            }
            oldI++;
        }
        return newI;
    }
};