//
// Created by zzt on 2/12/17.
//

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <cassert>
#include <list>
#include <algorithm>

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

//    int brute(vector<int> &h, int start, unsigned long size) {
//        int maxR = 0;
//        for (int f = 0; f < size; ++f) {
//            int minH = h[f];
//            for (int s = f; s < size; ++s) {
//                if (h[s] < minH) {
//                    minH = h[s];
//                }
//                int rect = minH * (s - f + 1);
//                if (rect > maxR) {
//                    maxR = rect;
//                }
//            }
//        }
//        return maxR;
//    }

//    int divideConquer2(vector<int> &h, int s, int e) {
//        if (s >= e) {
//            return 0;
//        }
//        int minH;
//        vector<int> minIndices;
//        minH = h[s];
//        for (int i = s; i < e; ++i) {
//            if (h[i] < minH) {
//                minH = h[i];
//            }
//        }
//        for (int i = s; i < e; ++i) {
//            if (h[i] == minH) {
//                minIndices.push_back(i);
//            }
//        }
//        minIndices.push_back(e);
//
//        int maxRect = minH * (e - s);
//        for (int pivot: minIndices) {
//            // not include min height in next sub-problem
//            int rect = divideConquer2(h, s, pivot);
//            if (rect > maxRect) {
//                maxRect = rect;
//            }
//            s = pivot + 1;
//        }
//        return maxRect;
//    }

//    int
//    divideConquer2_opt(vector<int> &h, int s, int e, priority_queue<int, std::vector<int>, std::greater<int>> &heap) {
//        if (s >= e) {
//            return 0;
//        }
//        int minH = INT32_MAX;
//        vector<int> minIndices;
//        for (int i = s; i < e; ++i) {
//            if (h[i] < minH) {
//                minH = h[i];
//                if (heap.top() == minH) {
//                    break;
//                }
//            }
//        }
//        for (int i = s; i < e; ++i) {
//            if (h[i] == minH) {
//                minIndices.push_back(i);
//            }
//        }
//        minIndices.push_back(e);
//
//        int maxRect = minH * (e - s);
//        assert(minH == heap.top());
//        heap.pop();
//        for (int pivot: minIndices) {
//            // not include min height in next sub-problem
//            int rect = divideConquer2_opt(h, s, pivot, heap);
//            if (rect > maxRect) {
//                maxRect = rect;
//            }
//            s = pivot + 1;
//        }
//        heap.push(minH);
//        return maxRect;
//    }

//    int prepareDC2(vector<int> &heights) {
//        priority_queue<int, std::vector<int>, std::greater<int>> heap;
//        for (int &i: heights) {
//            heap.push(i);
//        }
//        return divideConquer2_opt(heights, 0, heights.size(), heap);
//    }


//    int dc3(int s, int e, priority_queue<Height *, std::vector<Height *>, pless<Height>> heap) {
//        if (s >= e) return 0;
//
//        Height *first = heap.top();
//        while (first->i < s || first->i >= e) {
//            heap.pop();
//            first = heap.top();
//        }
//        int max = first->v * (e - s);
//        assert(first->i >= s && first->i < e);
//
//        int t1 = 0, t2 = 0;
//        heap.pop();
//        t1 = dc3(s, first->i, heap);
//        t2 = dc3(first->i + 1, e, heap);
//
//        t1 = t1 > t2 ? t1 : t2;
//        return (t1 > max ? t1 : max);
//    }

//    int prepareDC3(vector<int> &hs) {
//        return dc3(0, hs.size(), prepareHeight(hs));
//    }

    template<typename Type, typename Compare = std::less<Type> >
    struct pless : public std::binary_function<Type *, Type *, bool> {
        bool operator()(const Type *x, const Type *y) const { return Compare()(*x, *y); }
    };

    struct Height {
        int v;
        int i;

        Height(int v, int i) : v(v), i(i) {}

        bool operator<(const Height &rhs) const {
            return v > rhs.v;
        }

    };

    priority_queue<Height *, vector<Height *>, pless<Height>> prepareHeight(vector<int> &hs) {
        priority_queue<Height *, std::vector<Height *>, pless<Height>> heap;
        for (int i = 0; i < hs.size(); i++) {
            int h = hs[i];
            heap.push(new Height(h, i));
        }
        return heap;
    }

    int bfs(priority_queue<Height *, std::vector<Height *>, pless<Height>> heap) {
        const int s = 0, e = heap.size();
        vector<int> endIndicies;
        endIndicies.push_back(s-1);
        endIndicies.push_back(e);
        int max = 0;
        while (!heap.empty()) {
            Height *pHeight = heap.top();

            vector<int>::iterator it = upper_bound(endIndicies.begin(), endIndicies.end(), pHeight->i);
            int rangeE = *it;
            int rangeS = *(it-1) + 1;
            assert (pHeight->i < rangeE && pHeight->i >= rangeS);
            int tmp = pHeight->v * (rangeE - rangeS);
            if (max < tmp) {
                max = tmp;
            }

            heap.pop();
            endIndicies.insert(it, pHeight->i);
        }
        return max;
    }

public:

    int largestRectangleArea(vector<int> &heights) {
        return bfs(prepareHeight(heights));
    }

};


int main() {
    vector<int> v;
//    for (int i = 0; i < 10; ++i) {
//        v.push_back(i);
//    }
    for (int j = 10000; j >= 0; --j) {
        v.push_back(1);
    }
    Solution s;
    cout << s.largestRectangleArea(v);
}