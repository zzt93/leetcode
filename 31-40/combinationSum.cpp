#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>
#include <vector>

#include <string>
#include <sstream>
#include <cstdlib>

using namespace std;

class Solution {
public:
    vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        recursive(candidates,
            upper_bound(candidates.begin(), candidates.end(), target), target, res);
        return res;
    }
    
    void recursive(vector<int>& ints, vector<int>::iterator end, 
          int target, vector<vector<int>>& res) {
        if(target == 0) {
            vector<int> candi;
            res.push_back(candi);
			return;
        } else if (target < 0 || end == ints.begin()) {
            return;
        } 
        // include last one
        int last = *(end - 1);
        int t = target - last;
        int nowSize = res.size();
        recursive(ints, upper_bound(ints.begin(), end, t), t, res);   
        for(int i = nowSize; i < res.size(); i++) {
            vector<int>& tmp = res[i];
            tmp.push_back(last);
        }
        // not include 
        recursive(ints, end - 1, target, res);
    }
};

void split(const string &s, char delim, vector<int> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(atoi(item.c_str()));
    }
}

int main(int argc, char *argv[]){
	Solution s;
	ifstream in("testcase/combinationSum");
	string str;
	while(getline(in, str)) {
		str.erase(str.begin());
		str.pop_back();
		vector<int> ints;
		split(str, ',', ints);
		getline(in, str);
		s.combinationSum(ints, atoi(str.c_str()));
	}
	return 0;
}
