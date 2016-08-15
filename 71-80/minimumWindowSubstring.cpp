#include <iostream>
#include <map>
#include <deque>
#include <fstream>
#include <climits>

using namespace std;
using std::endl;
using std::cout;


class Solution {
public:
    void tryTrim(map<char, int>& inDeque, deque<int>& indices, map<char, int>& countChar, string &s) {
        char headChar = s[indices.front()];
        while(inDeque[headChar] > countChar[headChar]) {
            while(s[indices.front()] != headChar) {
                inDeque[s[indices.front()]]--;
                indices.pop_front();
            }
            inDeque[headChar]--;
            indices.pop_front();
            headChar = s[indices.front()];
        }
    }

    string minWindow(string s, string t) {
        map<char, int> countChar;
        for(char &c: t) {
            countChar[c]++;
        }
        int distinctChar = countChar.size();
        int start = 0, minLen = INT_MAX;
        int count = 0;
        deque<int> indices;
        map<char, int> inDeque;
        for(int i = 0; i < s.length(); i++) {
            char c = s[i];
            if(countChar.count(c) == 0) {
                continue;
            }

            if(inDeque[c] < countChar[c]) {
                count++;
            }
            indices.push_back(i);
            inDeque[c]++;
            if(count == t.length()) {
                tryTrim(inDeque, indices, countChar, s);
                int windowLen = indices.back() - indices.front() + 1;
                if(windowLen < minLen) {
                    minLen = windowLen;
                    start = indices.front();
                } 
            }
        }
        if(minLen == INT_MAX) {
            return "";
        }
        return s.substr(start, minLen);
    }
};

int main(int argc, char *argv[]){
	Solution s;
	ifstream infile("testcase/minimumWindowSubstring");
	string str, t;
	while(infile >> str >> t) {
	    cout << s.minWindow(str, t) << endl;
	}
	return 0;
}
