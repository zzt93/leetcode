#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace std;
using std::endl;
using std::cout;

class Solution {

    static bool cmp(const int &i, const int &j) {
        return i > j;
    }

public:
    void nextPermutation(vector<int> &nums) {
        if (nums.empty()) {
            return;
        }
        int size = nums.size();
        int last = nums[size - 1];
        int i;
        for (i = size - 2; i >= 0; i--) {
            if (last > nums[i]) {
                break;
            }
            last = nums[i];
        }
        if (i < 0) {
            sort(nums.begin(), nums.end());
            return;
        }
        // invariant: [i+1, size) descending
        // solution: [0, i-1) -- retain, swap(nums[i], min( nums[i+1, size) > nums[i] )), sort [i+1, size)
        vector<int>::iterator up = lower_bound(nums.begin() + i + 1, nums.end(), nums[i], cmp) - 1;
        assert(up != nums.end());
        iter_swap(up, nums.begin() + i);
        sort(nums.begin() + i + 1, nums.end());
    }
};

int main(int argc, char *argv[]) {
    Solution s;
    vector<int> a = {2, 5, 4, 3, 2, 2, 1};
//	vector<int> a = {1, 2, 3, 4};
    s.nextPermutation(a);
    for (int &i: a) {
        cout << i << " ";
    }
    return 0;
}
