#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include <map>

using namespace std;

class Solution {
public:
    int jump(vector<int> &nums) {
        unsigned long sz = nums.size();
        int minJump[sz];

        minJump[0] = 0;
        for (int i = 1; i < sz; i++) {
            minJump[i] = INT_MAX;
        }
        for (int i = 0; i < sz; i++) {
            int maxI = nums[i] + i;
            int newJump = minJump[i] + 1;
            if (maxI >= sz - 1) {
                return newJump;
            }
            for (int j = i + 1; j <= maxI && j < sz; j++) {
                if (newJump < minJump[j]) {
                    minJump[j] = newJump;
                }
            }
        }

        return minJump[sz - 1];
    }

    int jump2(vector<int> &nums) {
        unsigned long sz = nums.size();
        if (sz == 1) {
            return 0;
        }

        map<int, int> index2jump;
        int maxI = 0;
        index2jump[maxI] = 0;
        for (int i = 0; i < sz; ++i) {
            int nowMaxI = nums[i] + i;
            if (nowMaxI > maxI) {
                maxI = nowMaxI;
                int jump = index2jump.lower_bound(i)->second;
                index2jump[maxI] = jump + 1;
                if (maxI >= sz - 1) {
                    return jump + 1;
                }
            }
        }
        assert(false);
        return 0;
    }
};

void split(const string &s, char delim, vector<int> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(atoi(item.c_str()));
    }
}

int main(int argc, char *argv[]) {
    Solution s;
    ifstream in("testcase/jumpGame2");
    string line;
    while (in >> line) {
        vector<int> v;
        split(line, ',', v);
        cout << s.jump2(v) << endl;
    }
    return 0;
}
