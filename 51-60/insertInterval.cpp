//
// Created by zzt on 9/19/16.
//
#include <cassert>

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Interval {
    int start;
    int end;

    Interval() : start(0), end(0) {}

    Interval(int s, int e) : start(s), end(e) {}
};

class Solution {
    bool isEnd(int i, Interval &in) {
        return in.end == i;
    }
public:
    vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
        map<int, Interval> i2i;
        set<int> dup;
        for (Interval &in: intervals) {
            if (in.start == in.end) {
                dup.insert(in.start);
                continue;
            }
            i2i[in.start] = in;
            i2i[in.end] = in;
        }


        vector<Interval> res;
        Interval &in  = newInterval;
        if (in.start < in.end) {
            auto s = i2i.lower_bound(in.start);
            auto e = i2i.lower_bound(in.end);
            int mergedS, mergedE;
            if (s == i2i.end()) {
                assert(e == i2i.end());
                mergedS = in.start;
                mergedE = in.end;
            } else {
                map<int, Interval>::iterator start, end;
                if (isEnd(s->first, s->second)) {
                    assert(s != i2i.end());
                    start = --s;
                    mergedS = start->first;
                } else {
                    start = s;
                    mergedS = in.start;
                }

                if (e == i2i.end()) {
                    end = e;
                    mergedE = in.end;
                } else {
                    if (isEnd(e->first, e->second)) {
                        end = e;
                        mergedE = e->first;
                    } else if (in.end == e->first) {
                        assert(e != i2i.end());
                        end = ++e;
                        mergedE = e->first;
                    } else { // in the middle of two interval
                        //cout << "." << endl;
                        if (e != i2i.begin()) {
                            end = --e;
                        } else {
                            end = e;
                        }
                        mergedE = in.end;
                    }
                    if (start != end) {
                        assert(end != i2i.end());
                        end++;
                    }
                }
                i2i.erase(start, end);
            }
            Interval newIn(mergedS, mergedE);
            i2i[mergedS] = newIn;
            i2i[mergedE] = newIn;
        } else if (in.start == in.end) {
            dup.insert(in.start);
        }

        for (int i: dup) {
            auto it = i2i.lower_bound(i);
            if (it == i2i.end() ||
                (!isEnd(it->first, it->second) && it->first != i)) { // i not in interval
                res.push_back(Interval(i, i));
            }
        }
        cout << i2i.size() << endl;
        assert(i2i.size() % 2 == 0);
        for (auto p = i2i.begin(); p != i2i.end(); p++) {
            res.push_back(p->second);
            p++;
        }
        sort(res.begin(), res.end(), [](Interval i1, Interval i2) {return i1.start < i2.start;});
        return res;
    }
};
