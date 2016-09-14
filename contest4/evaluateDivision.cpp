//
// Created by zzt on 9/12/16.
//
#include <map>
#include <vector>
#include <cassert>
#include <set>

using namespace std;

class Solution {
    struct equation {
        string a;
        string b;
        double d;

        equation(string &a, string &b, double e) {
            this->a = a;
            this->b = b;
            d = e;
        }

        bool contain(string &s) {
            return s == a || s == b;
        }

        bool isFirst(string &s) {
            return s == a;
        }

        string other(string &s) {
            if (s == a) {
                return b;
            }
            assert(s == b);
            return a;
        }

        bool operator<(const equation &rhs) const {
            if (a < rhs.a)
                return true;
            if (rhs.a < a)
                return false;
            return b < rhs.b;
        }
    };

public:
    vector<double>
    calcEquation(vector<pair<string, string>> equations, vector<double> &values, vector<pair<string, string>> query) {

        multimap<string, equation> vars;
        auto it = values.begin();
        for (auto &p: equations) {
            equation e(p.first, p.second, *it);
            vars.insert(pair<string, equation>(p.first, e));
            vars.insert(pair<string, equation>(p.second, e));
            it++;
        }

        vector<double> res;
        for (auto &p: query) {
            set<equation> s;
            res.push_back(calc(p.first, p.second, vars, s));
        }
        return res;
    }

    double calc(string f, string s, multimap<string, equation> vars, set<equation> met) {
        if (!vars.count(f) || !vars.count(s)) {
            return -1.0;
        } else if (f == s) {
            return 1.0;
        } else {
            for (auto it = vars.equal_range(s).first; it != vars.equal_range(s).second; ++it) {
                equation &e = it->second;
                if (e.contain(f)) {
                    return e.isFirst(f) ? e.d : 1 / e.d;
                }
            }
            for (auto it = vars.equal_range(s).first; it != vars.equal_range(s).second; ++it) {
                equation &e = it->second;
                if (met.count(e)) {
                    continue;
                } else {
                    met.insert(e);
                }
                string other = e.other(s);
                double t = calc(f, other, vars, met);
                if (t != -1.0) {
                    if (!e.isFirst(s)) {
                        t *= e.d;
                    } else {
                        t /= e.d;
                    }
                    return t;
                }
            }
            return -1.0;
        }
    }
};