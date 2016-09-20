//
// Created by zzt on 9/20/16.
//


#include <iostream>

using namespace std;

/**
 * Definition for singly-linked list.

 */
struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {
        if (head == NULL) {
            return head;
        }
        ListNode *fake = new ListNode(-1);
        fake->next = head;
        ListNode *now = head;
        int len = 0;
        while (now != NULL) {
            len++;
            now = now->next;
        }
        int gap = (k % len);
        //cout << left << endl;
        ListNode *sec = fake, *first = fake;
        for (int i = 0; i < gap; i++) {
            sec = sec->next;
        }
        //cout << sec->val;
        while (sec->next != NULL) {
            first = first->next;
            sec = sec->next;
        }

        sec->next = head;
        fake->next = first->next;
        first->next = NULL;

        return fake->next;
    }
};