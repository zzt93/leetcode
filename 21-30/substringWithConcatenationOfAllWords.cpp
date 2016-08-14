#include <iostream>
#include <map>
#include <set>
#include <deque>
#include <vector>
#include <cassert>
#include <cstring>
#include <fstream>

#include <string>
#include <sstream>


using namespace std;
using std::endl;
using std::cout;

class Node {
public:
    int endIndex;
    string word;
    Node *next;
    bool visited;
    Node(int i, string s) {
        endIndex = i;
        word = s;
		visited = false;
		next = NULL;
    }
    
    void addNext(Node* next) {
        assert(this->next == NULL);
        this->next = next;
    }
    
    bool isVisited() {
        return visited;
    }
    
    void visit() {
        visited = true;
    }
    
    int startIndex() {
        return endIndex - word.length() + 1;
    }

    int cmp(const Node *b) {
        return strcmp(word.c_str(), b->word.c_str());
    }
};

class Solution {
public:
    vector<int> findSubstring(string s, vector<string>& words) {
        if(s.empty() || words.empty()) {
            return vector<int>();
        }
        map<int, string> match = matchStr(s, words);
        // make graph
        int wLen = words[0].length();
        map<int, Node*> nodes;
        for(map<int, string>::iterator it = match.begin(); it != match.end(); it++) {
            int end = it->first;
            Node *n;
            if (nodes.count(end)) {
                n = nodes[end];
            } else {
                n = new Node(end, it->second);
                nodes[end] = n;
            }
            if(match.count(end + wLen)) {
				int nextI = end + wLen;
                string tmp = match[nextI];
                // make edge
				Node *next = new Node(nextI, tmp);
				nodes[nextI] = next;
                n->addNext(next);
            }
        }
        // traverse graph
        return traverse(nodes, words.size(), countWordsTimes(words));
    }

    map<string, int> countWordsTimes(vector<string> &words) {
        map<string, int> res;
        for(string &s: words) {
            if(res.count(s)) {
                res[s] = res[s] + 1;
            } else {
                res[s] = 1;
            }
        }
        return res;
    }
    
    vector<int> traverse(map<int, Node*>& nodes, int size, map<string, int> countWords) {
        vector<int> res;
        for(map<int, Node*>::iterator it = nodes.begin(); it != nodes.end(); it++) {
            Node *start = it->second;
            if(start->isVisited()) {
                continue;
            }
            deque<Node*> deque;
            multiset<string> inDeque;
            while(start != NULL) {
                start->visit();
                string word = start->word;
                if(inDeque.count(word) == countWords[word]) {
                    // remove same element if already has
                    // e.g.: 1, 2, 3, 2 -> 3, 2
                    while(deque.front()->cmp(start) != 0) {
                        inDeque.erase(inDeque.find(deque.front()->word));
                        deque.pop_front();
                    }
                    inDeque.erase(inDeque.find(deque.front()->word));
                    deque.pop_front();
                }
                deque.push_back(start);
                inDeque.insert(word);
                assert(deque.size() == inDeque.size());
                if(deque.size() == size) {
                    res.push_back(deque.front()->startIndex());
                }
                start = start->next;
            }
        }
        return res;
    }
    
    map<int, string> matchStr(const string& s, vector<string>& words) {
        map<int, string> res;
        int sLen = s.length();
        set<string> distinctWord(words.begin(), words.end());
        for(const string &pattern: distinctWord) {
            vector<int> next = preprocess(pattern);
            int j = 0, wLen = pattern.length();
            for(int i = 0; i < sLen;) {
                if(j == -1) { // the first char is already different, 
					// move pattern right by increase i
                    j = 0;
                    i++;
                }
                if(s[i] == pattern[j]) {                
                    if(j == wLen - 1) { // match happen
                        // move pattern right
                        j = next[j];
                        // store this match
                        res[i] = pattern;
                        continue;
                    }
                    i++;
                    j++;
                } else {
                    j = next[j];
                }
            }
        }
        return res;
    }
    
    vector<int> preprocess(const string& s) {
        vector<int> res(s.length());
        res[0] = -1;
        const char* start = s.c_str();
        int j = -1;
        for(int i = 0; i < s.length() - 1; ) {
			if(j == -1) {
				res[i + 1] = 0;
				i++;
				j = 0;
				continue;
			}
            if(start[i] == start[j]) {
                res[i + 1] = j + 1;
                j++;
                i++;
            } else {
                j = res[j];
            }
        }
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

int main(int argc, char *argv[]){
	vector<string> words;
	string str, allWords;
	ifstream infile("testcase/substringWithConcatenationOfAllWords");
	infile >> str;
	infile >> allWords;
	allWords.erase(allWords.begin());
	allWords.pop_back();
	split(allWords, ',', words);
	Solution s;
	vector<int> a = s.findSubstring(str, words);
	return 0;
}
