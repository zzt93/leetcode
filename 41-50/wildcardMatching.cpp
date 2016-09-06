//
// Created by zzt on 9/6/16.
//

#include <iostream>
#include <fstream>

using namespace std;

class Solution {
public:
    bool isMatch(string s, string p) {
        int sz = s.size();
        int pz = p.size();
        bool match[sz + 1][pz + 1];
        match[0][0] = true;
        for (int i = 1; i < sz + 1; ++i) {
            match[i][0] = false;
        }

        {
            int j;
            for (j = 1; j < pz + 1; ++j) {
                if (p[j] == '*') {
                    match[0][j] = true;
                } else {
                    break;
                }
            }
            for (; j < pz + 1; ++j) {
                match[0][j] = false;
            }
        }

        for (int i = 0; i < sz; ++i) {
            for (int j = 0; j < pz; ++j) {
                if (s[i] == p[j] || p[j] == '?') {
                    match[i + 1][j + 1] = match[i][j];
                } else if (p[j] == '*') {
                    match[i + 1][j + 1] = match[i][j] || match[i + 1][j] || match[i][j + 1];
                } else if (s[i] != p[j]) {
                    match[i + 1][j + 1] = false;
                }
            }
        }

        return match[sz][pz];
    }
};

int main(int argc, char *argv[]) {
    ifstream in("testcase/wildcardMatching");
    string s;
    string p;
    Solution t;
    while (in >> s >> p) {
        cout << t.isMatch(s, p) << endl;
    }
    return 0;
}

