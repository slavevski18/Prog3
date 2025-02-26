#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        vector<int> best;
        int n = nums1.size(), m = nums2.size();

        for (int i = max(0, k - m); i <= min(k, n); i++) {
            vector<int> candidate = merge(maxSubsequence(nums1, i), maxSubsequence(nums2, k - i));
            if (best.empty() || candidate > best) {
                best = candidate;
            }
        }
        return best;
    }

private:
    vector<int> maxSubsequence(vector<int>& nums, int k) {
        vector<int> result;
        int drop = nums.size() - k;
        for (int num : nums) {
            while (!result.empty() && drop > 0 && result.back() < num) {
                result.pop_back();
                drop--;
            }
            result.push_back(num);
        }
        result.resize(k);
        return result;
    }

    vector<int> merge(vector<int> nums1, vector<int> nums2) {
        vector<int> result;
        while (!nums1.empty() || !nums2.empty()) {
            if (nums1 > nums2) {
                result.push_back(nums1.front());
                nums1.erase(nums1.begin());
            } else {
                result.push_back(nums2.front());
                nums2.erase(nums2.begin());
            }
        }
        return result;
    }
};

int main() {
    Solution solution;
    vector<int> nums1 = {3, 4, 6, 5};
    vector<int> nums2 = {9, 1, 2, 5, 8, 3};
    int k = 5;
    
    vector<int> result = solution.maxNumber(nums1, nums2, k);
    
    for (int num : result) {
        cout << num << " ";
    }
    cout << endl;
    
    return 0;
}
