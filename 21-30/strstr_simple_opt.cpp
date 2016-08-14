#include <iostream>

class Solution {
public:
    int strStr(string haystack, string needle) {
        return bruteForce(haystack, needle);
    }
    
    int bruteForce(string haystack, string needle) {
        if(needle.empty()) {
            return 0;
        }
        const char *start = haystack.c_str();
        const char *need = needle.c_str();
        const int gap = haystack.length() - needle.length();
        for(int i = 0; i <= gap; i++) {
            const char *c1 = start + i;
            if(same(c1, need)){
                return i;
            }
        }
        return -1;
    }
    
    bool same(const char *f, const char *s) {
        while(*s != '\0' && *f == *s) {
            f++;
            s++;
        }
        if(*s == '\0') {
            return true;
        }
        return false;
    }
};
