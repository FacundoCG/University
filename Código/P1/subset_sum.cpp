#include <bits/stdc++.h>

using namespace std;

// Backtracking Algorithm
bool subset_sum_BT(vector<int>& multiSet, int i, int k){
    if (i == -1){
        return k == 0;
    }

    if (k < 0){
        return false;
    }

    return subset_sum_BT(multiSet, i-1, k) || subset_sum_BT(multiSet, i-1, k-multiSet[i]);
}

// DP Algorithm with Top-Down approach
bool subset_sum_TD(vector<int>& multiSet, vector<vector<int>>& memo, int i, int k){
    if (i == -1){
        return k == 0;
    }

    if (k < 0){
        return false;
    }

    if (memo[i][k] == INT_MIN){
        memo[i][k] = subset_sum_TD(multiSet, memo, i-1, k) || subset_sum_TD(multiSet, memo, i-1, k-multiSet[i]);
    }

    return memo[i][k];
}

// DP Algorithm with Bottom-Up approach 
// This algorithm has a space complexity of O(nk)
bool subset_sum_BU(vector<int>& multiSet, int k){
    int n = multiSet.size();
    vector<vector<bool>> memo (n+1, vector<bool>(k+1, false));

    for(int i = 0; i < k+1; i++){
        memo[0][i] = i == 0;
    }

    for (int i = 1; i < n+1; i++){
        for (int j = 0; j < k+1; j++){
            memo[i][j] = memo[i-1][j] || (j-multiSet[i-1] >= 0 && memo[i-1][j-multiSet[i-1]]);
        }
    }

    return memo[n][k];
}

// This algorithm has a space complexity of O(k)
bool subset_sum_BU_V2(vector<int>& multiSet, int k){
    int n = multiSet.size();
    vector<bool> memo (k+1, false);
    memo[0] = true;

    for (int i = 1; i < n+1; i++){
        for (int j = k; j > -1; j--){
            memo[j] = memo[j] || (j-multiSet[i-1] >= 0 && memo[j-multiSet[i-1]]);
        }
    }

    return memo[k];
}


int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int k, n;
    cin >> k >> n;

    vector<int> multiSet(n);
    vector<vector<int>> memoTD(n+1, vector<int>(k+1, INT_MIN));

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        multiSet[i] = m;
    }

    cout << subset_sum_BT(multiSet, n-1, k) << "\n";
    cout << subset_sum_TD(multiSet, memoTD, n-1, k) << "\n";
    cout << subset_sum_BU_V2(multiSet, k) << "\n";
}