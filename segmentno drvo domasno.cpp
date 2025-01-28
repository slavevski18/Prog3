#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <climits>

using namespace std;

class SegmentTree {
private:
    vector<int> treeMin, treeMax, treeSum;
    int n;

    void build(const vector<int>& arr, int node, int start, int end) {
        if (start == end) {
            treeMin[node] = arr[start];
            treeMax[node] = arr[start];
            treeSum[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            int leftNode = 2 * node + 1;
            int rightNode = 2 * node + 2;
            build(arr, leftNode, start, mid);
            build(arr, rightNode, mid + 1, end);
            treeMin[node] = min(treeMin[leftNode], treeMin[rightNode]);
            treeMax[node] = max(treeMax[leftNode], treeMax[rightNode]);
            treeSum[node] = treeSum[leftNode] + treeSum[rightNode];
        }
    }

    int queryMin(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return INT_MAX; 
        if (l <= start && end <= r) return treeMin[node]; 
        int mid = (start + end) / 2;
        return min(queryMin(2 * node + 1, start, mid, l, r),
                   queryMin(2 * node + 2, mid + 1, end, l, r));
    }

    int queryMax(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return INT_MIN; 
        if (l <= start && end <= r) return treeMax[node]; 
        int mid = (start + end) / 2;
        return max(queryMax(2 * node + 1, start, mid, l, r),
                   queryMax(2 * node + 2, mid + 1, end, l, r));
    }

    int querySum(int node, int start, int end, int l, int r) {
        if (r < start || l > end) return 0;
        if (l <= start && end <= r) return treeSum[node];
        int mid = (start + end) / 2;
        return querySum(2 * node + 1, start, mid, l, r) +
               querySum(2 * node + 2, mid + 1, end, l, r);
    }

public:
    SegmentTree(const vector<int>& arr) {
        n = arr.size();
        treeMin.resize(4 * n, INT_MAX);
        treeMax.resize(4 * n, INT_MIN);
        treeSum.resize(4 * n, 0);
        build(arr, 0, 0, n - 1);
    }

    int getMin(int l, int r) {
        return queryMin(0, 0, n - 1, l, r);
    }

    int getMax(int l, int r) {
        return queryMax(0, 0, n - 1, l, r);
    }

    int getSum(int l, int r) {
        return querySum(0, 0, n - 1, l, r);
    }
};

int main() {
    srand(time(0));
    int size = 30 + rand() % 171; 
    vector<int> arr(size);

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000; 
    }

    cout << "Генерирана низа: ";
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;

    SegmentTree st(arr);

    int l = 5, r = 20; 
    cout << "Минимален елемент во опсегот [" << l << ", " << r << "] е: " << st.getMin(l, r) << endl;
    cout << "Максимален елемент во опсегот [" << l << ", " << r << "] е: " << st.getMax(l, r) << endl;
    cout << "Сума на елементите во опсегот [" << l << ", " << r << "] е: " << st.getSum(l, r) << endl;

    return 0;
}
