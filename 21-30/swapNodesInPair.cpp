#include <iostream>


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
    ListNode* swapPairs(ListNode* head) {
        ListNode *fake = new ListNode(-1);
        fake->next = head;
        ListNode *now = head, *pre = fake;
        while(now != NULL) {
            ListNode *next = now->next;
            if (next != NULL) {
                ListNode *tmp = next->next, *tmpPre = now;
                swap(pre, now, next);
                now = tmp;
                pre = tmpPre;
            } else {
                break;
            }
        }
        return fake->next; 
    }
    
    void swap(ListNode *pre, ListNode *now, ListNode *next) {
        pre->next = next;
        ListNode *tmp = next->next;
        next->next = now;
        now->next = tmp;
    }
};
