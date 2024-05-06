#include <bits/stdc++.h>

using namespace std;

int vectorSum(vector<int>& v){
    int n = v.size();
    int res = 0;

    for (int i = 0; i < n; i++){
        res += v[i];
    }

    return res;
}

int maxVector(vector<int>& v){
    int res = v[0];
    int n = v.size();

    for (int i = 1; i < n; i++){
        if (v[i] > res){
            res = v[i];
        }
    }

    return res;
}

tuple<int,int> optimalResult(tuple<int,int>& v1, tuple<int,int>& v2){
    int n1 = get<0>(v1);
    int n2 = get<0>(v2);
    int p1 = get<1>(v1);
    int p2 = get<1>(v2);

    if (n1 > n2){
        return v1;
    } else if (n1 < n2){
        return v2;
    }

    if (p1 < p2){
        return v1;
    }

    return v2;
}


// DP Algorithm with Top-Down approach
int longest_stack_search_TD (vector<int>& weights, vector<int>& tolerances, vector<vector<int>>& memo, int i, int p){
    if (i == -1){
        return 0;
    }

    if (memo[i][p] == -1){
        int ignore_box = longest_stack_search_TD (weights, tolerances, memo, i-1, p);
        if (tolerances[i] < p){
            memo[i][p] = ignore_box;
        } else {
            int using_box = longest_stack_search_TD (weights, tolerances, memo, i-1, p+weights[i]) + 1;
            memo[i][p] = max(ignore_box, using_box);
        }
    }

    return memo[i][p];
}

// DP Algorithm with Bottom-Up approach
int longest_stack_search_BU(vector<int>& weights, vector<int>& tolerances){
    int n = weights.size();
    int s = maxVector(tolerances);
    vector<vector<int>> memo (n, vector<int>(s+1, 0));


    for (int i = 0; i < n; i++){
        memo[i][tolerances[i]] = 1;
    }


    for (int i = 1; i < n; i++){
        for (int j = 0; j <= s; j++){
            int ignoreBox = memo[i-1][j];
            int useBox = 0;
                
            if (weights[i] < j && j + weights[i] <= s){
                int useBox = 1 + memo[i-1][j + weights[i]];                
            }

            memo[i][j] = max(memo[i][j], max(ignoreBox, useBox));
        }
    }

    int res = 0;

    for (int i = 0; i <= s; i++){
        res = max(res, memo[n-1][i]);
    }

    cout << "Printing the matrix defined" << endl;
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j <= s; j++){
            cout << memo[i][j] << " ";
        }

        cout << "\n";
    }

    return res;
} 

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int n;
    cin >> n;

    vector<int> weights(n);
    vector<int> tolerances(n);
    int maxWeight = 0;

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        weights[i] = m;
        maxWeight += m;
    }

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        tolerances[i] = m;
    }

    // vector<vector<int>> memoTD(n, vector<int>(maxWeight + 1, -1));
    // cout << "The maximum number of boxs is: " << longest_stack_search_TD(weights, tolerances, memoTD, n-1, 0) << "\n";
    cout << "The maximum number of boxs is: " << longest_stack_search_BU(weights, tolerances) << "\n";
}