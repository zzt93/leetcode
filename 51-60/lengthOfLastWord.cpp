//
// Created by zzt on 9/20/16.
//

class Solution {
public:
    int lengthOfLastWord(string s) {
        int len = 0;
        bool notSpace = false;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (notSpace && s[i] == ' ') {
                return len;
            } else if (!notSpace && s[i] == ' ') {
                continue;
            } else {
                notSpace = true;
                len ++;
            }
        }
        return len;
    }
};