#include <iostream>
#include <cassert>
#include <climits>
#include <fstream>
#include <algorithm>
#include <vector>
#include <set>
#include <list>
#include <sstream>

using namespace std;


class Solution {
    class Point {
    public:
        int r;
        int c;
        Point(int f, int s) {
            r = f;
            c = s;
        }
    };
    static const char EMPTY = '.';
    list<char> candidates[9][9];
    static const int SIZE = 9;
    Point* square[SIZE][9];
    
    void fillCandidates(vector<vector<char>>& board) {
        for(int r = 0; r < board.size(); r++) {
            vector<char> &v = board[r];
            for(int c = 0; c < board.size(); c++) {
                char &ch = v[c];
                if(ch == EMPTY) {
                    setCandidate(board, r, c);
                }
            }
        }
    }
    
    set<char> getConstraints(vector<vector<char>>& board, int r, int c) {
        set<char> res;
        vector<char> &row = board[r];
        for(char &c: row) {
            if(c == EMPTY) {
                continue;
            }
            res.insert(c);
        }
        // add column char
        for(int i = 0; i < 9; i++) {  
            char ch = board[i][c];
            if(ch == EMPTY) {
                continue;
            }
            res.insert(ch);
        }
        // add square
        Point **squareI = getSquareI(r, c);
        for(int i = 0; i < SIZE; i++) {
            char ch = board[squareI[i]->r][squareI[i]->c];
            if(ch == EMPTY) {
                continue;
            }
            res.insert(ch);
        }
        return res;
    }
    
    Point** getSquareI(int r, int c) {
        int i = r / 3 * 3 + c / 3;
        return square[i];
    }

    
    void setCandidate(vector<vector<char>>& board, int r, int c) {
        list<char> &v = candidates[r][c];
        set<char> have = getConstraints(board, r, c);
        for(char c = '1'; c <= '9'; c++) {
            if(!have.count(c)) {
                v.push_back(c);
            }
        }
    }

    void updateCandidate(vector<vector<char>>& board, int r, int c, char v, list<char> &candi) {
        auto it = find(candi.begin(), candi.end(), v);
        if(it == candi.end()) {
            return;
        }
        candi.erase(it);
        if(candi.size() == 1) {
            setACellUpdateCandidate(board, r, c, popSingle(candi));
        }
    }
    void setACellUpdateCandidate(vector<vector<char>>& board, int r, int c, char v) {
        board[r][c] = v;
        // update possible candidates
        vector<char> &row = board[r];
        for(int col = 0; col < 9; col++) {
            char &c = row[col];
            if(c != EMPTY) {
                continue;
            }
            list<char> &candi = candidates[r][col];
            updateCandidate(board, r, col, v, candi);
        }
        // add column char
        for(int row = 0; row < 9; row++) {  
            char ch = board[row][c];
            if(ch != EMPTY) {
                continue;
            }
            list<char> &candi = candidates[row][c];
            updateCandidate(board, row, c, v, candi);
        }
        // add square
        Point **squareI = getSquareI(r, c);
        for(int i = 0; i < SIZE; i++) {
            int row = squareI[i]->r;
            int col = squareI[i]->c;
            char ch = board[row][col];
            if(ch != EMPTY) {
                continue;
            }
            list<char> &candi = candidates[row][col];
            updateCandidate(board, row, col, v, candi);
        }
    }
    
    void initSquareIndex() {
        for(int i = 0; i < SIZE; i++) {
            int tmpR = i / 3 * 3;
            int tmpC = i % 3 * 3;
            Point** tmp = square[i];
            for(int j = 0; j < SIZE; j++) {
                int r = tmpR + j / 3;
                int c = tmpC + j % 3;
                tmp[j] = new Point(r, c);
            }
        }
    }

    char popSingle(list<char>& l) {
        assert(l.size() == 1);
        char c = l.front();
        l.pop_front();
        return c;
    }

    char fakePop(list<char> l) {

    }

    // use copy of board to simulate again and again?
    bool recursive(vector<vector<char>> board, bool &conflict) {
        // TODO not finish yet
        list<char> &min = findMin(candidates);
        if(min.size() == 1) {
        } else {
        }
    }

    void simulate(vector<vector<char>> &board) {
        bool conflict = false;
        list<char> fakeCandidates = candidates;
        while(!conflict) {
            recursive(board, conflict);
        }
    }
    
public:

    Solution() {
        initSquareIndex();        
    }
    
    void solveSudoku(vector<vector<char>>& board) {
        fillCandidates(board);
        bool canFill = true;
        while(canFill) {
            canFill = false;
            for(int r = 0; r < SIZE; r++) {
                for(int c = 0; c < SIZE; c++) {
                    if(candidates[r][c].size() == 1) {
                        setACellUpdateCandidate(board, r, c, popSingle(candidates[r][c]));
                        canFill = true;
                    }
                }
            }
        }
        simulate(board);
    }
};

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

int main(int argc, char *argv[]){
	vector<string> words;
	string allWords;
	ifstream infile("testcase/sudokuSolver");
	infile >> allWords;
	allWords.erase(allWords.begin());
	allWords.pop_back();
	split(allWords, ',', words);
	Solution s;
	vector<vector<char>> input;
	for(string &s: words) {
	    input.push_back(vector<char>(s.begin(), s.end()));
	}
	s.solveSudoku(input);
	return 0;
}
