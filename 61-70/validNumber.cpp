//
// Created by zzt on 9/21/16.
//


#include <iostream>
#include <algorithm>

using namespace std;

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
                                    std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
                         std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}

class Solution {
    // not allow empty string
    bool isNum(string s, int i) {
        bool res = false;
        for (; i < s.size(); i++) {
            if (s[i] > '9' || s[i] < '0') {
                return false;
            } else {
                res = true;
            }
        }
        return res;
    }
    bool isInt(string s) {
        //cout << ".";
        int i = 0;
        if (s[0] == '+' || s[0] == '-') {
            i++;
        }
        return isNum(s, i);
        //return regex_match(s, std::regex("[-+]*[0-9]+"));
    }

    bool isDouble(string s) {
        //cout << s << regex_match(s, std::regex("[0-9]*\\.[0-9]+"));
        //return regex_match(s, std::regex("[-+]*([0-9]*\\.[0-9]+|[0-9]+\\.[0-9]*)"));
        //|| regex_match(s, std::regex("[-+]*"));
        int i;
        int n = s.size();
        for (i = 0; i < n; i++) {
            if (s[i] == '.') {
                break;
            }
        }
        if (i == n) {
            return false;
        }
        cout << i;
        string f(s, 0, i);
        string sec(s, i+1, n-i-1);
        if (i == n-1) {
            return isInt(f);
        } else if (i == 0) {
            return isNum(sec, 0);
        }
        return (isInt(f) || f == "-" || f == "+") && isNum(sec, 0);
    }


    bool isSci(string s) {
        int i;
        int n = s.size();
        for (i = 0; i < n; i++) {
            if (s[i] == 'e') {
                break;
            }
        }
        if (i == n) {
            return false;
        }
        //cout << i;
        string f(s, 0, i);
        string sec(s, i+1, n-i-1);
        return (isInt(f) || isDouble(f)) && isInt(sec);
    }
public:
    bool isNumber(string s) {
        string str = trim(s);
        return isInt(s) || isDouble(s) || isSci(s);
    }
};