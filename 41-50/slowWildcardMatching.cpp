#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

class Solution {
    void initCandiMap(string s, map<char, vector<int>> &candiMap) {
        for (int i = 0; i < s.size(); i++) {
            char c = s[i];
            if (candiMap.count(c)) {
                candiMap[c].push_back(i);
            } else {
                vector<int> t;
                t.push_back(i);
                candiMap[c] = t;
            }
        }
    }

    vector<int> patternMinLen;

    void initPLen(string &p) {
        patternMinLen.clear();
        int count = 0;
        for (int i = p.size() - 1; i >= 0; i--) {
            patternMinLen.push_back(count);
            if (p[i] != '*') {
                count++;
            }
        }
        reverse(patternMinLen.begin(), patternMinLen.end());
    }

    const vector<int> empty = {};

    /*
    void split(string s, string delimiter, vector<string> &v) {
        int i = 0;
        while (delimiter.find(s[i]) != string::npos) {
            i++;
        }
        int last = i - 1;
        for (; i < s.size(); ++i) {
            if (delimiter.find(s[i]) != string::npos && i > last + 1) {
                v.push_back(string(s, last + 1, i - last - 1));
                last = i;
            } else if (delimiter.find(s[i]) != string::npos ) {
                last = i;
            }
        }
        if (i > last + 1) {
            v.push_back(string(s, last + 1, i - last - 1));
        }
    }

    bool impossibleCheck(string s, string p) {
        vector<string> v;
        split(p, "?*", v);
        unsigned long pos = 0;
        for (string &a: v) {
            pos = s.find(a, pos);
            if (pos == string::npos) {
                return true;
            }
        }
        return false;
    }
    */
public:
    bool isMatch(string s, string p) {
        map<char, vector<int>> candiMap;
        initCandiMap(s, candiMap);
        initPLen(p);
        return tryMatch(s, 0, p, 0, candiMap);
    }

    bool tryMatch(string &s, int ss, string &p, int ps, map<char, vector<int>> &candiMap) {
        int i = ss;
        int j = ps;
        while (i < s.size() && j < p.size()) {
            if (p[j] == '?' || s[i] == p[j]) {
                i++;
                j++;
            } else if (p[j] == '*') {
                // wildcard char min occupied len
                int minLen = 0;
                int cj = notWild(p, j + 1, minLen);
                //cout << minLen;
                if (cj == -1 && i + minLen <= s.size()) { // no char except */? and s is long enough
                    return true;
                }
                char c = p[cj];
                vector<int> candi = findCandiMapOpt(candiMap, i + minLen, c, s.size() - patternMinLen[cj]);
                for (int tmpi = candi.size() - 1; tmpi >= 0; tmpi--) {
                    int &ci = candi[tmpi];
                    if (tryMatch(s, ci + 1, p, cj + 1, candiMap)) {
                        return true;
                    }
                }
                return false;
            } else if (s[i] != p[j]) {
                return false;
            }
        }
        if (i != s.size()) {
            return false;
        }
        // i == s.size
        return notStar(p, j) == -1;
    }

    int notStar(string &p, int s) {
        while (s < p.size() && p[s] == '*') {
            s++;
        }
        if (s >= p.size()) {
            return -1;
        }
        return s;
    }

//    int notStarFaster(vector<int> &nonstarIndicies, int s) {
//        auto it = lower_bound(nonstarIndicies.begin(), nonstarIndicies.end(), s);
//        if (it == nonstarIndicies.end()) {
//            return -1;
//        }
//        return *it;
//    }

    int notWild(string &p, int s, int &minLen) {
        while (s < p.size() && (p[s] == '*' || p[s] == '?')) {
            if (p[s] == '?') {
                minLen++;
            }
            s++;
        }
        if (s >= p.size()) {
            return -1;
        }
        return s;
    }


//    vector<int> findCandi(string &s, int si, char aim) {
//        vector<int> res;
//        for (int i = si; i < s.size(); i++) {
//            char c = s[i];
//            if (c == aim) {
//                res.push_back(i);
//            }
//        }
//        return res;
//    }

    /**
     * find index of aim from s[si, sz)
     */
    vector<int> findCandiMapOpt(map<char, vector<int>> &c2i, int si, char aim, int maxIndex) {
        //cout << si << aim << endl;
        if (maxIndex < si) {
            return empty;
        }
        if (c2i.count(aim)) {
            vector<int> &tmp = c2i[aim];
            auto it = lower_bound(tmp.begin(), tmp.end(), si);
            if (it == tmp.end()) {
                return empty;
            }
            auto upper = lower_bound(tmp.begin(), tmp.end(), maxIndex);
            return vector<int>(it, upper);
        } else {
            return empty;
        }
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
