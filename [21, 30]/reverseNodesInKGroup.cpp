#include <iostream>

using std::endl;
using std::cout;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

/**
	- one fake/starting node can make code cleaner
	- when changing the sturcture of list, always need save some pointer before set
	- draw a graph
 */

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode* reverseKGroup(ListNode* head, int k) {
        ListNode *fake = new ListNode(-1);
        fake->next = head;
        ListNode *pre = fake;
        while(pre != NULL) {
            // [partHead, partEnd], i.e. index(partEnd) - index(partHead) + 1 = k
            ListNode *partHead = pre->next;
            ListNode *partEnd = pre;
            int c = 0;
            while(c < k) { // find end
                c++;
                partEnd = partEnd->next;
                if(partEnd == NULL) {
                    return fake->next;
                }
            }
			// save next head because partEnd->next will be set when reverse
			ListNode *nextStart = partEnd->next;
            // reverse internal list
            ListNode *last = partHead, *now = partHead->next;
            while(last != partEnd) {
                ListNode *tmp = now->next;
                // reverse
                now->next = last;
                // move next
                last = now;
                now = tmp;
            }
            // connect head/end
            pre->next = partEnd;
            partHead->next = nextStart;
            pre = partHead;
        }
        return fake->next;
    }
};


int main(int argc, char *argv[]){
	int t[] = {1, 2, 3, 4, 5, 6};
	ListNode *head = new ListNode(-1);
	ListNode *h = head;
	for(int i = 0; i < sizeof t / sizeof t[0]; i++) {
		h->next = new ListNode(t[i]);
		h = h->next;
	}
	Solution s;
	s.reverseKGroup(head->next, 2);
	return 0;
}
