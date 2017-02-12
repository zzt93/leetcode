//
// Created by zzt on 1/31/17.
//

#include <iostream>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

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
    ListNode *deleteDuplicates(ListNode *head) {
        if (head == NULL) {
            return head;
        }
        ListNode *now = head, *next = head->next;
        while (next != NULL) {
            if (now->val == next->val) {
                now->next = next->next;
            } else {
                now = next;
            }
            next = now->next;
        }
        return head;
    }
};