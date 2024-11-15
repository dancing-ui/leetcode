#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        constexpr int inf = 0x3f3f3f3f;
        vector<vector<vector<int>>> f(n, vector<vector<int>>(2, vector<int>(2, 0)));
        f[0][0][0] = 0;
        f[0][0][1] = -prices[0];
        f[0][1][0] = -inf;
        f[0][1][1] = -inf;

        for (int i = 1; i < n; i++) {
            f[i][0][0] = max(f[i - 1][0][0], f[i - 1][1][0]);
            f[i][0][1] = max(f[i - 1][0][1], f[i - 1][0][0] - prices[i]);
            f[i][1][0] = f[i - 1][0][1] + prices[i];
            f[i][1][1] = -inf;
        }
        return max(f[n - 1][0][0], f[n - 1][1][0]);
    }
};

int main() {
    return 0;
}