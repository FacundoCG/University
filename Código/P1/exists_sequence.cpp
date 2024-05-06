#include <bits/stdc++.h>

using namespace std;

// DP Algorithm with approach Top-Down
int solve(vector<int>& A, vector<vector<int>>& memo, int m, int i, int w){
    int n = A.size();
    if (i+1 == n){
        // cout << "Checking the m: " << m << endl;
        return m == w;
    }

    if (m > w){
        // cout << "The current m: " << m << " is useless and the i is: " << i << endl;
        return 0;
    }

    if (memo[i][m] == -1){
        // cout << "The current m is: " << m << " and i is: " << i << endl;
        memo[i][m] =  solve(A, memo, m+A[i+1], i+1, w) || solve(A, memo, m*A[i+1], i+1, w) || solve(A, memo, pow(m, A[i+1]), i+1, w);
    }

    return memo[i][m];
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int w, n;
    cin >> w >> n;

    vector<int> A(n, 0);
    vector<vector<int>> memoTD(n, vector<int>(w+1, -1));

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        A[i] = m;
    }

    cout << solve(A, memoTD, A[0], 0, w) << endl;
}