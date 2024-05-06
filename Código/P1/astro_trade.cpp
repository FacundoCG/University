#include <bits/stdc++.h>

using namespace std;

// DP Algorithm with approach Top-Down
int maximize_net_profit_from_asteroids_TD(vector<int>& asteroids, vector<vector<int>>& memo, int j, int c){
    if (j == -1 && c == 0){
		return 0;
	}
	
    if (j+1 < c || c < 0){
		return INT_MIN;
	}	

	if (memo[j][c] == -1){
		int buy = maximize_net_profit_from_asteroids_TD(asteroids, memo, j-1, c-1);
        int pass = maximize_net_profit_from_asteroids_TD(asteroids, memo, j-1, c);
		int sell = maximize_net_profit_from_asteroids_TD(asteroids, memo, j-1, c+1) + asteroids[j];

        if (buy != INT_MIN){
            buy -= asteroids[j];
        }

		memo[j][c] = max(buy, max(pass, sell));
	}

	return memo[j][c];
}

// DP Algorithm with approach Bottom-Up
// This algorith has a space complexity of O(n^2)
int maximize_net_profit_from_asteroids_BU(vector<int>& asteroids){
    int n = asteroids.size();
    vector<vector<int>> memo(n, vector<int>(n+1, INT_MIN));
    memo[0][0] = 0;
    memo[0][1] = -asteroids[0];

    for (int i = 1; i < n; i++){
        for (int j = 0; j < n+1; j++){
            int buy = INT_MIN;
            int sell = INT_MIN;

            if (j < n && memo[i-1][j+1] != INT_MIN){
                sell = memo[i-1][j+1] + asteroids[i];
            }

            if (j > 0){
                buy = memo[i-1][j-1] - asteroids[i];
            }

            int pass = memo[i-1][j];
            memo[i][j] = max(pass, max(sell,buy));
        }
    }

	return memo[n-1][0];
}

// This algorith has a space complexity of O(n)
int maximize_net_profit_from_asteroids_BU_V2(vector<int>& asteroids){
    int n = asteroids.size();
    vector<vector<int>> memo(2, vector<int>(n+1, INT_MIN));
    memo [0][0] = 0;
    memo [0][1] = -asteroids[0];

    int yesterday = 0;
    int today = 1;

    for (int i = 1; i < n; i++){
        for (int j = n; j > -1; j--){
            int pass = memo[yesterday][j];
            int buy = INT_MIN;
            int sell = INT_MIN;

            if (j < n){
                sell = memo[yesterday][j+1] + asteroids[i];
            }

            if (j > 0 && memo[yesterday][j-1] != INT_MIN){
                buy = memo[yesterday][j-1] - asteroids[i];
            }

            memo[today][j] = max(buy, max(sell, pass));
        }

        if (yesterday == 0){
            yesterday++;
            today--;
        } else {
            yesterday--;
            today++;
        }
    }

	return memo[yesterday][0];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> asteroids(n);
    vector<vector<int>> memoTD(n, vector<int>(n+1, -1));
    memoTD[0][0] = 0;

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        asteroids[i] = m;
    }

    cout << maximize_net_profit_from_asteroids_TD(asteroids, memoTD, n-1, 0) << "\n";
    cout << maximize_net_profit_from_asteroids_BU_V2(asteroids) << "\n";
}