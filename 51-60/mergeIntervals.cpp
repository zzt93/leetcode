//
// Created by zzt on 9/17/16.
//

#include <iostream>
#include <vector>
#include <map>
#include <cassert>

using namespace std;

/**
 * Definition for an interval.
 * struct Interval {
 *     int start;
 *     int end;
 *     Interval() : start(0), end(0) {}
 *     Interval(int s, int e) : start(s), end(e) {}
 * };
 */
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
    vector<Interval> merge(vector<Interval>& intervals) {
        map<int, Interval> i2i;
        set<int> dup;
        for(int i = 0; i < intervals.size(); i++) {
            //cout << i2i.size() << endl;
            Interval &in  = intervals[i];
            if (in.start > in.end) {
                continue;
            } else if (in.start == in.end) {
                dup.insert(in.start);
                continue;
            }

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
                    if (isEnd(e->first, e->second)) { // in the range of interval
                        end = e;
                        mergedE = e->first;
                    } else if (in.end == e->first) { // two interval connected
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
            //cout << mergedS << ": " << mergedE << endl;
            Interval newIn(mergedS, mergedE);
            i2i[mergedS] = newIn;
            i2i[mergedE] = newIn;
        }


        vector<Interval> res;
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
        return res;
    }
};

int main() {

}