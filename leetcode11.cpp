#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n = 0, max_area = 0;
    cin >> n;
   
    vector<int> heights;
   
    for (int i = 0; i < n; i++)
    {
        int height = 0;
        cin >> height;
        heights.push_back(height);
    }
   
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            int area = (j - i) * (min(heights[i], heights[j]));
           
            if (area > max_area)
                max_area = area;
        }
    }
   
    cout << max_area;

    return 0;
}
