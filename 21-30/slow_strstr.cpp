#include <iostream>

using std::endl;
using std::cout;

int main(int argc, char *argv[]){

	return 0;
}

class Solution {
public:
    int strStr(string haystack, string needle) {
        return bruteForce(haystack, needle);
    }
    
    int bruteForce(string haystack, string needle) {
        if(haystack.empty() && needle.empty()) {
            return 0;
        }
        const char *start = haystack.c_str();
        const char *need = needle.c_str();
        for(int i = 0; i < haystack.length(); i++) {
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
        return (*f - *s) == 0;
    }
};
