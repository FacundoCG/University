#include <bits/stdc++.h>
using namespace std;

int maximize_acorns_BU(vector<vector<int>>& trees, int h, int f){
    int t = trees.size();
    int res = 0;

    vector<vector<int>> memo(h+1, vector<int>(t, 0));
    vector<int> maximos(h+1, 0);

    for (int i = 0; i < t; i++){
        memo[0][i] = trees[i][0];
        maximos[0] = max(maximos[0], memo[0][i]);
    }

    for (int i = 1; i <= h; i++){
        for (int j = 0; j < t; j++){
            int extra = trees[j][i];

            memo[i][j] = extra + memo[i-1][j];

            if (i - f >= 0){
                memo[i][j] = max(memo[i][j], extra + maximos[i-f]);
            }

            maximos[i] = max(maximos[i], memo[i][j]);
        }
    }

    for (int i = 0; i < t; i++){
        res = max(res, memo[h][i]);
    }

    return res;
}

int main() {
    ios :: sync_with_stdio(0);
    cin.tie(0);

    int c;
    cin >> c;

    for (int i = 0; i < c; i++) {
        int t, h, f;
        cin >> t >> h >> f;

        vector<vector<int>> trees(t, vector<int>(h+1, 0));

        for (int j = 0; j < t; j++) {
            int m;
            cin >> m;

            for (int k = 0; k < m; k++){
                int a;
                cin >> a;

                trees[j][a] += 1;
            }
        }

        int res = maximize_acorns_BU(trees, h, f); 
        cout << res << "\n";
    }

    int finish;
    cin >> finish;
}