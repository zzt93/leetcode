#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>
#include <vector>

class Solution {
    map<int, string> mapping;
public:
    string countAndSay(int n) {
        if(n == 1) {
            mapping[1] = "1";
            return "1";
        }
        if(mapping.count(n)) {
            return mapping[n];
        } else {
            string now;
            string last = countAndSay(n-1);
            int count = 1;
            char lastC = last[0];
            for(int i = 1; i < last.size(); i++) {
                char c = last[i];
                if(c == lastC) {
                    count++;
                } else {
                    now = now + to_string(count) + lastC;
                    count = 1;
                    lastC = c;
                }
            }
            now = now + to_string(count) + lastC;
            mapping[n] = now;
            return now;
        }
    }
};
