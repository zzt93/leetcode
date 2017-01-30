//
// Created by zzt on 1/28/17.
//

#include <iostream>
#include <vector>
#include <map>

using namespace std;

class Solution {
public:
    vector<vector<int>> possibleNext(vector<vector<char>> &board, int x, int y) {
        int n = board.size() - 1;
        int m = board[0].size() - 1;
        vector<vector<int>> res;
        vector<int> down = {x + 1, y};
        vector<int> right = {x, y + 1};
        vector<int> up = {x - 1, y};
        vector<int> left = {x, y - 1};
        bool notUp = false, notD = false, notL = false, notR = false;
        if (x == 0) {
            notUp = true;
            if (y == 0) {
                notL = true;
            }
            if (y == m) {
                notR = true;
            }
        }
        if (x == n) {
            notD = true;
            if (y == 0) {
                notL = true;
            }
            if (y == m) {
                notR = true;
            }
        }
        if (x != 0 && x != n) {
            if (y == 0) {
                notL = true;
            }
            if (y == m) {
                notR = true;
            }
        }
        if (!notD) {
            res.push_back(down);
        }
        if (!notUp) {
            res.push_back(up);
        }
        if (!notR) {
            res.push_back(right);
        }
        if (!notL) {
            res.push_back(left);
        }
        return res;
    }

    bool findWord(string &str, int i, vector<vector<char>> &board, int x, int y, vector<vector<bool>> &visit) {
        bool same = str[i] == board[x][y];
        if (str.size() - 1 == i) {
            return same;
        }
        if (same) {
            visit[x][y] = true;
            for (vector<int> &loc: possibleNext(board, x, y)) {
                int &newX = loc[0];
                int &newY = loc[1];
                //cout << newX << " " << newY << endl;
                if (visit[newX][newY] == false &&
                    findWord(str, i + 1, board, newX, newY, visit)) {
                    return true;
                }
            }
            visit[x][y] = false;
        }
        return false;
    }

    bool exist(vector<vector<char>> &board, string word) {
        int n = board.size();
        int m = board[0].size();
        vector<vector<bool>> visit(n, vector<bool>(m));
        map<char, vector<vector<int>>> map;
        for (int i = 0; i < n; ++i) {
            for (int x = 0; x < m; ++x) {
                char &c = board[i][x];
                if (!map.count(c)) {
                    map[c] = vector<vector<int>>();
                }
                vector<int> tmp;
                tmp.push_back(i);
                tmp.push_back(x);
                map[c].push_back(tmp);

                visit[i][x] = false;
            }
        }
        char c = word[0];
        if (map.count(c)) {
            for (vector<int> &loc: map[c]) {
                cout << ":" << loc[0] << " " << loc[1] << endl;
                if (findWord(word, 0, board, loc[0], loc[1], visit)) {
                    return true;
                }
            }
        }
        return false;
    }
};


int main() {
//    string s1 = "abc", s2 = "aed", s3 = "afg";
    string s1 = "aaaaa", s2 = "aaaaa", s3 = "aaaaa", s4 = "aaaab";
    vector<char> v1(s1.begin(), s1.end());
    vector<char> v2(s2.begin(), s2.end());
    vector<char> v3(s3.begin(), s3.end());
    vector<char> v4(s4.begin(), s4.end());
    Solution s;
    vector<vector<char>> vv;
    vv.push_back(v1);
    vv.push_back(v2);
    vv.push_back(v3);
    vv.push_back(v4);
    cout << "res " << s.exist(vv, "aaaaaaaaaaaaaaaaaaaa");
}
