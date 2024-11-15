#include <vector>
using namespace std;

class Solution {
public:
    int maxProfit(int k, vector<int> &prices) {
        int n = prices.size();
        constexpr int inf = 0x3f3f3f3f;
        vector<vector<vector<int>>> f(n, vector<vector<int>>(k + 1, vector<int>(2, 0)));
        f[0][0][0] = 0;
        f[0][0][1] = -prices[0];
        for (int i = 1; i <= k; i++) {
            f[0][i][0] = -inf;
            f[0][i][1] = -inf;
        }
        for (int i = 1; i < n; i++) {
            f[i][0][1] = max(f[i - 1][0][1], -prices[i]);
            for (int j = 1; j <= k; j++) {
                f[i][j][0] = max(f[i - 1][j][0], f[i][j - 1][1] + prices[i]);
                f[i][j][1] = max(f[i - 1][j][1], f[i][j][0] - prices[i]);
            }
        }
        return max(0, f[n - 1][k][0]); // when n=1, return f[0][2][0]=-inf, so compared with 0 for maximum
    }
};

int main() {
    return 0;
}