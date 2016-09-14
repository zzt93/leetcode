//
// Created by zzt on 9/10/16.
//
#include <map>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
    struct gram {
        string s;
        long code;
        map<char, int> count;

        gram(string &s) {
            this->s = s;
            code = compute(s);
        }

        long compute(string &s) {
            long res = 0;
            for (char &c: s) {
                res += c;
                count[c]++;
            }
            return res;
        }

        bool operator<(const gram &rhs) const {
            if (code < rhs.code)
                return true;
            if (rhs.code < code)
                return false;
            auto e = count.begin();
            auto e2 = rhs.count.begin();
            for (; e != count.end() && e2 != rhs.count.end(); e++, e2++) {
                if (e->first < e2->first) {
                    return true;
                } else if (e->first > e2->first) {
                    return false;
                } else { // char is same, compare times
                    if (e->second < e2->second) {
                        return true;
                    } else if (e->second > e2->second) {
                        return false;
                    }
                }
            }
            // they are equal
            return false;
        }
    };

public:
    vector<vector<string>> groupAnagrams(vector<string> &strs) {
        map<gram, vector<string>> map;
        for (string &s: strs) {
            gram t(s);
            if (map.count(t)) {
                map[t].push_back(s);
            } else {
                vector<string> v;
                v.push_back(s);
                map[t] = v;
            }
        }
        vector<vector<string>> res;
        for (auto &e: map) {
            res.push_back(e.second);
        }
        return res;
    }
};