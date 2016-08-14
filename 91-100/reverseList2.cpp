#include <iostream>

using std::endl;
using std::cout;

int main(int argc, char *argv[]){

	return 0;
}

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
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        ListNode *fake = new ListNode(-1);
        fake->next = head;
        ListNode *start = fake;
        int c = 0;
        while(c < m - 1) {
            start = start->next;
            c++;
        }
        ListNode *pre = start, *end = start->next, *next = end->next;;
        start = start->next;
        c++;
        ListNode *last = start, *now = start->next;
        while(c < n) {
            c++;
            if(c == n) {
                end = now;
                next = end->next;
            }
            ListNode *tmp = now->next;
            now->next = last;
            last = now;
            now = tmp;
        }
        ListNode *partHead = pre->next;
        pre->next = end;
        partHead->next = next;
        
        return fake->next;
    }
};
