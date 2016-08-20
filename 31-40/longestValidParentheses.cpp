#include <iostream>
#include <algorithm>
#include <vector>
#include <fstream>
#include <stack>
#include <cassert>
#include <climits>

using namespace std;
using std::endl;
using std::cout;

class Solution {
public:
    int longestValidParentheses(string s) {
        stack<int> q;
        vector<int> toConnect;
        for(int i = 0; i < s.length(); i++) {
            char c = s[i];
            if(c == '(') {
                q.push(i);
            } else {
                if(!q.empty()) {
                    int leftI = q.top();
                    q.pop();
                    vector<int>::iterator low = lower_bound(toConnect.begin(), toConnect.end(), leftI);
                    toConnect.erase(low, toConnect.end());
                    toConnect.push_back(leftI);
                    toConnect.push_back(i);
                }
            }
        }
        assert((toConnect.size() & 1) == 0);
        // connect ajacent pair
        for(int i = 2; i < toConnect.size();) {
            if(toConnect[i] == toConnect[i-1] + 1) {
                toConnect.erase(toConnect.begin() + i-1, toConnect.begin() + i+1);
            } else {
                i+=2;
            }
        }
        // find max
        int max = INT_MIN;
        for(int i = 1; i < toConnect.size(); i+=2) {
            if(toConnect[i] - toConnect[i-1] > max) {
                max = toConnect[i] - toConnect[i-1] + 1;
            }
        }
        if(max == INT_MIN) {
            return 0;
        }
        return max;
    }
};

int main(int argc, char *argv[]){
	Solution s;
	string str;
	ifstream fin("testcase/longestValidParentheses");
	while(fin >> str) {
		cout << s.longestValidParentheses(str) << endl;
	}
	return 0;
}
