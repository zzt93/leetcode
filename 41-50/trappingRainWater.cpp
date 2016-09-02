#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>
#include <vector>
#include <stack>
#include <map>
#include <cstdlib>
#include <fstream>

#include <string>
#include <sstream>

using namespace std;

class Solution {
public:
	int subSum(vector<int>& height, int sI, int eI, int minH) {
		int sum = 0;
		for(int i = sI + 1; i < eI; i++) {
			if (height[i] > minH) {
				break;
			}
			sum += (minH - height[i]);
		}
		return sum;
	}

	int collect(int sI, int endI, vector<int>& height) {
		int endH = height[endI];
		int startH = height[sI];
		int minH = startH < endH ? startH : endH;
		return subSum(height, sI, endI, minH);
	}

    int trap(vector<int>& height) {	
		if(height.size() < 2) {
            return 0;
        }
		map<int, vector<int>> heightToIndex;
		for(int i = 0; i < height.size(); i++) {
			int h = height[i];
			if(heightToIndex.count(h)) {
				vector<int>& v = heightToIndex[h];
				v.push_back(i);
			} else {
				vector<int> v;
				v.push_back(i);
				heightToIndex[h] = v;
			}
		}	

		vector<int> indicies;
		assert(height.size() > 2);
		int nowI = 0, nextI = 1;
		for(; nextI < height.size(); nowI++, nextI++) {
			int now = height[nowI], next = height[nextI];
			if (now > next) {
				indicies.push_back(nowI);
			} else if (now < next) { // find an end
				int sI = findStartSimple(height, next, nextI);
				if (sI != -1 && sI != nowI) {
					auto it = lower_bound(indicies.begin(), indicies.end(), sI);
					assert(*it == sI);
					indicies.erase(it + 1, indicies.end());
					indicies.push_back(nextI);
				}
			}
		}

		int rain = 0;
		for(int i = 0; i + 1< indicies.size(); i++) {
			int start = indicies[i];
			int end = indicies[i + 1];
			rain += collect(start, end, height);
		}
		return rain;
    }

	int findStartSimple(vector<int>& height, int h, int i) {
		int max = 0;
		int mI = -1;
		for(int j = i - 1; j >= 0; j--) {
			if(height[j] >= h) {
				return j;
			}
			if(max < height[j]) {
				max = height[j];
				mI = j;
			}
		}
		if(mI == i - 1) {
			mI = -1;
		}
		return mI;
	}

	// @Deprecated: wrong version
	int findStart(map<int, vector<int>>& h2i, int h, int i) {
		assert(h > 0);
		// try to find larger one first
		auto upper = h2i.lower_bound(h);
		auto tmp = upper;
		auto sameOrLess = --tmp;
		while(upper != h2i.end()) {
			vector<int>& larger = upper->second;
			// find a larger one that before it
			auto index = lower_bound(larger.begin(), larger.end(), i);
			if (index != larger.begin()) {
				return *(index - 1);
			}
			upper++;
		}

		while(sameOrLess != h2i.begin()) {
			vector<int>& smaller = sameOrLess->second;
			auto index = lower_bound(smaller.begin(), smaller.end(), i);
			if (index != smaller.begin()) {
				return *(index - 1);
			}
			sameOrLess--;
		}
		return -1;
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
	string str;
	ifstream infile("testcase/trappingRainWater");
	while(infile >> str) {
		vector<int> v;
		split(str, ',', v);
		cout << s.trap(v) << endl;
	}
	return 0;
}
