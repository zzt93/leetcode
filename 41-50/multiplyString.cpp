#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>
#include <list>

using namespace std;

class Solution {
public:
    list<int> mul(int n, string num1, int i) {
        list<int> res;
        int carry = 0;
        for(int i = num1.size() - 1; i >= 0; i--) {
            char c = num1[i];
            int n0 = c - '0';
            int tmp = n * n0 + carry;
            carry = tmp / 10;
            res.push_back(tmp % 10);
        }
        if(carry != 0) {
            res.push_back(carry);
        }
        int count = 0;
        while(i > count) {
            count++;
            res.push_front(0);
        }
        return res;
    }
    string multiply(string num1, string num2) {
		// to handle strange and inconsistent test case
		/*
		"0"
		"9133"
		--> "0"
		*/
		if(num1.size() == 1 && num1[0] == '0') {
            return "0";
        }
        if(num2.size() == 1 && num2[0] == '0') {
            return "0";
        }

        int s2 = num2.size();
        list<list<int>> toSum(s2);
        for(int i = 0; i < s2; i++) {
            int n = num2[i] - '0';
            list<int> res = mul(n, num1, s2 - 1 - i);
            toSum.push_back(res);
        }
        list<char> chars;
        int i = 0;
        int carry = 0;
        while(!toSum.empty()) {
            int colSum = carry;
            list<list<int>>::iterator it = toSum.begin();
            while(it != toSum.end()) {
                list<int> &l = *it;
                if(l.empty()) {
                    it = toSum.erase(it);
                } else {
                    colSum += l.front();
                    l.pop_front();
					if (l.empty()) {
						it = toSum.erase(it);
					} else {
	                    it++;
					}
                }
            }
            carry = colSum / 10;
            int col = colSum % 10;
            chars.push_front((char)(col + '0'));
        }
        if(carry != 0) {
            chars.push_front((char)(carry + '0'));
        }
        return string(chars.begin(), chars.end());
    }
};

int main(int argc, char *argv[]){
	Solution s;
	cout << s.multiply("1", "1");
	return 0;
}
