
#include <iostream>
#include <cassert>
#include <vector>

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
    ListNode *lastSmall(ListNode *h, int x) {
        ListNode *n = h;
        while (n->next != NULL && n->next->val < x) {
            n = n->next;
        }
        return n;
    }

    ListNode *lastLarge(ListNode *h, int x) {
        ListNode *n = h;
        while (n->next != NULL && n->next->val >= x) {
            n = n->next;
        }
        return n;
    }

    void insert(ListNode *p, ListNode *l, ListNode *le) {
        assert(p != NULL);
        ListNode *ls = l->next;
        ListNode *n = p->next;
        p->next = ls;
        l->next = le->next;
        le->next = n;
    }

public:
    ListNode *partition(ListNode *head, int x) {
        ListNode *fake = new ListNode(-1);
        fake->next = head;

        ListNode *left = lastSmall(fake, x), *right = left;
        while (left->next != NULL) {
            right = lastLarge(right, x);
            assert(right != NULL);
            assert(right->val >= x);
            if (right->next == NULL) {
                break;
            }
            ListNode *tmpLeft = lastSmall(right, x);
            insert(left, right, tmpLeft);
            left = tmpLeft;
        }
        return fake->next;
    }
};

ListNode *makeList();

int main() {
    Solution s;
    ListNode *h = makeList();
    s.partition(h, 3);
}

ListNode *makeList() {
    ListNode *h = new ListNode(-1), *tmp = h;

    vector<int> v = {1, 4, 3, 2, 5, 2};
    for (int i = 0; i < v.size(); ++i) {
        tmp->next = new ListNode(v[i]);
        tmp = tmp->next;
    }
    return h->next;
}