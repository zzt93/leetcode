//
// Created by zzt on 2/12/17.
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {

//    int divideAndConquer(vector<int> &hs, int s, int e) {
//        if (e - s == 1) {
//            return hs[s];
//        }
//        int mid = (s + e) / 2;
//        int mL = divideAndConqure(hs, s, mid);
//        int mR = divideAndConqure(hs, mid, e);
//        int mCross = -1;
//        {
//            int leftI = mid - 1;
//            int rightI = mid;
//            // index chosen O(n^2), min find O(n)
//        }
//        return 0;
//    }

    int brute(vector<int> &h, int start, unsigned long size) {
        int maxR = 0;
        for (int f = 0; f < size; ++f) {
            int minH = h[f];
            for (int s = f; s < size; ++s) {
                if (h[s] < minH) {
                    minH = h[s];
                }
                int rect = minH * (s - f + 1);
                if (rect > maxR) {
                    maxR = rect;
                }
            }
        }
        return maxR;
    }

    int divideConquer2(vector<int> &h, int s, int e) {
        if (s >= e) {
            return 0;
        }
        int minH;
        vector<int> minIndices;
        minH = h[s];
        for (int i = s; i < e; ++i) {
            if (h[i] < minH) {
                minH = h[i];
            }
        }
        for (int i = s; i < e; ++i) {
            if (h[i] == minH) {
                minIndices.push_back(i);
            }
        }
        minIndices.push_back(e);

        int maxRect = minH * (e - s);
        for (int pivot: minIndices) {
            // not include min height
            int rect = divideConquer2(h, s, pivot);
            if (rect > maxRect) {
                maxRect = rect;
            }
            s = pivot + 1;
        }
        return maxRect;
    }

    int divideConquer2_opt(vector<int> &h, int s, int e, map<int, map<int, vector<int>>> &dp) {
        if (s >= e) {
            return 0;
        }
        cout << s << " " << e << endl;
        int minH;
        vector<int> minIndices;
        if (s == 0) {
            minH = dp[0][e][0];
            minIndices.push_back(dp[0][e][1]);
        } else if (e == h.size()) {
            cout << ". ";
            minH = dp[e][s][0];
            minIndices.push_back(dp[e][s][1]);
        } else {
            minH = h[s];
            for (int i = s; i < e; ++i) {
                if (h[i] < minH) {
                    minH = h[i];
                }
            }
            for (int i = s; i < e; ++i) {
                if (h[i] == minH) {
                    minIndices.push_back(i);
                }
            }
        }
        minIndices.push_back(e);
        int maxRect = minH * (e - s);
        for (int pivot: minIndices) {
            // not include min height
            int rect = divideConquer2_opt(h, s, pivot, dp);
            if (rect > maxRect) {
                maxRect = rect;
            }
            s = pivot + 1;
        }
        return maxRect;
    }

public:

    int largestRectangleArea(vector<int> &heights) {
        map<int, map<int, vector<int>>> dp;
        map<int, vector<int>> mapS;
        int minS = heights[0], si = 0;
        for (int i = 0; i < heights.size(); ++i) {
            if (heights[i] < minS) {
                minS = heights[i];
                si = i;
            }
            mapS[i + 1] = {minS, si};
            cout << "[0," << i + 1 << "):" << minS << "@" << si << endl;
        }
        map<int, vector<int>> mapE;
        int minE = heights[heights.size() - 1], ei = heights.size() - 1;;
        for (int r = heights.size() - 1; r >= 0; --r) {
            if (heights[r] < minE) {
                minE = heights[r];
                ei = r;
            }
            mapE[r] = {minE, ei};
            cout << "[" << r << "," << heights.size() << "):" << minE << "@" << ei << endl;
        }
        dp[0] = mapS;
        dp[heights.size()] = mapE;
        return divideConquer2_opt(heights, 0, heights.size(), dp);
    }
};


int main() {
    vector<int> v = {};
    for (int i = 0; i < 10; ++i) {
        v.push_back(i);
    }
//    for (int j = 10000; j >= 0; --j) {
//        v.push_back(j);
//    }
    Solution s;
    cout << s.largestRectangleArea(v);
}