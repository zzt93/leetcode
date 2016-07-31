#include <iostream>

using namespace std;

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
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        if(l1 == NULL && l2 == NULL) {
            return NULL;
        }
        ListNode *tmp_head = new ListNode(0);
        ListNode *prev = tmp_head;
        while(l1 != NULL && l2 != NULL) {
            ListNode *small = l2, *large = l1;
            if(l1->val < l2->val) {
                small = l1;
                large = l2;
            }
            prev->next = small;
            
            while(small != NULL && small->val < large->val) {
                prev = small;
                small = small->next;
            }
            prev->next = large;
            prev = large;
            
            l1 = small;
            l2 = large->next;
        }
        if(l2 == NULL) {
            prev->next = l1;
        }
        if(l1 == NULL) {
            prev->next = l2;
        }
        return tmp_head->next;
    }
};
