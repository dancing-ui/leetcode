#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(vector<int> &prices) {
        int n = prices.size();
        vector<vector<int>> f(n, vector<int>(2, 0));
        f[0][0] = 0;
        f[0][1] = -prices[0];
        for (int i = 1; i < n; i++) {
            f[i][0] = max(f[i - 1][0], f[i - 1][1] + prices[i]);
            f[i][1] = max(f[i - 1][1], f[i - 1][0] - prices[i]);
        }
        return f[n - 1][0];
    }
};

int main() {
    return 0;
}