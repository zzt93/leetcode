#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
    struct Less {
        bool operator()(const vector<int>& a, const vector<int>& b) {
            int minSize = a.size() < b.size() ? a.size() : b.size();
            for(int i = 0; i < minSize; i++) {
                if(a[i] < b[i]) {
                    return true;
                } else if(a[i] > b[i]) {
                    return false;
                }
            }
            return a.size() < b.size();
        }
    };
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        sort(candidates.begin(), candidates.end());
        vector<vector<int>> res;
        recursive(candidates,
            upper_bound(candidates.begin(), candidates.end(), target), target, res);
        set<vector<int>, Less> s(res.begin(), res.end());
        return vector<vector<int>> (s.begin(), s.end());;
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
        recursive(ints, upper_bound(ints.begin(), end - 1, t), t, res);   
        for(int i = nowSize; i < res.size(); i++) {
            vector<int>& tmp = res[i];
            tmp.push_back(last);
        }
        // not include 
        recursive(ints, end - 1, target, res);
    }
};
