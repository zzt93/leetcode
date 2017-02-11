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
        ListNode fake(0);
        fake.next = head;
        ListNode *pre = &fake, *now = head, *next;
        while (now != NULL) {
            next = now->next;
            bool hasSame = false;
            while (next != NULL && now->val == next->val) {
                hasSame = true;
                now = next;
                next = next->next;
            }
            if (hasSame) {
                // delete same node
                pre->next = next;
            } else {
                pre = now;
            }
            now = pre->next;
        }
        return fake.next;
    }
};