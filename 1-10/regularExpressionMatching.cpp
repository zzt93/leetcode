#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    void split(string &p, vector<string> &v) {
        int i;
        for (i = 0; i + 1 < p.size(); i++) {
            if (p[i + 1] == '*') {
                v.push_back(string(p, i, 2));
                i++;
            } else {
                v.push_back(string(p, i, 1));
            }
        }
        if (i < p.size()) {
            v.push_back(string(p, i, 1));
        }
    }

    bool isMatch(string s, string p) {
        vector<string> patternUnits;
        split(p, patternUnits);

        int sz = s.size();
        int pz = patternUnits.size();
        vector<vector<bool>> match(sz + 1);
        for (int i = 0; i < sz + 1; i++) {
            match[i] = vector<bool>(pz + 1);
        }

        match[0][0] = true;
        for (int i = 1; i < sz + 1; i++) {
            match[i][0] = false;
        }

        {
            int j = 1;
            for (; j < pz + 1; j++) {
                if (patternUnits[j - 1].size() == 2) { // has *
                    match[0][j] = true;
                } else {
                    break;
                }
            }

            for (; j < pz + 1; j++) {
                match[0][j] = false;
            }
        }

        for (int i = 0; i < sz; i++) {
            for (int j = 0; j < pz; j++) {
                char c = patternUnits[j][0];
                int size = patternUnits[j].size();
                if (size == 1) {
                    if (c == s[i] || c == '.') {
                        match[i + 1][j + 1] = match[i][j];
                    } else {
                        match[i + 1][j + 1] = false;
                    }
                } else if (size == 2) {
                    if (c == s[i] || c == '.') { // .*
                        match[i + 1][j + 1] = match[i][j] || match[i + 1][j] || match[i][j + 1];
                    } else { // a* and c
                        match[i + 1][j + 1] = match[i + 1][j];
                    }
                }
            }
        }

        return match[sz][pz];
    }
};

int main(int argc, char *argv[]) {
    ifstream in("testcase/regularExpressionMatching");
    string s;
    string p;
    Solution t;
    while (in >> s >> p) {
        cout << t.isMatch(s, p) << endl;
    }
    return 0;
}
