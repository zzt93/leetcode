//
// Created by zzt on 9/28/16.
//


#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <sstream>
#include <fstream>

using namespace std;

class Solution {
    /**
     *
     * @param start start of word, index for @param c
     * @param end end of word, index for @param c
     * @param words
     * @return
     */
    string spread(int start, int end, const vector<string> &words, const vector<int> &c, int max) {
        assert(is_space(start));
        if (is_space(end)) {
            end--;
        }
        int words_count = (end - start) / 2 + 1;
        int space_count = words_count - 1;
        int words_len = c[end] - c[start] - space_count;
        int left_space = max - words_len;
        if (space_count == 0) {
            space_count++;
        }
        int ave = left_space / space_count;
        int more_time = left_space - ave * space_count;
        string res(max, ' ');
        bool is_word = true;
        int word_i = start;
        for (int i = 0; i < max;) {
            if (is_word) {
                is_word = false;
                string w = words[get_word_i(word_i)];
                word_i += 2;
                for (int j = 0; j < w.size(); ++j) {
                    res[i] = w[j];
                    i++;
                }
            } else {
                if (more_time > 0) {
                    i += (ave + 1);
                    more_time--;
                } else {
                    i += ave;
                }
                is_word = true;
            }
        }
        return res;
    }

    bool is_space(int i) {
        return (i & 1) == 0;
    }

    int get_word_i(int t) {
        return t / 2;
    }

    string left_align(int start, int end, const vector<string> &words, const vector<int> &c, int max) {
        string res(max, ' ');
        int len = c[end] - c[start];
        bool is_word = true;
        int word_i = start;
        for (int i = 0; i < len;) {
            if (is_word) {
                is_word = false;
                string w = words[get_word_i(word_i)];
                word_i += 2;
                for (int j = 0; j < w.size(); ++j) {
                    res[i] = w[j];
                    i++;
                }
            } else {
                i++;
                is_word = true;
            }
        }
        return res;
    }


public:
    vector<string> fullJustify(vector<string> &words, int m) {
        if (m <= 1) {
            return words;
        }
        int n = words.size();
        int sz = 2 * n;
        vector<int> c(sz);
        c[0] = 0;
        for (int i = 1; i < sz; i++) {
            if (is_space(i)) {
                c[i] = c[i - 1] + 1;
            } else {
                c[i] = c[i - 1] + words[i / 2].size();
            }
        }
        int max = c[sz - 1];

        int base = 0;
        vector<string> res;
        const vector<int>::iterator &begin1 = c.begin();
        auto start = begin1;
        while (m + base <= max) {
            auto end = upper_bound(begin1, c.end(), m + base) - 1;
            assert(*end <= m + base);
            int anEnd = end - begin1;
            res.push_back(spread(start - begin1, anEnd, words, c, m));

            if (!is_space(anEnd)) {
                end++;
            }
            if (end == c.end()) {
                return res;
            }
            base = *end;
            start = end;
        }
        // handle last line
        assert(is_space(start - begin1));
        res.push_back(left_align(start - begin1, sz - 1, words, c, m));
        return res;
    }
};


void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}

vector<string> split(const string &s, char delim) {
    vector<string> elems;
    split(s, delim, elems);
    return elems;
}

int main(int argc, char *argv[]) {
    string allWords;
    int m;
    ifstream infile("testcase/textJustification");
    Solution s;
    while (infile >> allWords) {
        vector<string> words;
        allWords.erase(allWords.begin());
        allWords.pop_back();
        split(allWords, ',', words);
        infile >> m;
        vector<string> a = s.fullJustify(words, m);
        for (string &str: a) {
            cout << str << ";";
        }
        cout << endl;
    }
    return 0;
}