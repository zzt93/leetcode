//
// Created by zzt on 9/12/16.
//
#include <cassert>
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <iostream>
#include <fstream>


using namespace std;

int nextIJ[4][2] = {{2,  1},
                    {-2, 1},
                    {2,  -1},
                    {-2, -1}};
class Solution {
    struct Res {

        vector<string> b;
        vector<int> colIndex;
        int setTime;
        int n;
        int evenGap;
        int left;

        Res(vector<string> &v) : colIndex(v.size()) {
            b = v;
            setTime = 0;
            n = v.size();
            evenGap = ((n & 1) == 1) ? 0 : 1;
            left = n * n;
        }

        bool set(const int r, const int c) {
            assert(r < b.size() && c < b.size());
            colIndex[r] = c;
            // set row
            for (int i = 0; i < n; i++) {
                if (b[r][i] == ' ') {
                    left--;
                }
                b[r][i] = '.';
            }
            // set col
            for (int i = 0; i < n; i++) {
                if (b[i][c] == ' ') {
                    left--;
                }
                b[i][c] = '.';
            }
            // set diagonal
            for (int i = r - 1, j = c - 1; i >= 0 && j >= 0; i--, j--) {
                if (b[i][j] == ' ') {
                    left--;
                }
                b[i][j] = '.';
            }
            for (int i = r - 1, j = c + 1; i >= 0 && j < n; i--, j++) {
                if (b[i][j] == ' ') {
                    left--;
                }
                b[i][j] = '.';
            }
            for (int i = r + 1, j = c - 1; i < n && j >= 0; i++, j--) {
                if (b[i][j] == ' ') {
                    left--;
                }
                b[i][j] = '.';
            }
            for (int i = r + 1, j = c + 1; i < n && j < n; i++, j++) {
                if (b[i][j] == ' ') {
                    left--;
                }
                b[i][j] = '.';
            }

            b[r][c] = 'Q';

            setTime++;
        }

        bool hasNext(int &r, int &c, int dir) {
            c = (c + nextIJ[dir][1]) % n;
            int tryTime = 0;
            do {
                next(r, dir);
                if (b[r][c] == ' ') {
                    return true;
                }
                tryTime++;
            } while (left && tryTime < n / 2);
            return false;
        }

        void next(int &rowIndex, int dir) {
            int gap = nextIJ[dir][0];
            if (rowIndex + gap >= n) {
                rowIndex = rowIndex + gap - n;
                if (rowIndex == 0) {
                    rowIndex += evenGap;
                } else {
                    rowIndex -= evenGap;
                }
            } else if (rowIndex + gap < 0) {
                rowIndex = rowIndex + gap + n;
                if (rowIndex == n - 1) {
                    rowIndex -= evenGap;
                } else {
                    rowIndex += evenGap;
                }
            } else {
                rowIndex = rowIndex + gap;
            }
        }

        bool succ() {
            return setTime == n;
        }

        bool operator<(const Res &r) const {
            for (int i = 0; i < n; i++) {
                if (r.colIndex[i] < colIndex[i]) {
                    return false;
                } else if (r.colIndex[i] > colIndex[i]) {
                    return true;
                }
            }
            return false;
        }


        void rowSym(int i, int j) {
            string t = b[i];
            b[i] = b[j];
            b[j] = t;

            int tmp = colIndex[i];
            colIndex[i] = colIndex[j];
            colIndex[j] = tmp;
        }

        void colSym() {
            for (string &s: b) {
                reverse(s.begin(), s.end());
            }

            for (int i = 0; i < n; i++) {
                colIndex[i] = n - 1 - colIndex[i];
            }
        }

        void xySym() {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < i; j++) {
                    char t = b[i][j];
                    b[i][j] = b[j][i];
                    b[j][i] = t;
                }
            }

            vector<int> tmp(n);
            for (int i = 0; i < n; i++) {
                int j = colIndex[i];
                //assert(b[j][i] == 'G');
                tmp[j] = i;
            }
            colIndex = tmp;
        }

        void transpose() {
            int sum = 2 * n - 2;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n - i - 1; j++) {
                    int gap = i - j;
                    int twoSum = sum - i - j;
                    int newi = (twoSum + gap) / 2;
                    int newj = twoSum - newi;
                    char t = b[i][j];
                    b[i][j] = b[newi][newj];
                    b[newi][newj] = t;
                }
            }

            vector<int> tmp(n);
            for (int i = 0; i < n; i++) {
                int j = colIndex[i];
                int gap = i - j;
                int twoSum = sum - i - j;
                int newi = (twoSum + gap) / 2;
                int newj = twoSum - newi;
                tmp[newi] = newj;
            }
            colIndex = tmp;
        }
    };

    vector<string> initBoard(int n) {
        string s(n, ' ');
        vector<string> res(n, s);
        return res;
    }

    bool valid(int row, int col, Res &b, int dir) {
        if (row + nextIJ[dir][0] < 0 || col + nextIJ[dir][1] < 0) {
            return false;
        }
        int r = row;
        int c = col;
        b.set(r, c);
        while (b.hasNext(r, c, dir)) {
            b.set(r, c);
        }
        return b.succ();
    }

    Res rowSym(Res res, int n) {
        for (int i = 0; i < n / 2; i++) {
            res.rowSym(i, n - i - 1);
        }
        return res;
    }

    Res colSym(Res r, int n) {
        r.colSym();
        return r;
    }

    Res negaOneSym(Res r, int n) {
        r.xySym();
        return r;
    }

    Res oneSym(Res r, int n) {
        r.transpose();
        return r;
    }

public:

    vector<vector<string>> solveNQueens(int n) {
        vector<string> board = initBoard(n);
        set<Res> set;
        int mid = (n % 2) == 1 ? n / 2 + 1 : n / 2;
        for (int r = 0; r < mid; r++) {
            for (int c = 0; c <= r; c++) {
                Res empty(board);
                vector<Res> t(4, empty);
                for (int dir = 0; dir < 4; ++dir) {
                    Res &res = t[dir];
                    if (valid(r, c, res, dir)) {
                        set.insert(res);
                        set.insert(rowSym(res, n));
                        set.insert(colSym(res, n));
                        set.insert(negaOneSym(res, n));
                        set.insert(oneSym(res, n));
                    }
                }
            }
        }
        vector<vector<string>> res;
        for (auto r: set) {
            res.push_back(r.b);
        }
        return res;
    }
};

int main() {
    Solution s;
    ifstream in("testcase/nQueens");
    int n;
    while (in >> n) {
        cout << n << ": ";
        vector<vector<string>> t = s.solveNQueens(n);
        cout << t.size() << endl;
        for (vector<string> &v: t) {
            for (string &str: v) {
                cout << str << endl;
            }
            cout << endl;
        }
    }
}
